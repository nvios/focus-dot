#include "configurations/ConfigManager.h"

DeviceConfig ConfigManager::config = {
    "",       // wifiSSID
    "",       // wifiPASS
    0,        // utcOffset
    0         // daylightOffset
};

void ConfigManager::load() {
    // mock example
    // read from EEPROM or Preferences
    // In real code, you parse stored values into config
    // e.g. config.wifiSSID = ...
    // For now just do:
    config.wifiSSID = "";
    config.wifiPASS = "";
    config.utcOffset = 3600;      // example
    config.daylightOffset = 0;    // example
}

void ConfigManager::save() {
    // again, mock example
    // write config fields to EEPROM or Preferences
    // e.g. preferences.putString("ssid", config.wifiSSID);
}