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
    : _presetNumber(0),
      _resetModeEnteredTime(0),
      _ignoreNextClick(false),
      _currentState(AppState::STATE_IDLE),
      _led(led),
      _display(display),
      _wifiController(wifi),
      _clock(clock),
      _appState(appState)
{
}

void ButtonState::handleEvent(ButtonEvent event)
{
    if (event == ButtonEvent::RESET_HOLD)
    {
        _appState.setDialogueMessage("Click to go back\n\nDouble click to reset", DialogueType::RESET);
        _appState.setMode(AppMode::DIALOGUE);
        _display.writeAlignedText("Click to go back\n\nDouble click to reset", DISPLAY_WIDTH, DISPLAY_HEIGHT);
        _led.setLEDState(LEDState::PULSE_BLUE);
        return;
    }

    switch (_appState.getMode())
    {
    case AppMode::CLOCK:
    {
        if (event == ButtonEvent::SINGLE_CLICK)
        {
            _appState.setDialogueMessage("", DialogueType::TIMER_START);
            _appState.setMode(AppMode::DIALOGUE);
            _led.setLEDState(LEDState::PULSE_BLUE);
            _display.drawTimerDialogue(_appState.getTimer());
        }
        break;
    }

    case AppMode::TIMER:
    {
        auto &timerRef = _appState.getTimer();
        if (!timerRef.isRunning() && !timerRef.isPaused())
        {
            if (event == ButtonEvent::DOUBLE_CLICK)
            {
                timerRef.start();
                _appState.setMode(AppMode::TIMER);
                _led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == ButtonEvent::SINGLE_CLICK)
            {
                _appState.setMode(AppMode::ANIMATION);
                _led.setLEDState(LEDState::IDLE);
            }
        }
        else if (timerRef.isRunning())
        {
            if (event == ButtonEvent::SINGLE_CLICK)
            {
                timerRef.pause();
                _appState.setDialogueMessage("Click to resume\n\nDouble click to stop", DialogueType::TIMER_PAUSED);
                _appState.setMode(AppMode::DIALOGUE);
                _display.writeAlignedText(_appState.getDialogueMessage(), DISPLAY_WIDTH, DISPLAY_HEIGHT);
                _led.setLEDState(LEDState::PULSE_BLUE);
            }
        }
        else if (timerRef.isPaused())
        {
            if (event == ButtonEvent::SINGLE_CLICK)
            {
                timerRef.resume();
                _appState.setMode(AppMode::TIMER);
                _led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == ButtonEvent::DOUBLE_CLICK)
            {
                timerRef.stop();
                _appState.setMode(AppMode::CLOCK);
                _led.setLEDState(LEDState::IDLE);
            }
        }
        break;
    }

    case AppMode::ANIMATION:
    {
        if (event == ButtonEvent::SINGLE_CLICK)
        {
            _appState.setMode(AppMode::CLOCK);
            _led.setLEDState(LEDState::IDLE);
        }
        break;
    }

    case AppMode::DIALOGUE:
    {
        DialogueType type = _appState.getDialogueType();
        if (type == DialogueType::TIMER_START)
        {
            if (event == ButtonEvent::DOUBLE_CLICK)
            {
                _appState.getTimer().start();
                _appState.setMode(AppMode::TIMER);
                _led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == ButtonEvent::LONG_PRESS)
            {
                _appState.getTimer().cyclePreset();
                _appState.setDialogueMessage("", DialogueType::TIMER_START);
                _display.drawTimerDialogue(_appState.getTimer());
            }
            else if (event == ButtonEvent::SINGLE_CLICK)
            {
                _appState.setMode(AppMode::ANIMATION);
                _led.setLEDState(LEDState::IDLE);
            }
            else
            {
                _led.setLEDState(LEDState::PULSE_BLUE);
            }
        }
        else if (type == DialogueType::TIMER_PAUSED)
        {
            if (event == ButtonEvent::SINGLE_CLICK)
            {
                _appState.getTimer().resume();
                _appState.setMode(AppMode::TIMER);
                _led.setLEDState(LEDState::PULSE_RED);
            }
            else if (event == ButtonEvent::DOUBLE_CLICK)
            {
                _appState.getTimer().stop();
                _appState.setMode(AppMode::CLOCK);
                _led.setLEDState(LEDState::IDLE);
            }
        }
        else if (type == DialogueType::RESET)
        {
            if (event == ButtonEvent::SINGLE_CLICK)
            {
                _appState.setMode(AppMode::CLOCK);
                _led.setLEDState(LEDState::IDLE);
            }
            else if (event == ButtonEvent::DOUBLE_CLICK)
            {
                _display.writeAlignedText("Resetting your device...", DISPLAY_WIDTH, DISPLAY_HEIGHT);
                delay(2000);
                ESP.restart();
            }
        }
        break;
    }

    case AppMode::NOTIFICATION:
    {
        if (event == ButtonEvent::SINGLE_CLICK)
        {
            _appState.setMode(AppMode::CLOCK);
            _led.setLEDState(LEDState::IDLE);
        }
        break;
    }
    }
}

void ButtonState::setState(AppState newState)
{
    _currentState = newState;
}