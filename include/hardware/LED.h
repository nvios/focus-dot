#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Adafruit_NeoPixel.h>
#include <array>
#include "configurations/Config.h"
#include "states/LEDState.h"

class LED
{
public:
    LED(uint8_t pin = LED_PIN, uint16_t numPixels = LED_COUNT);
    void begin();
    void setLEDState(LEDState newState);
    LEDState getLEDState() const;
    void update();
    void displaySolidColor(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
    void setCustomColor(uint8_t r, uint8_t g, uint8_t b);

private:
    Adafruit_NeoPixel _ring;
    LEDStateManager _stateManager;

    // Variables used for animation effects
    unsigned long _stateStartTime;
    uint8_t _activeLed;
    unsigned long _lastTailUpdate;
    uint8_t _pulseVal;
    bool _pulseRising;

    // Constants for animation durations
    static const unsigned long EVENT_ANIMATION_MS;
    static const unsigned long VOC_ANIMATION_MS;
    static const unsigned long VOC_RED_PULSE_MS;

    // Animation functions
    void animateRainbowEffect();                           // full-strip rainbow (boot up)
    void animateTailFade(uint8_t r, uint8_t g, uint8_t b); // tail fade effect (spinning)
    void animatePulse(uint8_t r, uint8_t g, uint8_t b);    // pulse effect with increased speed
};

#endif