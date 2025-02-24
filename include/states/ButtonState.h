#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

enum AppState
{
    STATE_IDLE,
    STATE_CYCLE_MODE,
    STATE_RESET
};

enum ButtonEvent
{
    BUTTON_EVENT_NONE,
    BUTTON_EVENT_SINGLE_CLICK,
    BUTTON_EVENT_DOUBLE_CLICK,
    BUTTON_EVENT_LONG_PRESS,
    BUTTON_EVENT_RESET_HOLD
};

class LED;
class Display;
class WiFiController;
class ClockState;
class State;

class ButtonState
{
public:
    ButtonState(LED &led,
                Display &display,
                WiFiController &wifi,
                ClockState &clock,
                State &appState);

    void handleEvent(ButtonEvent event);

private:
    void setState(AppState newState);
    int presetNumber;
    AppState currentState;
    LED &led;
    Display &display;
    WiFiController &wifiController;
    ClockState &clock;
    State &appState;
};

#endif