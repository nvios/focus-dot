#include "hardware/Display.h"
#include "states/TimerState.h"
#include "assets/Fonts.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <vector>

Display::Display() : display_(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET) {}

bool Display::begin()
{
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display_.begin(0x3C, true))
        return false;
    display_.clearDisplay();
    display_.setFont(&Org_01);
    display_.display();
    return true;
}

void Display::splitTextIntoLines(const String &text, int maxWidth, int textSize, std::vector<String> &lines) {
    lines.clear();
    String currentLine;
    int i = 0;
    while (i < text.length()) {
        int nextSpace = text.indexOf(' ', i);
        int nextNewline = text.indexOf('\n', i);
        
        int breakPos = -1;
        bool isNewline = false;
        if (nextNewline != -1 && (nextSpace == -1 || nextNewline < nextSpace)) {
            breakPos = nextNewline;
            isNewline = true;
        } else {
            breakPos = (nextSpace != -1) ? nextSpace : text.length();
        }
        
        String word = text.substring(i, breakPos);
        i = breakPos + 1;
        
        String testLine = currentLine.isEmpty() ? word : currentLine + " " + word;
        int16_t x1, y1;
        uint16_t w, h;
        display_.setTextSize(textSize);
        display_.getTextBounds(testLine.c_str(), 0, 0, &x1, &y1, &w, &h);
        if (w > (uint16_t)maxWidth) {
            if (!currentLine.isEmpty())
                lines.push_back(currentLine);
            currentLine = word;
        } else {
            currentLine = testLine;
        }
        if (isNewline) {
            lines.push_back(currentLine);
            currentLine = "";
        }
    }
    if (!currentLine.isEmpty())
        lines.push_back(currentLine);
}

int Display::calculateTotalHeight(const std::vector<String> &lines, int textSize)
{
    int total = 0;
    for (auto &ln : lines)
    {
        int16_t x1, y1;
        uint16_t w, h;
        display_.setTextSize(textSize);
        display_.getTextBounds(ln.c_str(), 0, 0, &x1, &y1, &w, &h);
        total += h;
    }
    return total;
}

void Display::ellipsizeLinesToFit(std::vector<String> &lines, int maxHeight, int textSize)
{
    int th = calculateTotalHeight(lines, textSize);
    if (th <= maxHeight)
        return;
    while (lines.size() > 1 && th > maxHeight)
    {
        lines.pop_back();
        th = calculateTotalHeight(lines, textSize);
    }
    if (lines.size() == 1 && th > maxHeight)
    {
        while (!lines[0].isEmpty())
        {
            String temp = lines[0] + "...";
            int16_t x1, y1;
            uint16_t w, h;
            display_.getTextBounds(temp.c_str(), 0, 0, &x1, &y1, &w, &h);
            if ((int)h <= maxHeight && (int)w <= DISPLAY_WIDTH)
            {
                lines[0] = temp;
                return;
            }
            lines[0].remove(lines[0].length() - 1);
        }
        lines[0] = "...";
    }
    else if (!lines.empty())
    {
        lines.back() += "...";
        th = calculateTotalHeight(lines, textSize);
        while (th > maxHeight && lines.back().length() > 3)
        {
            lines.back().remove(lines.back().length() - 4, 1);
            th = calculateTotalHeight(lines, textSize);
        }
    }
}

int Display::writeAlignedText(const String &text, int maxWidth, int maxHeight, int startX, int startY, int textSize,
                              bool ellipsis, bool clearDisplay, bool displayText, VAlign vAlign, HAlign hAlign)
{
    if (clearDisplay)
        display_.clearDisplay();
    display_.setTextSize(textSize);
    display_.setTextColor(SH110X_WHITE);
    display_.setTextWrap(false);
    String t = text;
    t.trim();
    std::vector<String> lines;
    splitTextIntoLines(t, maxWidth, textSize, lines);
    if (ellipsis)
    {
        ellipsizeLinesToFit(lines, maxHeight, textSize);
    }
    else
    {
        int th = calculateTotalHeight(lines, textSize);
        while (!lines.empty() && th > maxHeight)
        {
            lines.pop_back();
            th = calculateTotalHeight(lines, textSize);
        }
    }
    int totalH = calculateTotalHeight(lines, textSize);
    int yOffset = (vAlign == VALIGN_TOP) ? startY : (vAlign == VALIGN_CENTER ? startY + (maxHeight - totalH) / 2 : startY + (maxHeight - totalH));
    int currentY = yOffset;
    for (auto &ln : lines)
    {
        int16_t x1, y1;
        uint16_t w, h;
        display_.setTextSize(textSize);
        display_.getTextBounds(ln.c_str(), 0, 0, &x1, &y1, &w, &h);
        int xOffset = (hAlign == HALIGN_LEFT) ? startX : (hAlign == HALIGN_CENTER ? startX + (maxWidth - w) / 2 : startX + (maxWidth - w));
        display_.setCursor(xOffset, currentY - y1);
        display_.println(ln);
        currentY += (h + textSize);
    }
    if (displayText)
        display_.display();
    return currentY;
}

