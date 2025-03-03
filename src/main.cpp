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
#include "controllers/AnimationsController.h"
#include "states/ClockState.h"
#include "states/State.h"
#include "assets/Bitmaps.h"

// Instances
LED led;
Display display;
VOC voc(led);
State appState;
WiFiController wifiController(display);
NTPController ntpController(display);
MQTTController mqttController(appState, led, display);
AnimationsController *animationsController = nullptr;
ClockState clockState(display, voc);
ButtonState buttonState(led, display, wifiController, clockState, appState);
Button button(BUTTON_PIN, true, buttonState);

// Timing variables
struct TimingControl
{
    unsigned long lastLedUpdate = 0;
    unsigned long lastMqttCheck = 0;
    unsigned long lastMqttUpdate = 0;
    unsigned long lastDisplayUpdate = 0;

    // Timer expiration animation control
    bool timerExpirationAnimationActive = false;
    unsigned long timerExpirationAnimationStart = 0;
};

TimingControl timing;

void onTimerComplete()
{
    timing.timerExpirationAnimationActive = true;
    timing.timerExpirationAnimationStart = millis();
    appState.setMode(AppMode::ANIMATION);
    animationsController->startBitmapAnimation((const byte *)flag, 30, true, false, 5000, 48, 48, "Mission\n      complete!");
    led.setLEDState(LEDState::SPIN_RAINBOW);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    ConfigManager::load();
    display.begin();
    led.begin();
    led.setLEDState(LEDState::SPIN_RAINBOW);

    animationsController = new AnimationsController(display.getHardware());
    animationsController->startBitmapAnimation((const byte *)logo2, 21, false, false, 0, 128, 64, "");
    while (animationsController->isBitmapAnimationRunning())
    {
        animationsController->update();
        led.update();
    }

    voc.begin();
    button.begin();

    WiFiStatus wifiStatus = wifiController.begin(WIFI_SSID, WIFI_PASS);
    if (wifiStatus != WiFiStatus::CONNECTED)
    {
        String errorMessage;
        switch (wifiStatus)
        {
        case WiFiStatus::CONNECTION_TIMEOUT:
            errorMessage = "Connection timeout :(";
            break;
        case WiFiStatus::INVALID_CREDENTIALS:
            errorMessage = "Invalid WiFi credentials";
            break;
        default:
            errorMessage = "Unknown WiFi error";
            break;
        }

        Serial.println("Wi-Fi connection failed: " + errorMessage);
        display.writeAlignedText(errorMessage + "\n\nRestarting...", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        delay(2000);
        ESP.restart();
    }

    mqttController.begin(2);

    if (!ntpController.begin(NTP_SERVER))
    {
        display.writeAlignedText("Time sync failed :(", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        delay(2000);
    }
    appState.getTimer().setOnComplete(onTimerComplete);
    led.setLEDState(LEDState::IDLE);
}

void updatePeripherals(unsigned long now)
{
    // Update button (highest priority for responsiveness)
    button.tick();

    // Update LED at 20Hz
    if (now - timing.lastLedUpdate >= 50)
    {
        timing.lastLedUpdate = now;
        led.update();
    }

    // Check MQTT connection every 30 seconds
    if (now - timing.lastMqttCheck >= 30000)
    {
        timing.lastMqttCheck = now;
        // Only try once to avoid delays
        mqttController.checkConnection(1);
    }

    // Update MQTT frequently but with minimal blocking
    if (now - timing.lastMqttUpdate >= 500)
    {
        timing.lastMqttUpdate = now;
        mqttController.update(now);
    }
}

void updateAppState(unsigned long now)
{
    switch (appState.getMode())
    {
    case AppMode::CLOCK:
        clockState.update();
        break;

    case AppMode::TIMER:
    {
        appState.getTimer().update();

        // Update timer display once per second
        if (now - timing.lastDisplayUpdate >= 1000)
        {
            timing.lastDisplayUpdate = now;
            display.drawTimer(appState.getTimer());
        }
        break;
    }

    case AppMode::ANIMATION:
        animationsController->update();
        if (timing.timerExpirationAnimationActive &&
            (now - timing.timerExpirationAnimationStart >= 5000))
        {
            timing.timerExpirationAnimationActive = false;
            appState.setMode(AppMode::CLOCK);
            led.setLEDState(LEDState::IDLE);
        }
        break;

    case AppMode::DIALOGUE:
        // No update needed for dialogue mode
        break;
    }
}

void loop()
{
    unsigned long now = millis();

    // Update peripherals and controllers
    updatePeripherals(now);

    // Update application state
    updateAppState(now);
}