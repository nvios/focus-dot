#include "controllers/network/MQTTController.h"

MQTTController::MQTTController(State &appStateRef, LED &ledRef, Display &displayRef)
    : appState(appStateRef),
      led(ledRef),
      display(displayRef),
      mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_KEY),
      eventFeed(&mqtt, MQTT_USERNAME MQTT_FEED)
{
}

void MQTTController::begin(int maxAttempts)
{
    display.writeAlignedText("Syncing your events...");
    mqtt.subscribe(&eventFeed);
    if (!mqttConnect(maxAttempts))
    {
        display.writeAlignedText("MQTT connection failed :(");
        Serial.println("MQTT connection failed; continuing anyway.");
    }
}

void MQTTController::checkConnection(int maxAttempts)
{
    if (!mqtt.connected())
    {
        mqttConnect(maxAttempts);
        if (mqtt.connected())
            mqtt.subscribe(&eventFeed);
    }
}

void MQTTController::update(unsigned long now)
{
    if (!mqtt.connected())
        return;
    Adafruit_MQTT_Subscribe *sub = mqtt.readSubscription(50);
    if (sub == &eventFeed)
    {
        parseEventJSON((char *)eventFeed.lastread);
        led.setLEDState(LEDState::EVENT_RAINBOW);
        eventDisplayStart = now;
        eventDisplayed = true;
        if (message == "")
            display.drawEvent(eventTitle, eventStart, eventEnd, 1);
        else
            display.writeAlignedText(message.c_str());
        appState.setMode(AppMode::NOTIFICATION);
    }

    if (appState.getMode() == AppMode::NOTIFICATION && eventDisplayed)
    {
        if (now - eventDisplayStart >= EVENT_DISPLAY_MS)
        {
            led.setLEDState(LEDState::IDLE);
            appState.setMode(AppMode::CLOCK);
            eventDisplayed = false;
            eventTitle = eventStart = eventEnd = "";
        }
    }
}

bool MQTTController::mqttConnect(int maxAttempts)
{
    int attempts = 0;
    while (attempts < maxAttempts)
    {
        Serial.print("Attempting MQTT connection (try #");
        Serial.print(attempts + 1);
        Serial.println(")");
        int8_t ret = mqtt.connect();
        if (ret == 0)
        {
            Serial.println("MQTT Connected!");
            return true;
        }
        else
        {
            Serial.print("MQTT connect failed: ");
            Serial.println(mqtt.connectErrorString(ret));
            mqtt.disconnect();
            delay(5000);
        }
        attempts++;
    }
    Serial.println("Failed to connect to MQTT after max attempts. Continuing without MQTT.");
    display.writeAlignedText("Event sync failed :(");
    return false;
}

void MQTTController::parseEventJSON(const char *payload)
{
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err)
    {
        Serial.println("JSON parse failed");
        return;
    }
    eventTitle = doc["subject"] | "Unknown Event";
    eventStart = doc["startTime"] | "";
    eventEnd = doc["endTime"] | "";
    message = doc["message"] | "";
}