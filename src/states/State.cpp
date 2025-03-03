#include "states/State.h"

State::State() : _mode(AppMode::CLOCK), _dialogueMessage(""), _dialogueType(DialogueType::NONE) {}

AppMode State::getMode() const
{
    return _mode;
}

void State::setMode(AppMode mode)
{
    _mode = mode;
}

void State::cycleMode()
{
    if (_mode == AppMode::CLOCK)
        _mode = AppMode::TIMER;
    else if (_mode == AppMode::TIMER)
        _mode = AppMode::ANIMATION;
    else
        _mode = AppMode::CLOCK;
}

TimerState &State::getTimer()
{
    return _timer;
}

void State::setDialogueMessage(const String &msg, DialogueType type)
{
    _dialogueMessage = msg;
    _dialogueType = type;
}

String State::getDialogueMessage() const
{
    return _dialogueMessage;
}

DialogueType State::getDialogueType() const
{
    return _dialogueType;
}