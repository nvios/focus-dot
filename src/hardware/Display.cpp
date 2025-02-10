#include "hardware/Display.h"
#include "assets/Fonts.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>

Display::Display()
    : display_(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, OLED_RESET) {
}

bool Display::begin() {
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display_.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        return false;
    }
    display_.clearDisplay();
    display_.setFont(&Org_01);
    display_.display();
    return true;
}

int Display::writeText(const char* text,
                       int startX,
                       int startY,
                       int textSize,
                       int maxLines) {
    display_.clearDisplay();
    display_.setTextSize(textSize);
    display_.setTextColor(WHITE);
    display_.setTextWrap(false);
    display_.setCursor(startX, startY);

    String input(text);
    input.trim();

    int lineCount = 0;
    bool ellipsized = false;
    String line;
    int idx = 0;

    while (idx < (int)input.length() && lineCount < maxLines) {
        int spacePos = input.indexOf(' ', idx);
        if (spacePos < 0) spacePos = input.length();
        String word = input.substring(idx, spacePos);
        idx = spacePos + 1;
        String testLine = line.isEmpty() ? word : (line + " " + word);

        int16_t x1, y1;
        uint16_t w, h;
        display_.getTextBounds(testLine.c_str(), 0, 0, &x1, &y1, &w, &h);

        if (w > DISPLAY_WIDTH) {
            if (lineCount == maxLines - 1) {
                while (!line.isEmpty()) {
                    display_.getTextBounds((line + "...").c_str(), 0, 0, &x1, &y1, &w, &h);
                    if (w <= DISPLAY_WIDTH) {
                        line += "...";
                        ellipsized = true;
                        break;
                    }
                    line.remove(line.length() - 1);
                }
                display_.println(line);
                break;
            }
            display_.println(line);
            lineCount++;
            line = word;
        } else {
            line = testLine;
        }
    }

    if (!ellipsized && !line.isEmpty() && lineCount < maxLines) {
        display_.println(line);
        lineCount++;
    }

    int finalY = display_.getCursorY();
    display_.display();
    return finalY;
}

void Display::splitTextIntoLines(const String& text,
                                 int maxWidth,
                                 int textSize,
                                 std::vector<String>& lines) {
    lines.clear();
    String currentLine;
    int i = 0;
    while (i < (int)text.length()) {
        int spacePos = text.indexOf(' ', i);
        if (spacePos < 0) spacePos = text.length();
        String word = text.substring(i, spacePos);
        i = spacePos + 1;
        String testLine = currentLine.isEmpty() ? word : (currentLine + " " + word);
        int16_t x1, y1;
        uint16_t w, h;
        display_.setTextSize(textSize);
        display_.getTextBounds(testLine.c_str(), 0, 0, &x1, &y1, &w, &h);
        if (w > (uint16_t)maxWidth) {
            if (!currentLine.isEmpty()) lines.push_back(currentLine);
            currentLine = word;
        } else {
            currentLine = testLine;
        }
    }
    if (!currentLine.isEmpty()) lines.push_back(currentLine);
}

int Display::calculateTotalHeight(const std::vector<String>& lines, int textSize) {
    int total = 0;
    for (auto &ln : lines) {
        int16_t x1, y1;
        uint16_t w, h;
        display_.setTextSize(textSize);
        display_.getTextBounds(ln.c_str(), 0, 0, &x1, &y1, &w, &h);
        total += h;
    }
    return total;
}

void Display::ellipsizeLinesToFit(std::vector<String>& lines, int maxHeight, int textSize) {
    int th = calculateTotalHeight(lines, textSize);
    if (th <= maxHeight) return;
    while (lines.size() > 1 && th > maxHeight) {
        lines.pop_back();
        th = calculateTotalHeight(lines, textSize);
    }
    if (lines.size() == 1 && th > maxHeight) {
        while (!lines[0].isEmpty()) {
            String temp = lines[0] + "...";
            int16_t x1, y1;
            uint16_t w, h;
            display_.getTextBounds(temp.c_str(), 0, 0, &x1, &y1, &w, &h);
            if ((int)h <= maxHeight && (int)w <= DISPLAY_WIDTH) {
                lines[0] = temp;
                return;
            }
            lines[0].remove(lines[0].length() - 1);
        }
        lines[0] = "...";
    } else if (!lines.empty()) {
        lines.back() += "...";
        th = calculateTotalHeight(lines, textSize);
        while (th > maxHeight && lines.back().length() > 3) {
            lines.back().remove(lines.back().length() - 4, 1);
            th = calculateTotalHeight(lines, textSize);
        }
    }
}

