#include "states/ButtonState.h"
#include "states/State.h"
#include "states/TimerState.h"
#include "hardware/LED.h"
#include "hardware/Display.h"
#include "controllers/network/WiFiController.h"
#include "states/ClockState.h"
#include <ESP.h>

ButtonState::ButtonState(LED &led,
                         Display &display,
                         WiFiController &wifi,
                         ClockState &clock,
                         State &appState)
    : currentState(STATE_IDLE),
      led(led),
      display(display),
      wifiController(wifi),
      clock(clock),
      appState(appState)
{
}

void ButtonState::handleEvent(ButtonEvent event)
{
    // Part A: Local Button FSM transitions
    switch (currentState)
    {
    case STATE_IDLE:
        if (event == BUTTON_EVENT_LONG_PRESS) {
            Serial.println("Long Press: Entering Config Mode");
            setState(STATE_CYCLE_MODE);
        }
        else if (event == BUTTON_EVENT_RESET_HOLD) {
            Serial.println("Reset Hold: Performing Factory Reset");
            setState(STATE_RESETTING);
        }
        // ... we do not necessarily single-click cycle the local state machine
        break;

    case STATE_CYCLE_MODE:
        if (event == BUTTON_EVENT_RESET_HOLD) {
            Serial.println("Reset from Config Mode...");
            setState(STATE_RESETTING);
        }
        break;

    case STATE_RESETTING:
        Serial.println("Performing Factory Reset...");
        ESP.restart();
        break;

    default:
        setState(STATE_IDLE);
        break;
    }

    // Part B: Global "mode" logic
    switch (appState.getMode())
    {
    case AppMode::CLOCK:
        if (event == BUTTON_EVENT_SINGLE_CLICK) {
            // cycle to TIMER or ANIMATION
            appState.cycleMode();
            Serial.println("Mode changed (clock -> next).");
        }
        else if (event == BUTTON_EVENT_DOUBLE_CLICK) {
            // e.g. refresh wifi
            Serial.println("Double Click: Refreshing Wi-Fi");
            wifiController.begin(WIFI_SSID, WIFI_PASS);
        }
        // long press might do nothing special
        break;

    case AppMode::TIMER:
    {
        auto &timerRef = appState.getTimer();
        if (!timerRef.isRunning()) {
            if (event == BUTTON_EVENT_DOUBLE_CLICK) {
                Serial.println("Starting timer");
                timerRef.start();
            }
            else if (event == BUTTON_EVENT_LONG_PRESS) {
                Serial.println("Cycling Timer Preset");
                timerRef.cyclePreset();
            }
        } else {
            // Timer is running or paused
            if (event == BUTTON_EVENT_SINGLE_CLICK) {
                if (timerRef.isPaused()) {
                    Serial.println("Resume timer");
                    timerRef.resume();
                } else {
                    Serial.println("Pause timer");
                    timerRef.pause();
                }
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK) {
                if (timerRef.isPaused()) {
                    Serial.println("Stop timer, return to clock");
                    timerRef.stop();
                    appState.setMode(AppMode::CLOCK);
                }
            }
        }
        break;
    }

    case AppMode::ANIMATION:
        if (event == BUTTON_EVENT_SINGLE_CLICK) {
            // Possibly cycle mode
            appState.cycleMode();
            Serial.println("Mode changed (animation -> next).");
        }
        // Double click does nothing in ANIMATION
        // Long press does nothing
        break;

    case AppMode::NOTIFICATION:
        // Could ignore all button events, or let user dismiss the notification
        if (event == BUTTON_EVENT_SINGLE_CLICK) {
            Serial.println("Dismiss notification, returning to CLOCK");
            appState.setMode(AppMode::CLOCK);
        }
        // double/long press might do nothing
        break;

    case AppMode::DIALOGUE:
        // Suppose single-click means "yes," double-click means "no," long press ignored
        if (event == BUTTON_EVENT_SINGLE_CLICK) {
            Serial.println("User answered YES in dialogue. Exiting dialogue...");
            appState.setMode(AppMode::CLOCK);
        }
        else if (event == BUTTON_EVENT_DOUBLE_CLICK) {
            Serial.println("User answered NO in dialogue. Exiting dialogue...");
            appState.setMode(AppMode::CLOCK);
        }
        // no-op on long press
        break;
    }
}

// Local button FSM function
void ButtonState::setState(AppState newState)
{
    currentState = newState;

    switch (currentState)
    {
    case STATE_IDLE:
        led.setLEDState(LEDState::IDLE);
        display.writeAlignedText("Idle State");
        break;

    case STATE_CYCLE_MODE:
        led.setLEDState(LEDState::IDLE);
        display.writeAlignedText("Configuration Mode");
        delay(2000);
        break;

    case STATE_RESETTING:
        led.setLEDState(LEDState::IDLE);
        display.writeAlignedText("Resetting...");
        break;

    default:
        break;
    }
}
