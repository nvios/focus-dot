#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <WiFi.h>
#include "hardware/Display.h"

class WiFiController {
public:
    WiFiController(Display &display);
    bool begin(const char* ssid, const char* password);

private:
    Display &display;
};

#endif