#include "states/LEDState.h"

LEDStateManager::LEDStateManager()
    : _currentLEDState(LEDState::IDLE), customR(0), customG(0), customB(0) {}

void LEDStateManager::setState(LEDState newState)
{
    _currentLEDState = newState;
}

LEDState LEDStateManager::getState() const
{
    return _currentLEDState;
}

void LEDStateManager::setCustomColor(uint8_t r, uint8_t g, uint8_t b)
{
    customR = r;
    customG = g;
    customB = b;
}