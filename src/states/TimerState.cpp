#include "states/TimerState.h"

TimerState::TimerState()
    : _presetCount(3), _currentPresetIdx(0),
      _running(false), _paused(false),
      _endTime(0), _pausedRemaining(0),
      _onComplete(nullptr) // initialize observer to null
{
    _presetDurations[0] = 1500;   // 25 minutes
    _presetDurations[1] = 5;     // 5  seconds
    _presetDurations[2] = 3000; // 50 minutes
}

void TimerState::setPresets(const int *presets, int count)
{
    _presetCount = (count > 3) ? 3 : count;
    for (int i = 0; i < _presetCount; i++)
    {
        _presetDurations[i] = presets[i];
    }
}

int TimerState::cyclePreset()
{
    _currentPresetIdx = (_currentPresetIdx + 1) % _presetCount;
    return _currentPresetIdx;
}

void TimerState::start()
{
    _running = true;
    _paused = false;
    unsigned long durationMs = _presetDurations[_currentPresetIdx] * 1000UL;
    _endTime = nowMs() + durationMs;
    _pausedRemaining = 0;
}

void TimerState::pause()
{
    if (_running && !_paused)
    {
        _paused = true;
        _pausedRemaining = _endTime - nowMs();
    }
}

void TimerState::resume()
{
    if (_running && _paused)
    {
        _paused = false;
        _endTime = nowMs() + _pausedRemaining;
        _pausedRemaining = 0;
    }
}

void TimerState::stop()
{
    _running = false;
    _paused = false;
    _endTime = 0;
    _pausedRemaining = 0;
    _currentPresetIdx = 0;
}

bool TimerState::isRunning() const { return _running; }
bool TimerState::isPaused() const { return _paused; }

int TimerState::getCurrentPresetIndex() const { return _currentPresetIdx; }

unsigned long TimerState::getRemainingMs() const
{
    if (!_running)
        return 0;
    if (_paused)
        return _pausedRemaining;
    long remain = (long)_endTime - (long)nowMs();
    return (remain > 0) ? remain : 0;
}

int TimerState::getCurrentPresetDuration() const
{
    if (_currentPresetIdx < 0 || _currentPresetIdx >= _presetCount)
        return 0;
    return _presetDurations[_currentPresetIdx];
}

void TimerState::update()
{
    if (_running && !_paused)
    {
        if (nowMs() >= _endTime)
        {
            if (_onComplete)
            {
                _onComplete();
            }
            stop();
        }
    }
}

unsigned long TimerState::nowMs() const { return millis(); }

void TimerState::setOnComplete(void (*callback)(void))
{
    _onComplete = callback;
}