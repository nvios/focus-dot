#include "controllers/network/WiFiController.h"

WiFiController::WiFiController(Display &display) : display(display) {}

bool WiFiController::begin(const char *ssid, const char *password)
{
    display.writeAlignedText("Connecting to your Wi-Fi...", 128, 64, 0, 0, 2, true, true, true, VALIGN_TOP, HALIGN_CENTER);

    WiFi.begin(ssid, password);

    unsigned long start = millis();
    unsigned long lastUpdate = millis();
    int progress = 5;
    display.drawProgressBar(10, 42, 108, 8, progress);
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - lastUpdate > 300)
        {
            progress = progress > 50 ? (progress > 75 ? 75 : progress += 1) : progress += 5;
            display.drawProgressBar(10, 42, 108, 8, progress);
            lastUpdate = millis();
        }
        if (millis() - start > 20000)
        {
            return false;
        }
    }
    Serial.print("Wi-Fi Connected!");
    return true;
}