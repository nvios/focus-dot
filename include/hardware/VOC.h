#ifndef VOC_H
#define VOC_H

#include "LED.h"
#include <DFRobot_SGP40.h>

class VOC
{
public:
    VOC(LED &led);
    void begin();
    int readVOC();

private:
    LED &_led;
    unsigned long lastVocUpdate;
    int _vocVal;
    LEDState _lastVocRange;
    DFRobot_SGP40 _sgp40;
};

#endif
