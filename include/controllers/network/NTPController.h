#ifndef NTP_CONTROLLER_H
#define NTP_CONTROLLER_H

#include <Arduino.h>
#include "configurations/Config.h"

void setupTime(const char* ntpServer);

bool syncTime(unsigned long timeoutMs);

#endif