#ifndef NTP_CONTROLLER_H
#define NTP_CONTROLLER_H

#include <Arduino.h>
#include "configurations/Config.h"
#include "hardware/Display.h"

class NTPController {
public:
    NTPController(Display &display);
    bool begin(const char* ntpServer);

private:
    void setupTime(const char* ntpServer);
    Display &display;
};

#endif