#ifndef DISPLAY_H
#define DISPLAY_H

#define DEFAULT_FRAME_WIDTH 128
#define DEFAULT_FRAME_HEIGHT 64
#define DEFAULT_FRAME_DELAY 64

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

class Display {
public:
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

  void startAnimation(const byte* frames, int frameCount, bool loop, bool reverse, bool boomerang, unsigned long loopDelay, unsigned long durationMs, int width, int height);
  void updateAnimation();
  bool isAnimationRunning();

private:
  Adafruit_SH1106G display_;
  String addHours(const String &timeInput, int hoursToAdd);
  void splitTextIntoLines(const String &text, int maxWidth, int textSize, std::vector<String> &lines);
  int calculateTotalHeight(const std::vector<String> &lines, int textSize);
  void ellipsizeLinesToFit(std::vector<String> &lines, int maxHeight, int textSize);


 const byte* animFrames = nullptr;
  int animFrameCount = 0;
  int animCurrentFrame = 0;
  int animFrameWidth = 0;
  int animFrameHeight = 0;
  bool animLoop = false;
  bool animReverse = false;
  bool animBoomerang = false;
  bool animForward = true;
  unsigned long animStartTime = 0;
  unsigned long animLastFrameTime = 0;
  unsigned long animDuration = 0;
  unsigned long animFrameDelay = DEFAULT_FRAME_DELAY;
  unsigned long animLoopDelay = 0;
};

#endif