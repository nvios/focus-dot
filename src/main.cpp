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
MQTTController mqttController(appState, led, display);
AnimationsController *animationsController = nullptr;
ClockState clockState(display, voc);
ButtonState buttonState(led, display, wifiController, clockState, appState);
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
    animationsController = new AnimationsController(display.getHardware());
    display.startAnimation((const byte *)logo2, 21, false, false, 0, 128, 64);
    while (display.isAnimationRunning())
    {
        display.updateAnimation();
    }
    led.begin();
    voc.begin();
    button.begin();

    if (!wifiController.begin(WIFI_SSID, WIFI_PASS))
    {
        Serial.println("Wi-Fi connection failed...");
        display.writeAlignedText("Connection timeout. Restarting...");
        delay(2000);
        ESP.restart();
    }
    mqttController.begin(1);
    display.writeAlignedText("Checking the time...");
    setupTime(NTP_SERVER);
    if (!syncTime(10000))
    {
        Serial.println("Time sync failed, continuing anyway.");
        display.writeAlignedText("Time sync failed :(");
    }
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
    mqttController.update(now);

    if (appState.getMode() == AppMode::TIMER)
    {
        appState.getTimer().update();
        display.drawTimer(appState.getTimer());
    }
    else if (appState.getMode() == AppMode::CLOCK)
    {
        clockState.update();
    }
    else if (appState.getMode() == AppMode::ANIMATION)
    {
        if (led.getLEDState() != LEDState::SOLID_BLUE)
        {
            led.setLEDState(LEDState::SOLID_BLUE);
        }
        animationsController->update();
    }
    else if (appState.getMode() == AppMode::DIALOGUE)
    {
        display.writeAlignedText("Dialogue mode!");
    }
}