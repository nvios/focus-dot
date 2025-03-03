#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <WiFi.h>
#include "hardware/Display.h"

enum class WiFiStatus
{
    CONNECTED,
    CONNECTION_TIMEOUT,
    INVALID_CREDENTIALS,
    UNKNOWN_ERROR
};

class WiFiController
{
public:
    WiFiController(Display &display);
    WiFiStatus begin(const char *ssid, const char *password, unsigned long timeout = 20000);
    bool isConnected() const;
    void disconnect();
    String getLocalIP() const;

private:
    Display &_display;
    WiFiStatus _status;
};

#endif