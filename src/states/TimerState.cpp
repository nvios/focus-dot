#include "states/TimerState.h"

TimerState::TimerState()
    : presetCount(3), currentPresetIdx(0),
      running(false), paused(false),
      endTime(0), pausedRemaining(0),
      onComplete(nullptr) // initialize observer to null
{
    presetDurations[0] = 5;     // 5  seconds
    presetDurations[1] = 300;   // 5 minutes
    presetDurations[2] = 14400; // 240 minutes
}

void TimerState::setPresets(const int *presets, int count)
{
    presetCount = (count > 3) ? 3 : count;
    for (int i = 0; i < presetCount; i++)
    {
        presetDurations[i] = presets[i];
    }
}

int TimerState::cyclePreset()
{
    currentPresetIdx = (currentPresetIdx + 1) % presetCount;
    return currentPresetIdx;
}

void TimerState::start()
{
    running = true;
    paused = false;
    unsigned long durationMs = presetDurations[currentPresetIdx] * 1000UL;
    endTime = nowMs() + durationMs;
    pausedRemaining = 0;
}

void TimerState::pause()
{
    if (running && !paused)
    {
        paused = true;
        pausedRemaining = endTime - nowMs();
    }
}

void TimerState::resume()
{
    if (running && paused)
    {
        paused = false;
        endTime = nowMs() + pausedRemaining;
        pausedRemaining = 0;
    }
}

void TimerState::stop()
{
    running = false;
    paused = false;
    endTime = 0;
    pausedRemaining = 0;
    currentPresetIdx = 0;
}

bool TimerState::isRunning() const { return running; }
bool TimerState::isPaused() const { return paused; }

int TimerState::getCurrentPresetIndex() const { return currentPresetIdx; }

unsigned long TimerState::getRemainingMs() const
{
    if (!running)
        return 0;
    if (paused)
        return pausedRemaining;
    long remain = (long)endTime - (long)nowMs();
    return (remain > 0) ? remain : 0;
}

int TimerState::getCurrentPresetDuration() const
{
    if (currentPresetIdx < 0 || currentPresetIdx >= presetCount)
        return 0;
    return presetDurations[currentPresetIdx];
}

void TimerState::update()
{
    if (running && !paused)
    {
        if (nowMs() >= endTime)
        {
            if (onComplete)
            {
                onComplete();
            }
            stop();
        }
    }
}

unsigned long TimerState::nowMs() const { return millis(); }

void TimerState::setOnComplete(void (*callback)(void))
{
    onComplete = callback;
}