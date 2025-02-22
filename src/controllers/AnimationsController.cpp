#include "controllers/AnimationsController.h"

AnimationsController::AnimationsController(Adafruit_SH1106G &disp) : display(disp)
{
    blinkState = OPEN;
    blinkStartTime = millis();
    eyeScale = 1.0;
    lastShiftTime = millis();
    centers[0][0] = 40;
    centers[0][1] = 32;
    centers[1][0] = 30;
    centers[1][1] = 32;
    centers[2][0] = 40;
    centers[2][1] = 22;
    centers[3][0] = 50;
    centers[3][1] = 32;
    centers[4][0] = 40;
    centers[4][1] = 42;
    currentCenterX = centers[0][0];
    currentCenterY = centers[0][1];
    targetCenterX = currentCenterX;
    targetCenterY = currentCenterY;
    isShifting = false;
}

void AnimationsController::update()
{
    unsigned long now = millis();

    // Blink state machine
    switch (blinkState)
    {
    case OPEN:
        eyeScale = 1.0;
        if (now - blinkStartTime >= OPEN_DURATION)
        {
            blinkState = CLOSING;
            blinkStartTime = now;
        }
        break;
    case CLOSING:
    {
        float t = (now - blinkStartTime) / (float)CLOSING_DURATION;
        if (t >= 1.0)
        {
            t = 1.0;
            blinkState = CLOSED;
            blinkStartTime = now;
        }
        eyeScale = 1.0 - t * (1.0 - MIN_SCALE);
        break;
    }
    case CLOSED:
        eyeScale = MIN_SCALE;
        if (now - blinkStartTime >= CLOSED_DURATION)
        {
            blinkState = OPENING;
            blinkStartTime = now;
        }
        break;
    case OPENING:
    {
        float t = (now - blinkStartTime) / (float)OPENING_DURATION;
        if (t >= 1.0)
        {
            t = 1.0;
            blinkState = OPEN;
            blinkStartTime = now;
        }
        eyeScale = MIN_SCALE + t * (1.0 - MIN_SCALE);
        break;
    }
    }

    // Smooth shifting of eye center position
    if (!isShifting && (now - lastShiftTime >= SHIFT_INTERVAL))
    {
        int idx = random(numCenters);
        targetCenterX = centers[idx][0];
        targetCenterY = centers[idx][1];
        startCenterX = currentCenterX;
        startCenterY = currentCenterY;
        isShifting = true;
        shiftStartTime = now;
    }
    if (isShifting)
    {
        float f = (now - shiftStartTime) / (float)SHIFT_DURATION;
        if (f >= 1.0)
        {
            f = 1.0;
            isShifting = false;
            lastShiftTime = now;
        }
        currentCenterX = startCenterX + f * (targetCenterX - startCenterX);
        currentCenterY = startCenterY + f * (targetCenterY - startCenterY);
    }

    // Draw the eyes animation
    display.clearDisplay();
    float anchorFraction = 0.75;
    float fixedAnchorY = currentCenterY - baseHeight / 2 + anchorFraction * baseHeight;
    float leftEyeX = currentCenterX - baseWidth / 2.0;
    float leftEyeY = fixedAnchorY - anchorFraction * (baseHeight * eyeScale);
    float rightCenterX = currentCenterX + baseWidth + eyeSeparation;
    float rightEyeX = rightCenterX - baseWidth / 2.0;
    float rightEyeY = fixedAnchorY - anchorFraction * (baseHeight * eyeScale);
    display.fillRoundRect(leftEyeX, leftEyeY, baseWidth, baseHeight * eyeScale, borderRadius, SH110X_WHITE);
    display.fillRoundRect(rightEyeX, rightEyeY, baseWidth, baseHeight * eyeScale, borderRadius, SH110X_WHITE);
    display.display();
}