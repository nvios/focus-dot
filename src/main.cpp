#include <Arduino.h>
#include "configurations/Config.h"
#include "configurations/ConfigManager.h"
#include "hardware/Button.h"
#include "states/ButtonState.h"
#include "hardware/LED.h"
#include "hardware/Display.h"
#include "hardware/VOC.h"
#include "controllers/network/WiFiController.h"
#include "controllers/network/NTPController.h"
#include "controllers/network/MQTTController.h"
#include "states/ClockState.h"

// Instances
LED led;
Display display;
VOC voc(led);
WiFiController wifiController(display);
ClockState clockState(display, voc);
ButtonState buttonState(led, display, wifiController, clockState);
Button button(BUTTON_PIN, true, buttonState);

// Timing variables
static unsigned long lastLedUpdate = 0;
static unsigned long lastDisplayUpdate = 0;
static unsigned long lastMqttCheck = 0;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    ConfigManager::load();

    display.begin();
    led.begin();
    voc.begin();

    if (!wifiController.begin(WIFI_SSID, WIFI_PASS)) // for prod: if (!wifiController.begin(ConfigManager::config.wifiSSID, ConfigManager::config.wifiPass)) 
    {
        Serial.println("Handling Wi-Fi connection failure...");
        ESP.restart();
    }

    mqtt.subscribe(&eventFeed);
    bool connected = mqttConnect(1);
    if (!connected)
    {
        Serial.println("MQTT connection failed; continuing anyway.");
        display.writeText("No luck with accessing the calendar :(");
    }

    display.writeText("Checking the time...");
    setupTime(NTP_SERVER);
    bool synced = syncTime(10000);
    if (!synced)
    {
        Serial.println("Time sync failed, continuing anyway.");
        display.writeText("Time sync failed :(");
    }

    button.begin();
}

void loop()
{
    button.tick();

    unsigned long now = millis();

    if (now - lastLedUpdate >= 50)
    {
        lastLedUpdate = now;
        led.update();
    }

    if (now - lastMqttCheck >= MQTT_RETRY_FREQUENCY_MS)
    {
        lastMqttCheck = now;
        if (!mqtt.connected())
            mqttConnect(3);
    }

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
        clockState.update();
    }
}