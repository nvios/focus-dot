#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

struct DeviceConfig {
    char wifiSSID[32];
    char wifiPass[64];
    int utcOffset;
    int daylightOffset;
    // future configs
};

class ConfigManager {
public:
    static DeviceConfig config;
    static void load();
    static void save();
};

#endif