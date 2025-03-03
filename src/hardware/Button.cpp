#include "hardware/Button.h"

Button::Button(uint8_t pin, bool activeLow, ButtonState &state)
    : _pressStartTime(0),
      _resetHoldFired(false),
      _oneButton(pin, activeLow),
      _buttonState(state)
{
}

void Button::begin()
{
    // Use lambda functions to capture 'this' pointer and call member functions
    _oneButton.attachClick([this]()
                           { this->onSingleClick(); });
    _oneButton.attachDoubleClick([this]()
                                 { this->onDoubleClick(); });
    _oneButton.setClickMs(300);
    _oneButton.attachLongPressStart([this]()
                                    { this->onLongPressStart(); });
    _oneButton.setPressMs(1000);
    _oneButton.attachDuringLongPress([this]()
                                     { this->onLongPressDuring(); });
}

void Button::tick()
{
    _oneButton.tick();
}

void Button::onSingleClick()
{
    _buttonState.handleEvent(ButtonEvent::SINGLE_CLICK);
}

void Button::onDoubleClick()
{
    _buttonState.handleEvent(ButtonEvent::DOUBLE_CLICK);
}

void Button::onLongPressStart()
{
    _pressStartTime = millis();
    _resetHoldFired = false;
    _buttonState.handleEvent(ButtonEvent::LONG_PRESS);
}

void Button::onLongPressDuring()
{
    unsigned long duration = millis() - _pressStartTime;
    if (!_resetHoldFired && duration >= 10000)
    {
        _resetHoldFired = true;
        _buttonState.handleEvent(ButtonEvent::RESET_HOLD);
    }
}