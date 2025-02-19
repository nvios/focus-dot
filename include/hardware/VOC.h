#ifndef VOC_DRIVER_H
#define VOC_DRIVER_H

#include <DFRobot_SGP40.h>
#include "LED.h"

class VOC
{
public:
    VOC(LED& led);
    void begin();
    int readVOC();

private:
    LED& _led;
    DFRobot_SGP40 _sgp40;
    unsigned long lastVocUpdate;
    int cycleIndex;
    int _vocVal;
};

#endif