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
#include "states/State.h"

// Instances
LED led;
Display display;
VOC voc(led);
WiFiController wifiController(display);
ClockState clockState(display, voc);
State appState;
ButtonState buttonState(led, display, wifiController, clockState, appState);
Button button(BUTTON_PIN, true, buttonState);

// Timing variables
static unsigned long lastLedUpdate = 0;
static unsigned long lastDisplayUpdate = 0;
static unsigned long lastMqttCheck = 0;

// Create our MQTT controller (now also takes Display)
MQTTController mqttController(appState, led, display);

void setup()
{
    Serial.begin(115200);
    delay(1000);

    ConfigManager::load();

    display.begin();
    led.begin();
    voc.begin();

    // for prod: if (!wifiController.begin(ConfigManager::config.wifiSSID, ConfigManager::config.wifiPass)) 
    if (!wifiController.begin(WIFI_SSID, WIFI_PASS))
    {
        Serial.println("Handling Wi-Fi connection failure...");
        display.writeAlignedText("Connection timeout. Restarting...");
        delay(2000);
        ESP.restart();
    }

    mqttController.begin(1);

    display.writeAlignedText("Checking the time...");
    setupTime(NTP_SERVER);
    bool synced = syncTime(10000);
    if (!synced)
    {
        Serial.println("Time sync failed, continuing anyway.");
        display.writeAlignedText("Time sync failed :(");
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

    // Periodic check for MQTT connectivity and incoming messages
    if (now - lastMqttCheck >= MQTT_RETRY_FREQUENCY_MS)
    {
        lastMqttCheck = now;
        mqttController.checkConnection(3); 
    }
    mqttController.update(now);

    if (appState.getMode() == AppMode::TIMER) {
       // keep the timer updated
       appState.getTimer().update();
       display.drawTimer(appState.getTimer());
    }
    else if (appState.getMode() == AppMode::CLOCK) {
       clockState.update();
    }
    else if (appState.getMode() == AppMode::ANIMATION) {
       // display animation
    }
    else if (appState.getMode() == AppMode::DIALOGUE) {
       display.writeAlignedText("Dialogue mode!");
    }
}

/*
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
            display.drawEvent(eventTitle, eventStart, eventEnd, 1);
            eventDisplayed = true;
        }
    }
    else {
        // MAIN MODE HANDLING
        AppMode mode = appState.getMode();

        if (mode == AppMode::CLOCK) {
            clockState.update();
        }
        else if (mode == AppMode::TIMER) {
            // Update timer countdown
            appState.getTimer().update();
            // Draw the timer
            display.drawTimer(appState.getTimer());
        }
        else if (mode == AppMode::ANIMATION) {
            // Some custom animation logic
            // e.g. display.showAnimation();
        }
    }
} 
*/