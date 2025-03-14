#ifndef TIMERSTATE_H
#define TIMERSTATE_H

#include <Arduino.h>

class TimerState
{
public:
    TimerState();
    void setPresets(const int *presets, int count);
    int cyclePreset();
    void start();
    void pause();
    void resume();
    void stop();
    bool isRunning() const;
    bool isPaused() const;
    int getCurrentPresetIndex() const;
    unsigned long getRemainingMs() const;
    int getCurrentPresetDuration() const;
    void update();

    // Observer for timer complete
    void setOnComplete(void (*callback)(void));

private:
    int _presetCount;
    int _currentPresetIdx;
    bool _running;
    bool _paused;
    unsigned long _endTime;
    unsigned long _pausedRemaining;
    int _presetDurations[3];
    unsigned long nowMs() const;
    void (*_onComplete)(void);
};

#endif