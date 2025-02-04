#include "controllers/network/WiFiController.h"

WiFiController::WiFiController(Display &display) : display(display) {}

bool WiFiController::begin(const char* ssid, const char* password) {
    display.writeText("Spinning up the connection...");

    WiFi.begin(ssid, password);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - start > 10000) { // 10-second timeout
            display.writeText("Wi-Fi connection failed!");
            return false;
        }
        delay(500);
        Serial.print(".");
    }

    display.writeText("Wi-Fi Connected!");
    return true;
}