#include "states/ClockState.h"
#include "hardware/Display.h"
#include "hardware/VOC.h"

ClockState::ClockState(Display &display, VOC &voc)
    : display(display), voc(voc) {}

void ClockState::update()
{
    unsigned long now = millis();
    if (now - lastDraw < 1000)
        return;
    lastDraw = now;

    time_t t = time(nullptr);
    struct tm *ti = localtime(&t);
    const char *daysOfWeek[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

    display.drawClock(ti->tm_hour, ti->tm_min,
                      daysOfWeek[ti->tm_wday], ti->tm_mday,
                      voc.readVOC());
}