#include <Arduino.h>
#include "Config.h"
#include "hardware/Button.h"
#include "states/ButtonState.h"
#include "hardware/LED.h"
#include "hardware/Display.h"
#include "hardware/VOC.h"
#include "controllers/network/WiFiController.h"
#include "controllers/network/NTPController.h"
#include "controllers/network/MQTTController.h"

// Create instances
LED led;
Display display;
VOC voc(led);
WiFiController wifiController(display);
ButtonState buttonState(led, display, wifiController);
Button button(BUTTON_PIN, true, buttonState);

// Timing variables
static unsigned long lastLedUpdate = 0;
static unsigned long lastDisplayUpdate = 0;
static unsigned long lastMqttCheck = 0;

// UI state
bool uiToggleState = true;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Initialize display
    display.begin();

    // Initialize LEDs
    led.begin();

    // Initialize VOC Driver
    voc.begin();

    // Connect to Wi-Fi
    if (!wifiController.begin(WIFI_SSID, WIFI_PASS))
    {
        // Handle connection failure (e.g., retry, enter sleep, etc.)
        Serial.println("Handling Wi-Fi connection failure...");
        // Example: Retry connection or restart
        ESP.restart();
    }

    // Initialize MQTT
    mqtt.subscribe(&eventFeed);
    bool connected = mqttConnect(1);
    if (!connected)
    {
        Serial.println("MQTT connection failed; continuing anyway.");
        display.writeText("No luck with accessing the calendar :(");
    }

    // Initialize NTP
    display.writeText("Checking the time...");
    setupTime(NTP_SERVER, UTC_OFFSET, DAYLIGHT_OFFSET);

    bool synced = syncTime(10000); // 10s timeout
    if (!synced)
    {
        Serial.println("Time sync failed, continuing anyway.");
        display.writeText("Time sync failed :(");
    }

    // Attach callback functions to button events
    button.begin();
}

void loop()
{
    // Let OneButton handle the button events
    button.tick();

    unsigned long now = millis();

    // LED update
    if (now - lastLedUpdate >= 50)
    {
        lastLedUpdate = now;
        led.update();
    }

    // Display update, MQTT subscription check
    if (now - lastDisplayUpdate >= 1000)
    {
        lastDisplayUpdate = now;
        if (mqtt.connected())
        {
            Adafruit_MQTT_Subscribe *sub = mqtt.readSubscription(50);
            if (sub == &eventFeed)
            {
                parseEventJSON((char *)eventFeed.lastread);
                showEvent = true;
                eventDisplayStart = now;
            }
        }

        if (showEvent && (now - eventDisplayStart >= EVENT_DISPLAY_MS))
        {
            led.setLEDState(LEDState::IDLE);
            showEvent = false;
            eventDisplayed = false;
            eventTitle = eventStart = eventEnd = "";
        }

        if (showEvent)
        {
            if (!eventDisplayed)
            {
                led.setLEDState(LEDState::EVENT_RAINBOW);
                display.drawEventOnDisplay(eventTitle, eventStart, eventEnd, 1);
                eventDisplayed = true;
            }
        }
        else
        {
            time_t t = time(nullptr);
            struct tm *ti = localtime(&t);
            const char *daysOfWeek[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

            display.drawUi(uiToggleState, ti->tm_hour, ti->tm_min,
                   daysOfWeek[ti->tm_wday], ti->tm_mday,
                   voc.readVOC());
        }
    }

    // MQTT connection check
    if (now - lastMqttCheck >= MQTT_RETRY_FREQUENCY_MS)
    {
        lastMqttCheck = now; // Update the last check time
        if (!mqtt.connected())
            mqttConnect(3);
    }
}