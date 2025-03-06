#include "controllers/network/WiFiController.h"

WiFiController::WiFiController(Display &display)
    : _display(display), _status(WiFiStatus::UNKNOWN_ERROR) {}

WiFiStatus WiFiController::begin(const char *ssid, const char *password, unsigned long timeout)
{
    _display.writeAlignedText("Connecting to the Wi-Fi...",
                              DISPLAY_WIDTH, DISPLAY_HEIGHT,
                              0, 0, 2, true, true, true,
                              VALIGN_TOP, HALIGN_CENTER);

    // Check if credentials are provided
    if (!ssid || strlen(ssid) == 0)
    {
        _status = WiFiStatus::INVALID_CREDENTIALS;
        return _status;
    }

    WiFi.begin(ssid, password);

    unsigned long start = millis();
    unsigned long lastUpdate = millis();
    int progress = 5;
    _display.drawProgressBar(10, 42, 108, 8, progress);

    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - lastUpdate > 300)
        {
            progress = progress > 50 ? (progress > 75 ? 75 : progress += 1) : progress += 5;
            _display.drawProgressBar(10, 42, 108, 8, progress);
            lastUpdate = millis();
        }

        if (millis() - start > timeout)
        {
            _status = WiFiStatus::CONNECTION_TIMEOUT;
            return _status;
        }

        // Check for authentication failure
        if (WiFi.status() == WL_CONNECT_FAILED || WiFi.status() == WL_NO_SSID_AVAIL)
        {
            _status = WiFiStatus::INVALID_CREDENTIALS;
            return _status;
        }
    }

    Serial.println("Wi-Fi Connected! IP: " + WiFi.localIP().toString());
    _status = WiFiStatus::CONNECTED;
    return _status;
}

bool WiFiController::isConnected() const
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiController::disconnect()
{
    WiFi.disconnect();
    _status = WiFiStatus::UNKNOWN_ERROR;
}

String WiFiController::getLocalIP() const
{
    return WiFi.localIP().toString();
}