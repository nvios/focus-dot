#ifndef HARDWARE_BUTTON_H
#define HARDWARE_BUTTON_H

#include <OneButton.h>
#include "states/ButtonState.h"

class Button {
public:
    Button(uint8_t pin, bool activeLow, ButtonState &state);
    void begin();
    void tick();

private:
    static void onSingleClick();
    static void onDoubleClick();
    static void onLongPressStart();
    static void onLongPressDuring();

    static unsigned long pressStartTime;
    static bool resetHoldFired;
    static Button* instance;

    OneButton oneButton;
    ButtonState &buttonState;
};

#endif