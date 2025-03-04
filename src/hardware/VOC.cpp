#include "hardware/VOC.h"

VOC::VOC(LED &led)
    : _led(led), lastVocUpdate(0), _vocVal(0), _lastVocRange(LEDState::SPIN_GREEN) {}

void VOC::begin()
{
    if (!_sgp40.begin(10000))
    {
        Serial.println("Failed to initialize SGP40 sensor!");
    }
}

int VOC::readVOC()
{
    unsigned long now = millis();
    if (now - lastVocUpdate >= 4000)
    {
        lastVocUpdate = now;
        _vocVal = _sgp40.getVoclndex();
        Serial.print("VOC: ");
        Serial.println(_vocVal);
        LEDState newState = (_vocVal < 100) ? LEDState::SPIN_GREEN : (_vocVal < 180) ? LEDState::SPIN_YELLOW
                                                                                     : LEDState::SPIN_RED;
        if (newState != _lastVocRange)
        {
            _led.setLEDState(newState);
            _lastVocRange = newState;
        }
    }
    return _vocVal;
}