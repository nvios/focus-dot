#include "controllers/AnimationsController.h"

AnimationsController::AnimationsController(Adafruit_SH1106G &disp) : display(disp)
{
    // Initialize eyes animation state
    mode = EYES;
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

    // Initialize bitmap animation state as not running
    animationFrames = nullptr;
    totalFrames = 0;
    loopAnimation = false;
    playInReverse = false;
    bitmapAnimationRunning = false;
    currentFrame = 0;
    frameWidth = frameHeight = 0;
    frameDelay = 100;
    animationDuration = 0;
    animationStartTime = lastFrameTime = 0;
    frameX = frameY = frameSize = 0;
}

void AnimationsController::update()
{
    if (mode == BITMAP)
    {
        updateBitmapAnimation();
    }
    else
    {
        updateEyesAnimation();
    }
}

void AnimationsController::updateEyesAnimation()
{
    unsigned long now = millis();

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

    // Draw eyes animation
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

void AnimationsController::startBitmapAnimation(const byte *frames, int frameCount, bool loop, bool reverse, unsigned long durationMs, int width, int height)
{
    mode = BITMAP;
    animationFrames = frames;
    totalFrames = frameCount;
    loopAnimation = loop;
    playInReverse = reverse;
    bitmapAnimationRunning = true;
    currentFrame = playInReverse ? totalFrames - 1 : 0;
    frameWidth = width;
    frameHeight = height;
    frameDelay = 100;
    animationDuration = (durationMs == 0) ? totalFrames * frameDelay : durationMs;
    animationStartTime = millis();
    lastFrameTime = millis();
    frameX = (display.width() - frameWidth) / 2;
    frameY = (display.height() - frameHeight) / 2;
    frameSize = (frameWidth * frameHeight) / 8;

    display.clearDisplay();
    display.drawBitmap(frameX, frameY, &animationFrames[currentFrame * frameSize], frameWidth, frameHeight, SH110X_WHITE);
    display.display();
}

void AnimationsController::updateBitmapAnimation()
{
    if (!bitmapAnimationRunning)
        return;

    unsigned long currentTime = millis();
    if (currentTime - animationStartTime >= animationDuration)
    {
        bitmapAnimationRunning = false;
        mode = EYES; // Switch back to eyes animation
        return;
    }
    if (currentTime - lastFrameTime >= frameDelay)
    {
        lastFrameTime = currentTime;
        if (playInReverse)
        {
            currentFrame--;
            if (currentFrame < 0)
            {
                if (loopAnimation)
                    currentFrame = totalFrames - 1;
                else
                {
                    bitmapAnimationRunning = false;
                    mode = EYES;
                    return;
                }
            }
        }
        else
        {
            currentFrame++;
            if (currentFrame >= totalFrames)
            {
                if (loopAnimation)
                    currentFrame = 0;
                else
                {
                    bitmapAnimationRunning = false;
                    mode = EYES;
                    return;
                }
            }
        }
        display.clearDisplay();
        display.drawBitmap(frameX, frameY, &animationFrames[currentFrame * frameSize], frameWidth, frameHeight, SH110X_WHITE);
        display.display();
    }
}

bool AnimationsController::isBitmapAnimationRunning()
{
    return bitmapAnimationRunning;
}

void AnimationsController::startEyesAnimation()
{
    mode = EYES;
    blinkState = OPEN;
    blinkStartTime = millis();
    eyeScale = 1.0;
    lastShiftTime = millis();
    currentCenterX = centers[0][0];
    currentCenterY = centers[0][1];
    targetCenterX = currentCenterX;
    targetCenterY = currentCenterY;
    isShifting = false;
}