#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Adafruit_NeoPixel.h>
#include <functional>
#include "configurations/Config.h"

enum class LEDState
{
    IDLE,
    SPIN_RAINBOW,
    SPIN_GREEN,
    SPIN_YELLOW,
    SPIN_RED,
    PULSE_RED,
    PULSE_BLUE,
    SOLID_BLUE
};

class LED
{
public:
    LED(uint8_t pin = LED_PIN, uint16_t numPixels = LED_COUNT);
    void begin();
    void setLEDState(LEDState newState);
    void update();
    LEDState getLEDState() const { return _currentLEDState; }
    void displaySolidColor(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness);

private:
    Adafruit_NeoPixel _ring;
    LEDState _currentLEDState;
    unsigned long _stateStartTime;
    static const unsigned long EVENT_ANIMATION_MS;
    static const unsigned long VOC_ANIMATION_MS;
    static const unsigned long VOC_RED_PULSE_MS;
    uint8_t _activeLed;
    unsigned long _lastTailUpdate;
    uint8_t _pulseVal;
    bool _pulseRising;
    void animateTailFade(std::function<uint32_t(int)> colorFunc, uint8_t tailLen = 9, unsigned long stepTime = 120);
    void animateRainbowTail();
    void animateSolidTail(uint8_t R, uint8_t G, uint8_t B);
    void animatePulse(uint8_t R, uint8_t G, uint8_t B);
};

#endif