#ifndef VOC_DRIVER_H
#define VOC_DRIVER_H

#include <Arduino.h>
#include "LED.h"

class VOC
{
public:

    /**
     * Constructor.
     * @param ledDriver Reference to an LEDDriver instance to control LEDs based on VOC levels.
     */
    VOC(LED& led);

    /**
     * Initializes the VOC sensor (if any initialization is needed).
     */
    void begin();

    /**
     * Reads the VOC sensor value.
     * @return Current VOC value.
     */
    int readVOC();

private:
    unsigned long lastVocUpdate;
    int cycleIndex;
    static const int mockVals[3];
    LED& _led;
};

#endif // VOC_DRIVER_H