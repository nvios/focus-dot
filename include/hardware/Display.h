#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <configurations/Config.h>
#include <vector>

enum VAlign {
  VALIGN_TOP,
  VALIGN_CENTER,
  VALIGN_BOTTOM
};

enum HAlign {
  HALIGN_LEFT,
  HALIGN_CENTER,
  HALIGN_RIGHT
};

class Display {
public:
    Display();
    bool begin();
    int writeText(const char* text,
                  int startX = 0,
                  int startY = 8,
                  int textSize = 2,
                  int maxLines = 3);

    int writeAlignedText(const String& text,
                         int maxWidth = DISPLAY_WIDTH,
                         int maxHeight = DISPLAY_HEIGHT,
                         int startX = 0,
                         int startY = 0,
                         int textSize = 2,
                         bool ellipsis = true,
                         VAlign vAlign = VALIGN_CENTER,
                         HAlign hAlign = HALIGN_CENTER);

    void drawUi(int mode, int hour, int min, const char* wDay, int mDay, int voc);
    void drawEventOnDisplay(const String& title,
                            const String& startTime,
                            const String& endTime,
                            int hoursToAdd);

private:
    Adafruit_SSD1306 display_;
    void drawStackedUi(int hour, int min, const char* wDay, int mDay, int voc);
    void drawLinearUi(int hour, int min, const char* wDay, int mDay, int voc);
    String addHours(const String& timeInput, int hoursToAdd);

    void splitTextIntoLines(const String& text, int maxWidth, int textSize, std::vector<String>& lines);
    int calculateTotalHeight(const std::vector<String>& lines, int textSize);
    void ellipsizeLinesToFit(std::vector<String>& lines, int maxHeight, int textSize);
};

#endif