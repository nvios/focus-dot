#ifndef LED_STATE_H
#define LED_STATE_H

#include <stdint.h>

enum class LEDState
{
    OFF,
    IDLE,
    SPIN_RAINBOW,
    SPIN_GREEN,
    SPIN_YELLOW,
    SPIN_RED,
    PULSE_RED,
    PULSE_BLUE
};

class LEDStateManager {
public:
    LEDStateManager();
    void setState(LEDState newState);
    LEDState getState() const;
    void setCustomColor(uint8_t R, uint8_t G, uint8_t B);
    uint8_t customR, customG, customB;

private:
    LEDState _currentLEDState;
};

#endif