#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
#include "states/TimerState.h"

enum class AppMode {
    CLOCK,
    TIMER,
    ANIMATION,
    NOTIFICATION,
    DIALOGUE
};

enum class DialogueType {
    NONE,
    TIMER_START,    // "Double click to start\nP-01: ... min."
    TIMER_PAUSED,   // "Click to resume\nDouble click to stop"
    RESET           // "Click to go back\nDouble click to reset"
};

class State {
public:
    State();
    AppMode getMode() const;
    void setMode(AppMode mode);
    void cycleMode();
    TimerState &getTimer();

    void setDialogueMessage(const String &msg, DialogueType type);
    String getDialogueMessage() const;
    DialogueType getDialogueType() const;

private:
    AppMode mode;
    String dialogueMessage;
    DialogueType dialogueType;
    TimerState timer;
};

#endif