#ifndef NTP_CONTROLLER_H
#define NTP_CONTROLLER_H

#include <Arduino.h>
#include "Config.h"

void setupTime(const char* ntpServer, long utcOffset, int daylightOffset);

bool syncTime(unsigned long timeoutMs);

#endif