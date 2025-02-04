#include "controllers/network/MQTTController.h"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_KEY);
Adafruit_MQTT_Subscribe eventFeed(&mqtt, MQTT_USERNAME MQTT_FEED);

String eventTitle = "";
String eventStart = "";
String eventEnd = "";
bool showEvent = false, eventDisplayed = false;
unsigned long eventDisplayStart = 0;

bool mqttConnect(int maxAttempts)
{
    int attempts = 0;
    while (attempts < maxAttempts)
    {
        Serial.print("Attempting MQTT connection (try #");
        Serial.print(attempts + 1);
        Serial.println(")...");

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
    return false;
}

void parseEventJSON(const char *payload)
{
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err)
    {
        Serial.print("JSON parse failed: ");
        Serial.println(err.f_str());
        return;
    }
}