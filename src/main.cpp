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
static unsigned long lastLedUpdate = 0;
static unsigned long lastMqttCheck = 0;
static unsigned long lastMqttUpdate = 0;

// Timer expiration animation control
bool timerExpirationAnimationActive = false;
unsigned long timerExpirationAnimationStart = 0;

void onTimerComplete()
{
    timerExpirationAnimationActive = true;
    timerExpirationAnimationStart = millis();
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
    animationsController->startBitmapAnimation((const byte *)logo2, 21, false, false, 0, 128, 64,"");
    while (animationsController->isBitmapAnimationRunning())
    {
        animationsController->update();
        led.update();
    }

    voc.begin();
    button.begin();

    if (!wifiController.begin(WIFI_SSID, WIFI_PASS))
    {
        Serial.println("Wi-Fi connection failed...");
        display.writeAlignedText("Connection timeout :(\n\nRestarting...", DISPLAY_WIDTH, DISPLAY_HEIGHT);
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
        mqttController.checkConnection(3);
    }
    if (now - lastMqttUpdate >= 2000)
    {
        lastMqttUpdate = now;
        mqttController.update(now);
    }

    switch (appState.getMode())
    {
    case AppMode::CLOCK:
        clockState.update();
        break;
    case AppMode::TIMER:
    {
        appState.getTimer().update();
        static unsigned long lastDisplayUpdate = 0;
        if (now - lastDisplayUpdate >= 1000)
        {
            lastDisplayUpdate = now;
            display.drawTimer(appState.getTimer());
        }
        break;
    }
    case AppMode::ANIMATION:
        animationsController->update();
        if (timerExpirationAnimationActive && (now - timerExpirationAnimationStart >= 5000))
        {
            timerExpirationAnimationActive = false;
            appState.setMode(AppMode::CLOCK);
            led.setLEDState(LEDState::IDLE);
        }
        break;
    case AppMode::DIALOGUE:
        break;
    }
}