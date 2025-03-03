#ifndef HARDWARE_BUTTON_H
#define HARDWARE_BUTTON_H

#include <OneButton.h>
#include "states/ButtonState.h"

class Button
{
public:
    Button(uint8_t pin, bool activeLow, ButtonState &state);
    void begin();
    void tick();

private:
    // Static callback handlers for OneButton
    static void handleClick();
    static void handleDoubleClick();
    static void handleLongPressStart();
    static void handleLongPressDuring();

    // Instance callback methods
    void onSingleClick();
    void onDoubleClick();
    void onLongPressStart();
    void onLongPressDuring();

    // Static instance pointer for callbacks
    static Button *_instance;

    // Member variables
    unsigned long _pressStartTime;
    bool _resetHoldFired;
    OneButton _oneButton;
    ButtonState &_buttonState;
};

#endif