int Display::writeAlignedText(const String& text,
                              int maxWidth,
                              int maxHeight,
                              int startX,
                              int startY,
                              int textSize,
                              bool ellipsis,
                              VAlign vAlign,
                              HAlign hAlign) {
    display_.clearDisplay();
    display_.setTextSize(textSize);
    display_.setTextColor(WHITE);
    display_.setTextWrap(false);

    String t = text;
    t.trim();
    std::vector<String> lines;
    splitTextIntoLines(t, maxWidth, textSize, lines);

    if (ellipsis) {
        ellipsizeLinesToFit(lines, maxHeight, textSize);
    } else {
        int th = calculateTotalHeight(lines, textSize);
        while (!lines.empty() && th > maxHeight) {
            lines.pop_back();
            th = calculateTotalHeight(lines, textSize);
        }
    }

    int totalH = calculateTotalHeight(lines, textSize);
    int yOffset = 0;
    if (vAlign == VALIGN_TOP)      yOffset = startY;
    else if (vAlign == VALIGN_CENTER) yOffset = startY + (maxHeight - totalH)/2;
    else if (vAlign == VALIGN_BOTTOM) yOffset = startY + (maxHeight - totalH);

    int currentY = yOffset;
    for (auto &ln : lines) {
        int16_t x1, y1;
        uint16_t w, h;
        display_.setTextSize(textSize);
        display_.getTextBounds(ln.c_str(), 0, 0, &x1, &y1, &w, &h);
        int xOffset = 0;
        if (hAlign == HALIGN_LEFT)      xOffset = startX;
        else if (hAlign == HALIGN_CENTER) xOffset = startX + (maxWidth - w)/2;
        else if (hAlign == HALIGN_RIGHT)  xOffset = startX + (maxWidth - w);
        display_.setCursor(xOffset, currentY);
        display_.println(ln);
        currentY += h;
    }
    display_.display();
    return currentY;
}

void Display::drawUi(int mode, int hour, int min, const char* wDay, int mDay, int voc) {
    if (mode == 0) {
        drawStackedUi(hour, min, wDay, mDay, voc);
    } else {
        drawLinearUi(hour, min, wDay, mDay, voc);
    }
    display_.display();
}

void Display::drawStackedUi(int hour, int min, const char* wDay, int mDay, int voc) {
    display_.clearDisplay();
    display_.setTextSize(5);
    display_.setFont(&Num_01);
    display_.setCursor(0, 20);
    display_.print(hour < 10 ? "0" + String(hour) : String(hour));
    display_.setCursor(0, 50);
    display_.print(min < 10 ? "0" + String(min) : String(min));

    display_.setTextSize(1);
    display_.setFont(&Org_01);
    display_.setCursor(64, 24);
    display_.print(wDay);
    display_.setCursor(64, 54);
    display_.print("VOC");

    display_.setTextSize(voc > 200 ? 2 : 3);
    display_.setCursor(86, 22);
    display_.print(mDay);
    display_.setCursor(86, 52);
    display_.print(voc);
}

void Display::drawLinearUi(int hour, int min, const char* wDay, int mDay, int voc) {
    display_.clearDisplay();
    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", hour, min);
    int16_t x1, y1;
    uint16_t w, h;
    display_.setTextSize(5);
    display_.getTextBounds(buf, 0, 0, &x1, &y1, &w, &h);
    int posX = (DISPLAY_WIDTH - w) / 2;
    display_.setCursor(posX, 30);
    display_.print(buf);

    display_.setTextSize(1);
    display_.setCursor(12, 56);
    display_.print("VOC");
    display_.setCursor(72, 56);
    display_.print(wDay);

    display_.setTextSize(2);
    display_.setCursor(34, 55);
    display_.print(voc);
    display_.setCursor(94, 55);
    display_.print(mDay);
}

String Display::addHours(const String& timeInput, int hoursToAdd) {
    int hours = timeInput.substring(0, 2).toInt();
    int minutes = timeInput.substring(3, 5).toInt();
    hours = (hours + hoursToAdd) % 24;
    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", hours, minutes);
    return String(buf);
}

void Display::drawEventOnDisplay(const String& title,
                                 const String& startTime,
                                 const String& endTime,
                                 int hoursToAdd) {
    int finalY = writeText(title.c_str());
    display_.setTextSize(2);
    display_.setCursor(0, 62);

    String sTime = addHours(startTime, hoursToAdd);
    String eTime = addHours(endTime, hoursToAdd);
    display_.print(sTime);
    display_.print(" > ");
    display_.println(eTime);
    display_.display();
}