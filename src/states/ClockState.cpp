#include "states/ClockState.h"

/* ClockState::ClockState(DisplayDriver &display, NTPClient &timeClient)
    : _display(display), _timeClient(timeClient), _lastUpdate(0) {}

void ClockState::enter()
{
    _display.clear();
    _lastUpdate = millis();
}

void ClockState::update()
{
    if (_ntpClient.isTimeSynced())
    {
        String time = _ntpClient.getFormattedTime();
        _display.drawText(time.c_str(), 10, 20);
    }
    else
    {
        _display.drawText("Syncing...", 10, 20);
    }
}

void ClockState::handleInput()
{
    // Handle button presses to switch states (e.g., BTN_LEFT pressed)
}

void ClockState::exit()
{
    _display.clear();
} */