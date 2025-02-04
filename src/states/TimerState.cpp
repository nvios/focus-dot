#include "states/TimerState.h"

/*TimerState::TimerState(DisplayDriver &display, LEDDriver &ledDriver)
    : _display(display), _ledDriver(ledDriver),
      _timerStartTime(0), _remainingTime(0), _isRunning(false) {}

void TimerState::enter()
{
    _display.clear();
    _remainingTime = DEFAULT_TIMER_DURATION;
    _updateDisplay();
    _ledDriver.startAnimation(); // Start LED animation
}

void TimerState::update()
{
    if (_isRunning)
    {
        unsigned long elapsed = millis() - _timerStartTime;
        if (elapsed >= _remainingTime)
        {
            _isRunning = false;
            _remainingTime = 0;
            _ledDriver.setAlertAnimation(); // Switch to alert mode
        }
        else
        {
            _remainingTime -= elapsed;
            _timerStartTime = millis();
        }
        _updateDisplay();
    }
    _ledDriver.update(); // Update LEDs
}

void TimerState::exit()
{
    _display.clear();
    _ledDriver.stopAnimation(); // Turn off LEDs
}

// Other methods (startTimer, pauseTimer, etc.) remain unchanged

void TimerState::handleInput()
{
    // Example: Use button presses to control the timer
    // if (ButtonDriver::isPressed(BTN_PAUSE)) pauseTimer();
}

void TimerState::startTimer(unsigned long duration)
{
    _remainingTime = duration;
    _timerStartTime = millis();
    _isRunning = true;
}

void TimerState::pauseTimer()
{
    _isRunning = false;
}

void TimerState::resetTimer()
{
    _isRunning = false;
    _remainingTime = DEFAULT_TIMER_DURATION;
    _updateDisplay();
}

void TimerState::_updateDisplay()
{
    unsigned long seconds = _remainingTime / 1000;
    char buf[10];
    snprintf(buf, sizeof(buf), "%02lu:%02lu", seconds / 60, seconds % 60);

    _display.clear();
    _display.drawText(buf, 10, 20);

    uint8_t progress = 100 - ((_remainingTime * 100) / DEFAULT_TIMER_DURATION);
    _display.drawProgressBar(progress);
}*/