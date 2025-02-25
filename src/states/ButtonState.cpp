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
    : led(led),
      display(display),
      wifiController(wifi),
      clock(clock),
      appState(appState)
{
}

void ButtonState::handleEvent(ButtonEvent event)
{
    if (event == BUTTON_EVENT_RESET_HOLD)
    {
        appState.setDialogueMessage("Click to go back\n\nDouble click to reset", DialogueType::RESET);
        appState.setMode(AppMode::DIALOGUE);
        display.writeAlignedText("Click to go back\n\nDouble click to reset", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        led.setLEDState(LEDState::IDLE);
        return;
    }

    switch (appState.getMode())
    {
    case AppMode::CLOCK:
    {
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            auto &timerRef = appState.getTimer();
            int preset = timerRef.getCurrentPresetIndex();
            String msg = "Double click to start timer\n\nP-0" + String(preset + 1) + ": " +
                         String(timerRef.getCurrentPresetDuration() / 60) + " min.";
            appState.setDialogueMessage(msg, DialogueType::TIMER_START);
            appState.setMode(AppMode::DIALOGUE);
            led.setLEDState(LEDState::PULSE_BLUE);
            display.writeAlignedText(msg, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        }
        else if (event == BUTTON_EVENT_DOUBLE_CLICK)
        {
            wifiController.begin(WIFI_SSID, WIFI_PASS);
        }
        break;
    }

    case AppMode::TIMER:
    {
        auto &timerRef = appState.getTimer();
        if (!timerRef.isRunning() && !timerRef.isPaused())
        {
            if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                timerRef.start();
                appState.setMode(AppMode::TIMER);
                led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                appState.setMode(AppMode::ANIMATION);
                led.setLEDState(LEDState::IDLE);
            }
        }
        else if (timerRef.isRunning())
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                timerRef.pause();
                appState.setDialogueMessage("Click to resume\n\nDouble click to stop", DialogueType::TIMER_PAUSED);
                appState.setMode(AppMode::DIALOGUE);
                display.writeAlignedText(appState.getDialogueMessage(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
                led.setLEDState(LEDState::PULSE_BLUE);
            }
        }
        else if (timerRef.isPaused())
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                timerRef.resume();
                appState.setMode(AppMode::TIMER);
                led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                timerRef.stop();
                appState.setMode(AppMode::CLOCK);
                led.setLEDState(LEDState::IDLE);
            }
        }
        break;
    }

    case AppMode::ANIMATION:
    {
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            appState.setMode(AppMode::CLOCK);
            led.setLEDState(LEDState::IDLE);
        }
        break;
    }

    case AppMode::DIALOGUE:
    {
        DialogueType type = appState.getDialogueType();
        if (type == DialogueType::TIMER_START)
        {
            if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                appState.getTimer().start();
                appState.setMode(AppMode::TIMER);
                led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == BUTTON_EVENT_LONG_PRESS)
            {
                int preset = appState.getTimer().cyclePreset();
                String msg = "Double click to start timer\n\nP-0" + String(preset + 1) + ": " +
                             String(appState.getTimer().getCurrentPresetDuration() / 60) + " min.";
                appState.setDialogueMessage(msg, DialogueType::TIMER_START);
                display.writeAlignedText(msg, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            }
            else if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                appState.setMode(AppMode::ANIMATION);
                led.setLEDState(LEDState::IDLE);
            }
            else
            {
                // Maintain PULSE_BLUE if no recognized event.
                led.setLEDState(LEDState::PULSE_BLUE);
            }
        }
        else if (type == DialogueType::TIMER_PAUSED)
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                appState.getTimer().resume();
                appState.setMode(AppMode::TIMER);
                led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                appState.getTimer().stop();
                appState.setMode(AppMode::CLOCK);
                led.setLEDState(LEDState::IDLE);
            }
        }
        else if (type == DialogueType::RESET)
        {
            if (event == BUTTON_EVENT_SINGLE_CLICK)
            {
                appState.setMode(AppMode::CLOCK);
                led.setLEDState(LEDState::IDLE);
            }
            else if (event == BUTTON_EVENT_DOUBLE_CLICK)
            {
                ESP.restart();
            }
        }
        break;
    }

    case AppMode::NOTIFICATION:
    {
        if (event == BUTTON_EVENT_SINGLE_CLICK)
        {
            appState.setMode(AppMode::CLOCK);
            led.setLEDState(LEDState::IDLE);
        }
        break;
    }
    }
}