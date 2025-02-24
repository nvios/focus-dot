#include "states/LEDState.h"

LEDStateManager::LEDStateManager()
    : _currentLEDState(LEDState::IDLE), customR(0), customG(24), customB(0) {}

void LEDStateManager::setState(LEDState newState)
{
    _currentLEDState = newState;
}

LEDState LEDStateManager::getState() const
{
    return _currentLEDState;
}

void LEDStateManager::setCustomColor(uint8_t R, uint8_t G, uint8_t B)
{
    customR = R;
    customG = G;
    customB = B;
}