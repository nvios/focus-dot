#include "states/State.h"

State::State()
    : currentMode(AppMode::CLOCK) {}

void State::cycleMode()
{
    if (currentMode == AppMode::CLOCK)
        currentMode = AppMode::TIMER;
    else if (currentMode == AppMode::TIMER)
        currentMode = AppMode::ANIMATION;
    else if (currentMode == AppMode::ANIMATION)
        currentMode = AppMode::CLOCK;
}

AppMode State::getMode() const { return currentMode; }
void State::setMode(AppMode mode) { currentMode = mode; }
TimerState& State::getTimer() { return timer; }