#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <configurations/Config.h>

class Display {
public:
    Display();
    bool begin();
    int writeText(const char* text,
                  int startX = 0,
                  int startY = 8,
                  int textSize = 2,
                  int maxLines = 3);
    void drawUi(int mode, int hour, int min, const char* wDay, int mDay, int voc);
    void drawEventOnDisplay(const String& title,
                            const String& startTime,
                            const String& endTime,
                            int hoursToAdd);

private:
    void drawStackedUi(int hour, int min, const char* wDay, int mDay, int voc);
    void drawLinearUi(int hour, int min, const char* wDay, int mDay, int voc);
    String addHours(const String& timeInput, int hoursToAdd);

    Adafruit_SSD1306 display_;
};

#endif
