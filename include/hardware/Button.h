#ifndef HARDWARE_BUTTON_H
#define HARDWARE_BUTTON_H

#include <OneButton.h>
#include <functional>
#include "states/ButtonState.h"

class Button
{
public:
    Button(uint8_t pin, bool activeLow, ButtonState &state);
    void begin();
    void tick();

private:
    // Callback methods
    void onSingleClick();
    void onDoubleClick();
    void onLongPressStart();
    void onLongPressDuring();

    // Member variables
    unsigned long _pressStartTime;
    bool _resetHoldFired;
    OneButton _oneButton;
    ButtonState &_buttonState;
};

#endif