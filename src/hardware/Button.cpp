#include "hardware/Button.h"

unsigned long Button::pressStartTime = 0;
bool Button::resetHoldFired = false;
Button* Button::instance = nullptr;

Button::Button(uint8_t pin, bool activeLow, ButtonState &state)
    : oneButton(pin, activeLow), buttonState(state) {
    instance = this;
}

void Button::begin() {
    oneButton.attachClick(onSingleClick);
    oneButton.attachDoubleClick(onDoubleClick);
    oneButton.setClickMs(300);
    oneButton.attachLongPressStart(onLongPressStart);
    oneButton.setPressMs(1000);
    oneButton.attachDuringLongPress(onLongPressDuring);
}

void Button::tick() {
    oneButton.tick();
}

void Button::onSingleClick() {
    instance->buttonState.handleEvent(BUTTON_EVENT_SINGLE_CLICK);
}

void Button::onDoubleClick() {
    instance->buttonState.handleEvent(BUTTON_EVENT_DOUBLE_CLICK);
}

void Button::onLongPressStart() {
    pressStartTime = millis();
    resetHoldFired = false;
    instance->buttonState.handleEvent(BUTTON_EVENT_LONG_PRESS);
}

void Button::onLongPressDuring() {
    unsigned long duration = millis() - pressStartTime;
    if (!resetHoldFired && duration >= 10000) {
        resetHoldFired = true;
        instance->buttonState.handleEvent(BUTTON_EVENT_RESET_HOLD);
    }
}