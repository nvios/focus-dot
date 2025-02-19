#include "controllers/network/NTPController.h"
#include "configurations/ConfigManager.h"


void setupTime(const char* ntpServer) {
    configTime(ConfigManager::config.utcOffset, 
               ConfigManager::config.daylightOffset,
               ntpServer);
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