void Display::drawClock(int hour, int min, const char *wDay, int mDay, int voc)
{
    display_.clearDisplay();
    char timeBuf[6];
    snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", hour, min);
    int line1Y = writeAlignedText(timeBuf, 128, 64, 0, 8, 5, false, true, false, VALIGN_TOP, HALIGN_CENTER);
    int line2Y = line1Y + 10;
    int16_t x1, y1;
    uint16_t w, h;
    char dayBuf[5];
    snprintf(dayBuf, sizeof(dayBuf), "%02d", mDay);
    display_.setTextSize(2);
    display_.getTextBounds(dayBuf, 0, 0, &x1, &y1, &w, &h);
    int dayWidth = w;
    char vocBuf[6];
    snprintf(vocBuf, sizeof(vocBuf), "%d", voc);
    display_.getTextBounds(vocBuf, 0, 0, &x1, &y1, &w, &h);
    int vocValWidth = w;
    int labelWidth = 22;
    int totalLine2Width = labelWidth + dayWidth + 4 + labelWidth + vocValWidth;
    int line2X = (DISPLAY_WIDTH - totalLine2Width) / 2;
    display_.setTextSize(1);
    display_.setCursor(line2X, line2Y);
    display_.print(wDay);
    line2X += labelWidth;
    display_.setTextSize(2);
    display_.setCursor(line2X, line2Y);
    display_.print(dayBuf);
    line2X += dayWidth + 4;
    display_.setTextSize(1);
    display_.setCursor(line2X, line2Y);
    display_.print("VOC");
    line2X += labelWidth;
    display_.setTextSize(2);
    display_.setCursor(line2X, line2Y);
    display_.print(vocBuf);
    display_.display();
}

String Display::addHours(const String &timeInput, int hoursToAdd)
{
    int hours = timeInput.substring(0, 2).toInt();
    int minutes = timeInput.substring(3, 5).toInt();
    hours = (hours + hoursToAdd) % 24;
    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", hours, minutes);
    return String(buf);
}

void Display::drawEvent(const String &title, const String &startTime, const String &endTime, int hoursToAdd)
{
    int finalY = writeAlignedText(title.c_str(), 128, 64, 0, 0, 2, true, true, false, VALIGN_TOP, HALIGN_CENTER);
    display_.setTextSize(2);
    display_.setCursor(0, 62);
    String sTime = addHours(startTime, hoursToAdd);
    String eTime = addHours(endTime, hoursToAdd);
    String buffer = sTime + " > " + eTime;
    writeAlignedText(buffer.c_str(), 128, 64, 0, finalY + 10, 2, true, false, true, VALIGN_TOP, HALIGN_CENTER);
}

void Display::drawTimer(const TimerState &timer)
{
    display_.clearDisplay();
    unsigned long remainingMs = timer.getRemainingMs();
    if (!timer.isRunning())
        remainingMs = (unsigned long)timer.getCurrentPresetDuration() * 1000UL;
    unsigned long totalSec = remainingMs / 1000UL;
    unsigned int minutes = totalSec / 60;
    unsigned int seconds = totalSec % 60;
    char timeBuf[6];
    snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d", minutes, seconds);
    display_.setTextSize(5);
    int16_t x1, y1;
    uint16_t w, h;
    display_.getTextBounds(timeBuf, 0, 0, &x1, &y1, &w, &h);
    int mainFontSize = (w > 128) ? 4 : 5;
    display_.setTextSize(mainFontSize);
    int line1Y = writeAlignedText(timeBuf, 128, 64, 0, 0, mainFontSize, false, true, false, VALIGN_CENTER, HALIGN_CENTER);
    char presetBuf[6];
    snprintf(presetBuf, sizeof(presetBuf), "P-%02d", timer.getCurrentPresetIndex() + 1);
    int line2Y = line1Y + 8;
    display_.setTextSize(1);
    display_.setCursor((DISPLAY_WIDTH - 3 * 6) / 2, line2Y);
    display_.print(presetBuf);
    if (!timer.isRunning())
        writeAlignedText("Double tap to start", 128, 64, 0, 64 - 10, 1, false, true, false, VALIGN_BOTTOM, HALIGN_CENTER);
    else if (timer.isPaused())
        writeAlignedText("Tap to resume\nDouble tap to stop", 128, 64, 0, 64 - 20, 1, false, true, false, VALIGN_BOTTOM, HALIGN_CENTER);
    display_.display();
}

