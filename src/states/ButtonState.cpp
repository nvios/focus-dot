#include "states/ButtonState.h"
#include "hardware/LED.h"
#include "hardware/Display.h"
#include "controllers/network/WiFiController.h"

ButtonState::ButtonState(LED &led, Display &display, WiFiController &wifi)
    : led(led)
    , display(display)
    , wifiController(wifi)
    , currentState(STATE_IDLE)
{}

void ButtonState::handleEvent(ButtonEvent event) {
    switch (currentState) {
        case STATE_IDLE:
            if (event == BUTTON_EVENT_SINGLE_CLICK) {
                Serial.println("UI Toggle State Changed");
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK) {
                Serial.println("Double Click: Refreshing Wi-Fi");
                wifiController.begin(WIFI_SSID, WIFI_PASS);
            }
            else if (event == BUTTON_EVENT_LONG_PRESS) {
                Serial.println("Long Press: Entering Config Mode");
                setState(STATE_CONFIG_MODE);
            }
            else if (event == BUTTON_EVENT_RESET_HOLD) {
                Serial.println("Reset Hold: Performing Factory Reset");
                setState(STATE_RESETTING);
            }
            break;

        case STATE_CONFIG_MODE:
            break;

        case STATE_RESETTING:
            Serial.println("Performing Factory Reset...");
            ESP.restart();
            break;

        default:
            setState(STATE_IDLE);
            break;
    }
}

void ButtonState::setState(AppState newState) {
    currentState = newState;
    switch (currentState) {
        case STATE_IDLE:
            led.setLEDState(LEDState::IDLE);
            display.writeText("Idle State");
            break;
        case STATE_CONFIG_MODE:
            led.setLEDState(LEDState::IDLE);
            display.writeText("Configuration Mode");
            break;
        case STATE_RESETTING:
            led.setLEDState(LEDState::IDLE);
            display.writeText("Resetting...");
            break;
        default:
            break;
    }
}