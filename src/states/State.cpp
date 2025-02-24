#include "states/State.h"

State::State() : mode(AppMode::CLOCK), dialogueMessage(""), dialogueType(DialogueType::NONE) {}

AppMode State::getMode() const
{
    return mode;
}

void State::setMode(AppMode m)
{
    mode = m;
}

void State::cycleMode()
{
    if (mode == AppMode::CLOCK)
        mode = AppMode::TIMER;
    else if (mode == AppMode::TIMER)
        mode = AppMode::ANIMATION;
    else
        mode = AppMode::CLOCK;
}

TimerState &State::getTimer()
{
    return timer;
}

void State::setDialogueMessage(const String &msg, DialogueType type)
{
    dialogueMessage = msg;
    dialogueType = type;
}

String State::getDialogueMessage() const
{
    return dialogueMessage;
}

DialogueType State::getDialogueType() const
{
    return dialogueType;
}