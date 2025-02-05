#ifndef CLOCK_STATE_H
#define CLOCK_STATE_H

class Display;
class VOC;

class ClockState {
public:
    ClockState(Display& display, VOC& voc);
    void toggleLayout();
    void update();

private:
    Display& display;
    VOC& voc;
    bool stackedLayout = true;
    unsigned long lastDraw = 0;
};

#endif