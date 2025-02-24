#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Adafruit_NeoPixel.h>
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
    void displaySolidColor(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness);
    void setCustomColor(uint8_t R, uint8_t G, uint8_t B);

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
    void animateRainbowEffect();           // full-strip rainbow (boot up)
    void animateTailFade(uint8_t R, uint8_t G, uint8_t B); // tail fade effect (spinning)
    void animatePulse(uint8_t R, uint8_t G, uint8_t B);      // pulse effect with increased speed
};

#endif