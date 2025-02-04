#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

#include <Arduino.h>

enum AppState {
    STATE_IDLE,
    STATE_CONFIG_MODE,
    STATE_RESETTING
};

enum ButtonEvent {
    BUTTON_EVENT_NONE,
    BUTTON_EVENT_SINGLE_CLICK,
    BUTTON_EVENT_DOUBLE_CLICK,
    BUTTON_EVENT_LONG_PRESS,
    BUTTON_EVENT_RESET_HOLD
};

class LED;
class Display;
class WiFiController;

class ButtonState {
public:
    ButtonState(LED &led, Display &display, WiFiController &wifi);
    void handleEvent(ButtonEvent event);
    AppState getCurrentState() const;
    void setState(AppState newState);

private:
    LED &led;
    Display &display;
    WiFiController &wifiController;
    AppState currentState;
};

#endif