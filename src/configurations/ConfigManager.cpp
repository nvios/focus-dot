#include "configurations/ConfigManager.h"

DeviceConfig ConfigManager::config = { "", "", 3600, 0, "", 1883, "", "" };

void ConfigManager::load() {
    Preferences preferences;
    preferences.begin("config", false);

    strcpy(config.wifiSSID, preferences.getString("wifiSSID", "").c_str());
    strcpy(config.wifiPass, preferences.getString("wifiPass", "").c_str());
    config.utcOffset = preferences.getInt("utcOffset", 3600);
    config.daylightOffset = preferences.getInt("daylightOffset", 0);
    strcpy(config.mqttServer, preferences.getString("mqttServer", "").c_str());
    config.mqttPort = preferences.getInt("mqttPort", 1883);
    strcpy(config.mqttUsername, preferences.getString("mqttUsername", "").c_str());
    strcpy(config.mqttKey, preferences.getString("mqttKey", "").c_str());
    
    preferences.end();
}

void ConfigManager::save() {
    Preferences preferences;
    preferences.begin("config", false);

    preferences.putString("wifiSSID", config.wifiSSID);
    preferences.putString("wifiPass", config.wifiPass);
    preferences.putInt("utcOffset", config.utcOffset);
    preferences.putInt("daylightOffset", config.daylightOffset);
    preferences.putString("mqttServer", config.mqttServer);
    preferences.putInt("mqttPort", config.mqttPort);
    preferences.putString("mqttUsername", config.mqttUsername);
    preferences.putString("mqttKey", config.mqttKey);
    
    preferences.end();
}

void ConfigManager::reset() {
    Preferences preferences;
    preferences.begin("config", false);
    preferences.clear();
    preferences.end();
}
