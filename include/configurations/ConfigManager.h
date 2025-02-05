#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <Preferences.h>

struct DeviceConfig {
    char wifiSSID[32];
    char wifiPass[64];
    int utcOffset;
    int daylightOffset;
    char mqttServer[64];
    int mqttPort;
    char mqttUsername[32];
    char mqttKey[64];
};

class ConfigManager {
public:
    static DeviceConfig config;
    static void load();
    static void save();
    static void reset(); // Factory reset for user settings
};

#endif