#include "hardware/VOC.h"

VOC::VOC(LED& led)
    : _led(led), lastVocUpdate(0), _vocVal(0)
{
}

void VOC::begin()
{
    if (!_sgp40.begin(10000)) {
        // Handle sensor initialization failure
    }
}

int VOC::readVOC()
{
    unsigned long now = millis();

    // Update the reading every 4 seconds
    if (now - lastVocUpdate >= 4000)
    {
        lastVocUpdate = now;
        _vocVal = _sgp40.getVoclndex();

        // Threshold-based LED behavior
        if (_vocVal < 100) {
            _led.setLEDState(LEDState::VOC_GREEN);
        } else if (_vocVal < 180) {
            _led.setLEDState(LEDState::VOC_YELLOW);
        } else {
            _led.setLEDState(LEDState::VOC_RED);
        }
    }
    return _vocVal;
}