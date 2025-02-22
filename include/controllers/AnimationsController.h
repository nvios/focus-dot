#ifndef ANIMATIONS_CONTROLLER_H
#define ANIMATIONS_CONTROLLER_H

#include <Arduino.h>
#include <Adafruit_SH110X.h>

class AnimationsController
{
public:
    AnimationsController(Adafruit_SH1106G &disp);
    void update();

private:
    Adafruit_SH1106G &display;

    enum BlinkState
    {
        OPEN,
        CLOSING,
        CLOSED,
        OPENING
    };
    BlinkState blinkState;
    unsigned long blinkStartTime;
    float eyeScale;

    static const int baseWidth = 36;
    static const int baseHeight = 42;
    static const int eyeSeparation = 16;
    static const int borderRadius = 8;
    static const unsigned long OPEN_DURATION = 5000;
    static const unsigned long CLOSING_DURATION = 100;
    static const unsigned long CLOSED_DURATION = 100;
    static const unsigned long OPENING_DURATION = 60;
    static constexpr float MIN_SCALE = 0.1;

    static const unsigned long SHIFT_INTERVAL = 6000;
    static const unsigned long SHIFT_DURATION = 500;
    unsigned long lastShiftTime;
    unsigned long shiftStartTime;
    bool isShifting;

    float currentCenterX, currentCenterY;
    float targetCenterX, targetCenterY;
    float startCenterX, startCenterY;
    static const int numCenters = 5;
    float centers[numCenters][2];
};

#endif