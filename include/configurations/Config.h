#ifndef CONFIG_H
#define CONFIG_H

// Wi-Fi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

// MQTT
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_USERNAME "luca_bontempi"
#define MQTT_KEY "aio_xJum97iGoWDd4nJf7EGAreKE2WeL"
#define MQTT_FEED "/feeds/calendar"
#define MQTT_RETRY_FREQUENCY_MS 3600000 // 1 hour

// NTP
#define NTP_SERVER "pool.ntp.org"
#define UTC_OFFSET 3600
#define DAYLIGHT_OFFSET 0

// OLED
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define SDA_PIN 8
#define SCL_PIN 9
#define OLED_RESET -1

// LED
#define LED_COUNT 16
#define LED_PIN 4

// Button
#define BUTTON_PIN 6

// Events
#define EVENT_DISPLAY_MS 60000 // 1 minute

#endif
