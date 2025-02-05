#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Adafruit_NeoPixel.h>
#include <functional>
#include "configurations/Config.h"

// Define LEDState enum if not already defined elsewhere
enum class LEDState
{
    IDLE,
    EVENT_RAINBOW,
    VOC_GREEN,
    VOC_YELLOW,
    VOC_RED,
    VOC_RED_PULSE
    // Add other states as needed
};

class LED
{
public:
    /**
     * Constructor.
     * @param pin       Pin number for NeoPixel data.
     * @param numPixels Number of NeoPixels.
     */
    LED(uint8_t pin = LED_PIN, uint16_t numPixels = LED_COUNT);

    /**
     * Initializes the LED strip.
     */
    void begin();

    /**
     * Sets the LED state.
     * @param newState LEDState enum value.
     */
    void setLEDState(LEDState newState);

    /**
     * Updates the LEDs based on the current state.
     * Call this in loop().
     */
    void update();

private:
    Adafruit_NeoPixel _ring;
    LEDState _currentLEDState;
    unsigned long _stateStartTime;

    // Animation durations in milliseconds
    static const unsigned long EVENT_ANIMATION_MS;
    static const unsigned long VOC_ANIMATION_MS;
    static const unsigned long VOC_RED_PULSE_MS;

    // Tail animation variables
    uint8_t _activeLed;
    unsigned long _lastTailUpdate;

    // Red pulse animation variables
    uint8_t _pulseVal;
    bool _pulseRising;

    /**
     * Helper function to perform tail fade animations.
     * @param colorFunc Function to determine the color based on LED index.
     * @param tailLen Length of the tail.
     * @param stepTime Time between animation steps.
     */
    void animateTailFade(std::function<uint32_t(int)> colorFunc, uint8_t tailLen = 9, unsigned long stepTime = 120);

    /**
     * Animates a rainbow tail.
     */
    void animateRainbowTail();

    /**
     * Animates a solid color tail.
     * @param R Red component.
     * @param G Green component.
     * @param B Blue component.
     */
    void animateSolidTail(uint8_t R, uint8_t G, uint8_t B);

    /**
     * Animates a red pulse effect.
     */
    void animateRedPulse();
};

#endif // LED_DRIVER_H