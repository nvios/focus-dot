#ifndef TIMERSTATE_H
#define TIMERSTATE_H

#include <Arduino.h>

class TimerState {
public:
    TimerState();

    void cyclePreset();
    void start();
    void pause();
    void resume();
    void stop();

    bool isRunning() const;
    bool isPaused() const;
    int getCurrentPresetIndex() const;
    int getCurrentPresetDuration() const;
    unsigned long getRemainingMs() const;

    void setPresets(const int* presets, int count);
    void update();

private:
    int presetDurations[3]; 
    int presetCount;
    int currentPresetIdx;
    bool running;
    bool paused;
    unsigned long endTime;
    unsigned long pausedRemaining;

    unsigned long nowMs() const;
};

#endif