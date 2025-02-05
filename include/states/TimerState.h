#ifndef TIMER_STATE_H
#define TIMER_STATE_H

#include "State.h"
#include "hardware/Display.h"
#include "hardware/LED.h"
#include "configurations/Config.h"

/* class TimerState : public State {
public:
    //TimerState(DisplayDriver& display, LEDDriver& ledDriver);
    void enter() override;
    void update() override;
    void handleInput() override;
    void exit() override;

    void startTimer(unsigned long duration);
    void pauseTimer();
    void resetTimer();

private:
    //DisplayDriver& _display;
    //LEDDriver& _ledDriver;
    unsigned long _timerStartTime;
    unsigned long _remainingTime;
    bool _isRunning;
    void _updateDisplay();
}; */

#endif