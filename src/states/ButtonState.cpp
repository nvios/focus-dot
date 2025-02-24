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
    // --- Part A: Local Button FSM transitions ---
    switch (currentState)
    {
    case STATE_IDLE:
        if (event == BUTTON_EVENT_RESET_HOLD)
        {
            Serial.println("Reset Hold: Entering Reset Mode");
            setState(STATE_RESET);
        }
        break;
    case STATE_CYCLE_MODE:
        if (event == BUTTON_EVENT_RESET_HOLD)
        {
            Serial.println("Reset from Config Mode...");
            setState(STATE_RESET);
        }
        break;
    case STATE_RESET:
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            Serial.println("Exiting Reset Mode");
            appState.setMode(AppMode::CLOCK);
            display.writeAlignedText("Clock Mode", DISPLAY_WIDTH, DISPLAY_HEIGHT);
            setState(STATE_IDLE);
        }
        else if (event == BUTTON_EVENT_DOUBLE_CLICK)
        {
            Serial.println("Performing Factory Reset");
            ESP.restart();
        }
        break;
    default:
        setState(STATE_IDLE);
        break;
    }

    // --- Part B: Global "mode" logic ---
    switch (appState.getMode())
    {
    case AppMode::CLOCK:
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            // Switch to timer start dialogue.
            auto &timerRef = appState.getTimer();
            int preset = appState.getTimer().getCurrentPresetIndex();
            String msg = "Double click to start\n\nP-" + String(preset + 1) + ": " +
                         String(appState.getTimer().getCurrentPresetDuration() / 60) + " min.";
            appState.setDialogueMessage(msg, DialogueType::TIMER_START);
            appState.setMode(AppMode::DIALOGUE);
            display.writeAlignedText(msg, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            Serial.println("Mode changed (clock -> dialogue for timer start).");
        }
        else if (event == BUTTON_EVENT_DOUBLE_CLICK)
        {
            Serial.println("Double Click: Refreshing Wi-Fi");
            wifiController.begin(WIFI_SSID, WIFI_PASS);
        }
        break;

    case AppMode::TIMER:
    {
        auto &timerRef = appState.getTimer();
        if (!timerRef.isRunning() && !timerRef.isPaused())
        {
            // Timer not started.
            if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                Serial.println("Starting timer");
                timerRef.start();
                appState.setMode(AppMode::TIMER);
            }
            else if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                Serial.println("Cycling to animation mode");
                appState.setMode(AppMode::ANIMATION);
            }
        }
        else if (timerRef.isRunning())
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                Serial.println("Pausing timer");
                timerRef.pause();
                appState.setDialogueMessage("Click to resume\nDouble click to stop", DialogueType::TIMER_PAUSED);
                appState.setMode(AppMode::DIALOGUE);
                display.writeAlignedText(appState.getDialogueMessage(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
            }
        }
        else if (timerRef.isPaused())
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                Serial.println("Resuming timer");
                timerRef.resume();
                appState.setMode(AppMode::TIMER);
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                Serial.println("Stopping timer, returning to clock");
                timerRef.stop();
                appState.setMode(AppMode::CLOCK);
            }
        }
        break;
    }

    case AppMode::ANIMATION:
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            appState.cycleMode();
            Serial.println("Mode changed (animation -> clock).");
        }
        break;

    case AppMode::NOTIFICATION:
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            Serial.println("Dismiss notification, returning to CLOCK");
            appState.setMode(AppMode::CLOCK);
        }
        break;

    case AppMode::DIALOGUE:
    {
        DialogueType type = appState.getDialogueType();
        if (type == DialogueType::TIMER_START)
        {
            // In TIMER_START dialogue, double-click starts timer,
            // long press cycles the preset, and single click goes to animation.
            if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                Serial.println("Timer dialogue (start): double click -> start timer");
                appState.getTimer().start();
                appState.setMode(AppMode::TIMER);
            }
            else if (event == BUTTON_EVENT_LONG_PRESS)
            {
                Serial.println("Timer dialogue (start): long press -> cycle timer preset");
                int preset = appState.getTimer().cyclePreset();
                String msg = "Double click to start\n\nP-" + String(preset + 1) + ": " +
                             String(appState.getTimer().getCurrentPresetDuration() / 60) + " min.";
                appState.setDialogueMessage(msg, DialogueType::TIMER_START);
                display.writeAlignedText(msg, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            }
            else if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                Serial.println("Timer dialogue (start): single click -> go to animation mode");
                appState.setMode(AppMode::ANIMATION);
            }
        }
        else if (type == DialogueType::TIMER_PAUSED)
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                Serial.println("Timer dialogue (paused): single click -> resume timer");
                appState.getTimer().resume();
                appState.setMode(AppMode::TIMER);
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                Serial.println("Timer dialogue (paused): double click -> stop timer");
                appState.getTimer().stop();
                appState.setMode(AppMode::CLOCK);
            }
        }
        else if (type == DialogueType::RESET)
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                Serial.println("Reset dialogue: single click -> cancel reset");
                appState.setMode(AppMode::CLOCK);
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                Serial.println("Reset dialogue: double click -> performing factory reset");
                ESP.restart();
            }
        }
        break;
    }
    }
}

void ButtonState::setState(AppState newState)
{
    currentState = newState;
    switch (currentState)
    {
    case STATE_IDLE:
        led.setLEDState(LEDState::IDLE);
        display.writeAlignedText("Idle State", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        break;
    case STATE_CYCLE_MODE:
        led.setLEDState(LEDState::IDLE);
        display.writeAlignedText("Dialogue Mode", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        delay(2000);
        break;
    case STATE_RESET:
        led.setLEDState(LEDState::IDLE);
        display.writeAlignedText("Click to go back\nDouble click to reset", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        appState.setDialogueMessage("Click to go back\nDouble click to reset", DialogueType::RESET);
        delay(1000); // Delay to help avoid spurious events.
        break;
    default:
        break;
    }
}