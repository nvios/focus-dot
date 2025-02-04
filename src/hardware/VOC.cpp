#include "hardware/VOC.h"
#include "hardware/LED.h"

// Initialize the static mock values
const int VOC::mockVals[3] = {12, 93, 248};

VOC::VOC(LED& led)
    : lastVocUpdate(0), cycleIndex(0), _led(led)
{
    // Constructor body can be empty or used for additional initialization
}

void VOC::begin()
{
    // Initialize VOC sensor here if needed
    // For mock values, no initialization is required
}

int VOC::readVOC()
{
    unsigned long now = millis();

    if (now - lastVocUpdate >= 10000)
    {
        lastVocUpdate = now;
        cycleIndex = (cycleIndex + 1) % 3;

        // Update LED state based on cycleIndex
        switch (cycleIndex)
        {
            case 0:
                _led.setLEDState(LEDState::VOC_GREEN);
                break;
            case 1:
                _led.setLEDState(LEDState::VOC_YELLOW);
                break;
            case 2:
                _led.setLEDState(LEDState::VOC_RED);
                break;
        }
    }

    return mockVals[cycleIndex];
}