#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "TimerState.h"

enum class AppMode {
    CLOCK,
    TIMER,
    ANIMATION,
    NOTIFICATION,
    DIALOGUE
};

class State {
public:
    State();
    void cycleMode(); 
    AppMode getMode() const;
    void setMode(AppMode mode);
    TimerState& getTimer();

private:
    AppMode currentMode;
    TimerState timer;
};

#endif
