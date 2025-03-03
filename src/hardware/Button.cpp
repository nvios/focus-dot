#include "hardware/Button.h"

// Static instance pointer for callbacks
Button *Button::_instance = nullptr;

Button::Button(uint8_t pin, bool activeLow, ButtonState &state)
    : _pressStartTime(0),
      _resetHoldFired(false),
      _oneButton(pin, activeLow),
      _buttonState(state)
{
    _instance = this;
}

void Button::begin()
{
    // Use static callback functions
    _oneButton.attachClick(Button::handleClick);
    _oneButton.attachDoubleClick(Button::handleDoubleClick);
    _oneButton.setClickMs(300);
    _oneButton.attachLongPressStart(Button::handleLongPressStart);
    _oneButton.setPressMs(1000);
    _oneButton.attachDuringLongPress(Button::handleLongPressDuring);
}

void Button::tick()
{
    _oneButton.tick();
}

// Static callback handlers
void Button::handleClick()
{
    if (_instance)
        _instance->onSingleClick();
}

void Button::handleDoubleClick()
{
    if (_instance)
        _instance->onDoubleClick();
}

void Button::handleLongPressStart()
{
    if (_instance)
        _instance->onLongPressStart();
}

void Button::handleLongPressDuring()
{
    if (_instance)
        _instance->onLongPressDuring();
}

// Instance methods
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