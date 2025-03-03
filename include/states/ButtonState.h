#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

enum class AppState
{
    STATE_IDLE,
    STATE_CYCLE_MODE,
    STATE_RESET
};

enum class ButtonEvent
{
    NONE,
    SINGLE_CLICK,
    DOUBLE_CLICK,
    LONG_PRESS,
    RESET_HOLD
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

    int _presetNumber;
    unsigned long _resetModeEnteredTime;
    bool _ignoreNextClick;
    AppState _currentState;

    // References to other components
    LED &_led;
    Display &_display;
    WiFiController &_wifiController;
    ClockState &_clock;
    State &_appState;
};

#endif