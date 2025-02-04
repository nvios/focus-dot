#include "states/StateManager.h"

/* StateManager::StateManager() : _currentState(nullptr) {}

void StateManager::init(State *initialState)
{
    _currentState = initialState;
    _currentState->enter();
}

void StateManager::update()
{
    if (_currentState)
    {
        _currentState->update();
    }
}

void StateManager::handleInput(ButtonDriver &buttons)
{
    if (buttons.wasClicked(BTN_MODE))
    {
        // Example: Toggle between ClockState and TimerState
        if (_currentState == &clockState)
        {
            changeState(&timerState);
        }
        else
        {
            changeState(&clockState);
        }
    }
}

void StateManager::changeState(State *newState)
{
    if (_currentState)
    {
        _currentState->exit();
    }
    _currentState = newState;
    _currentState->enter();
} */