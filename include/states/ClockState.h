#ifndef CLOCK_STATE_H
#define CLOCK_STATE_H

#include "State.h"
#include "Config.h"
#include <WiFi.h>
#include "controllers/network/NTPController.h"

/* class ClockState : public State
{
public:
    ClockState(DisplayDriver &display, NTPClient &timeClient);
    void enter() override;
    ClockState(DisplayDriver& display, NetworkNTPClient& ntpClient);
    void update() override;
    void handleInput() override;
    void exit() override;

private:
    DisplayDriver &_display;
    NTPClient &_timeClient;
    NetworkNTPClient& _ntpClient;
    unsigned long _lastUpdate;
}; */

#endif