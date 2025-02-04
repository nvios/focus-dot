#include "controllers/network/NTPController.h"
#include <time.h>

void setupTime(const char* ntpServer, long utcOffset, int daylightOffset)
{
    configTime(utcOffset, daylightOffset, ntpServer);
}

bool syncTime(unsigned long timeoutMs)
{
    unsigned long start = millis();

    while (time(nullptr) < 10000)
    {
        if (millis() - start > timeoutMs)
        {
            Serial.println("Time sync failed (timeout).");
            return false;
        }
        delay(1000);
    }
    return true;
}