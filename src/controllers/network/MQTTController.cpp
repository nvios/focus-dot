#include "controllers/network/MQTTController.h"

MQTTController::MQTTController(State &appStateRef, LED &ledRef, Display &displayRef)
    : appState(appStateRef),
      led(ledRef),
      display(displayRef),
      mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_KEY),
      eventFeed(&mqtt, MQTT_USERNAME MQTT_FEED)
{
    // Set a shorter keep-alive interval (in seconds)
    mqtt.setKeepAliveInterval(30);
}

void MQTTController::begin(int maxAttempts)
{
    display.writeAlignedText("Syncing events...", 128, 64, 0, 0, 2, true, true, true, VALIGN_TOP, HALIGN_CENTER);
    mqtt.subscribe(&eventFeed);
    if (!mqttConnect(maxAttempts))
    {
        display.writeAlignedText("MQTT connection failed :(");
        Serial.println("MQTT connection failed; continuing anyway.");
    }
    _lastPingTime = millis();
}

void MQTTController::checkConnection(int maxAttempts)
{
    unsigned long now = millis();

    // If connected, check if we need to ping (no blocking operations)
    if (mqtt.connected())
    {
        // Send a ping every 25 seconds to keep the connection alive
        if (now - _lastPingTime > 25000)
        {
            mqtt.ping(); // Don't check result to avoid blocking
            _lastPingTime = now;
        }
    }
    // If not connected, try to reconnect (with minimal attempts)
    else
    {
        if (mqttConnect(maxAttempts))
        {
            mqtt.subscribe(&eventFeed);
            _lastPingTime = now;
        }
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
        if (message == "" && eventStart == "" && eventEnd == "" && eventTitle == "")
        {
            return;
        }
        led.setLEDState(LEDState::SPIN_RAINBOW);
        eventDisplayStart = now;
        eventDisplayed = true;
        if (message == "")
        {
            display.drawEvent(eventTitle, eventStart, eventEnd, 1);
        }
        else
        {
            display.writeAlignedText(message.c_str());
        }
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
    unsigned long start = millis();
    unsigned long lastUpdate = millis();
    int progress = 75;
    display.drawProgressBar(10, 42, 108, 8, progress);

    // Check WiFi first
    if (WiFi.status() != WL_CONNECTED)
    {
        return false;
    }

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
        if (millis() - start > 5000)
        {
            Serial.print("MQTT connect failed: ");
            Serial.println(mqtt.connectErrorString(ret));
            mqtt.disconnect();
        }
        if (millis() - lastUpdate > 1000)
        {
            progress = progress > 90 ? 90 : progress += 1;
            display.drawProgressBar(10, 42, 108, 8, progress);
            lastUpdate = millis();
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