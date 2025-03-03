#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>
#include "configurations/Config.h"
#include "states/State.h"
#include "hardware/LED.h"
#include "hardware/Display.h"

class MQTTController
{
public:
    MQTTController(State &appStateRef, LED &ledRef, Display &displayRef);
    void begin(int maxAttempts);
    void checkConnection(int maxAttempts);
    void update(unsigned long now);

private:
    bool mqttConnect(int maxAttempts);
    void parseEventJSON(const char *payload);

    State &appState;
    LED &led;
    Display &display;
    WiFiClient client;
    Adafruit_MQTT_Client mqtt;
    Adafruit_MQTT_Subscribe eventFeed;

    String eventTitle, eventStart, eventEnd, message;
    bool showEvent = false, eventDisplayed = false;
    unsigned long eventDisplayStart = 0;
    unsigned long _lastPingTime = 0;
};

#endif