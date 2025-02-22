#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <configurations/Config.h>
#include <states/TimerState.h>
#include <vector>

enum VAlign
{
  VALIGN_TOP,
  VALIGN_CENTER,
  VALIGN_BOTTOM
};
enum HAlign
{
  HALIGN_LEFT,
  HALIGN_CENTER,
  HALIGN_RIGHT
};

class Display
{
public:
  Adafruit_SH1106G &getHardware();
  Display();
  bool begin();
  int writeAlignedText(const String &text,
                       int maxWidth = DISPLAY_WIDTH,
                       int maxHeight = DISPLAY_HEIGHT,
                       int startX = 0,
                       int startY = 0,
                       int textSize = 2,
                       bool ellipsis = true,
                       bool clearDisplay = true,
                       bool displayText = true,
                       VAlign vAlign = VALIGN_CENTER,
                       HAlign hAlign = HALIGN_CENTER);

  void drawClock(int hour, int min, const char *wDay, int mDay, int voc);
  void drawTimer(const TimerState &timer);
  void drawEvent(const String &title, const String &startTime, const String &endTime, int hoursToAdd);

  void startAnimation(const byte *frames, int frameCount, bool loop, bool reverse, unsigned long durationMs, int width, int height);
  void updateAnimation();
  bool isAnimationRunning();

private:
  Adafruit_SH1106G display_;
  String addHours(const String &timeInput, int hoursToAdd);
  void splitTextIntoLines(const String &text, int maxWidth, int textSize, std::vector<String> &lines);
  int calculateTotalHeight(const std::vector<String> &lines, int textSize);
  void ellipsizeLinesToFit(std::vector<String> &lines, int maxHeight, int textSize);

  const byte *animationFrames;
  int totalFrames;
  int currentFrame;
  int frameWidth;
  int frameHeight;
  int frameX;
  int frameY;
  int frameSize;
  bool animationRunning;
  bool loopAnimation;
  bool playInReverse;
  unsigned long animationStartTime;
  unsigned long lastFrameTime;
  unsigned long animationDuration;
  unsigned long frameDelay;
};

#endif