#include "controllers/network/NTPController.h"
#include "configurations/ConfigManager.h"

NTPController::NTPController(Display &display) : display(display) {}


void NTPController::setupTime(const char* ntpServer) {
    configTime(ConfigManager::config.utcOffset, 
               ConfigManager::config.daylightOffset,
               ntpServer);
}

bool NTPController::begin(const char* ntpServer)
{
    setupTime(ntpServer);
    unsigned long start = millis();
    unsigned long lastUpdate = millis();
    int progress = 90;
    display.writeAlignedText("Winding the clock...", 128, 64, 0, 0, 2, true, true, true, VALIGN_TOP, HALIGN_CENTER);
    display.drawProgressBar(10, 42, 108, 8, progress);
    while (time(nullptr) < 10000)
    {
        if (millis() - start > 10000)
        {
            Serial.println("Time sync failed (timeout).");
            return false;
        }
        if (millis() - lastUpdate > 500)
        {
            progress = progress > 99 ? 100 : progress += 1;
            display.drawProgressBar(10, 42, 108, 8, progress);
            lastUpdate = millis();
        }
    }
    return true;
}