void Display::startAnimation(const byte *frames, int frameCount, bool loop, bool reverse, bool boomerang, unsigned long loopDelay, unsigned long durationMs, int width, int height)
{
    animFrames = frames;
    animFrameCount = frameCount;
    animLoop = loop;
    animReverse = reverse;
    animBoomerang = boomerang;
    animLoopDelay = loopDelay;
    animFrameWidth = width;
    animFrameHeight = height;
    animFrameDelay = DEFAULT_FRAME_DELAY;
    animDuration = (durationMs == 0) ? frameCount * animFrameDelay : durationMs;
    animStartTime = millis();
    animLastFrameTime = millis();

    if (animBoomerang)
    {
        animForward = !reverse;
        animCurrentFrame = (animForward ? 0 : animFrameCount - 1);
    }
    else
    {
        animCurrentFrame = (reverse ? animFrameCount - 1 : 0);
    }

    int frameX = (display_.width() - animFrameWidth) / 2;
    int frameY = (display_.height() - animFrameHeight) / 2;
    int frameSize = (animFrameWidth * animFrameHeight) / 8;
    display_.clearDisplay();
    display_.drawBitmap(frameX, frameY, animFrames + (animCurrentFrame * frameSize), animFrameWidth, animFrameHeight, SH110X_WHITE);
    display_.display();
}

void Display::updateAnimation()
{
    if (animFrameCount <= 0)
        return;
    unsigned long currentTime = millis();

    if (currentTime - animLastFrameTime < animFrameDelay)
        return;

    if (!animBoomerang)
    {
        if (!animReverse)
        {
            animCurrentFrame++;
            if (animCurrentFrame >= animFrameCount)
            {
                if (animLoop)
                    animCurrentFrame = 0;
                else
                {
                    animFrameCount = 0;
                    return;
                }
            }
        }
        else
        {
            animCurrentFrame--;
            if (animCurrentFrame < 0)
            {
                if (animLoop)
                    animCurrentFrame = animFrameCount - 1;
                else
                {
                    animFrameCount = 0;
                    return;
                }
            }
        }
        animLastFrameTime = currentTime;
    }
    else
    {
        if (animForward)
        {
            if (animCurrentFrame < animFrameCount - 1)
            {
                animCurrentFrame++;
                animLastFrameTime = currentTime;
            }
            else
            {
                animForward = false;
                animCurrentFrame = (animFrameCount > 1) ? animFrameCount - 2 : 0;
                animLastFrameTime = currentTime;
            }
        }
        else
        {
            if (animCurrentFrame > 0)
            {
                animCurrentFrame--;
                animLastFrameTime = currentTime;
            }
            else
            {
                if (currentTime - animLastFrameTime < animFrameDelay + animLoopDelay)
                    return;
                animForward = true;
                animCurrentFrame = (animFrameCount > 1) ? 1 : 0;
                animLastFrameTime = currentTime;
            }
        }
    }

    int frameX = (display_.width() - animFrameWidth) / 2;
    int frameY = (display_.height() - animFrameHeight) / 2;
    int frameSize = (animFrameWidth * animFrameHeight) / 8;
    display_.clearDisplay();
    display_.drawBitmap(frameX, frameY, animFrames + (animCurrentFrame * frameSize), animFrameWidth, animFrameHeight, SH110X_WHITE);
    display_.display();
}

bool Display::isAnimationRunning()
{
    return (animFrameCount > 0);
}

Adafruit_SH1106G& Display::getHardware() {
  return display_;
}