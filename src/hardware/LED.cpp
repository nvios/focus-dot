#include "hardware/LED.h"
#include "Arduino.h"
#include <math.h>

const unsigned long LED::EVENT_ANIMATION_MS = 45000;
const unsigned long LED::VOC_ANIMATION_MS = 10000;

LED::LED(uint8_t pin, uint16_t numPixels)
    : _ring(numPixels, pin, NEO_GRB + NEO_KHZ800),
      _stateStartTime(0),
      _activeLed(0),
      _lastTailUpdate(0),
      _pulseVal(0),
      _pulseRising(true)
{
}

void LED::begin()
{
    _ring.begin();
    _ring.clear();
    _ring.show();
}

void LED::setLEDState(LEDState newState)
{
    _stateManager.setState(newState);
    _stateStartTime = millis();
    _activeLed = 0;
    _lastTailUpdate = 0;
    _pulseVal = 0;
    _pulseRising = true;
}

LEDState LED::getLEDState() const
{
    return _stateManager.getState();
}

void LED::setCustomColor(uint8_t R, uint8_t G, uint8_t B)
{
    _stateManager.setCustomColor(R, G, B);
}

void LED::displaySolidColor(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)
{
    uint32_t color = _ring.Color((R * brightness) / 255, (G * brightness) / 255, (B * brightness) / 255);
    _ring.fill(color);
    _ring.show();
}

void LED::animateRainbowEffect()
{
    uint16_t numPixels = _ring.numPixels();
    for (uint16_t i = 0; i < numPixels; i++)
    {
        uint16_t hue = (millis() / 10 + (i * 256 / numPixels)) & 0xFF;
        _ring.setPixelColor(i, _ring.gamma32(_ring.ColorHSV(hue * 256)));
    }
    _ring.show();
}

void LED::animateTailFade(uint8_t R, uint8_t G, uint8_t B)
{
    uint16_t numPixels = _ring.numPixels();
    _ring.clear();
    _ring.setPixelColor(_activeLed, _ring.Color(R, G, B));
    uint8_t maxBrightness = 50;
    uint8_t tailLen = 9;
    for (uint8_t i = 1; i <= tailLen; i++)
    {
        uint8_t brightness = maxBrightness - (maxBrightness / (tailLen + 1)) * i;
        int index = (_activeLed - i + numPixels) % numPixels;
        _ring.setPixelColor(index, _ring.Color((R * brightness) / maxBrightness, (G * brightness) / maxBrightness, (B * brightness) / maxBrightness));
    }
    _ring.show();

    if (millis() - _lastTailUpdate >= 120)
    {
        _activeLed = (_activeLed + 1) % numPixels;
        _lastTailUpdate = millis();
    }
}

void LED::animatePulse(uint8_t R, uint8_t G, uint8_t B)
{
    const int pulseMax = 24;
    const int pulseMin = 4;
    if (_pulseRising)
    {
        _pulseVal += 1;
        if (_pulseVal >= pulseMax)
        {
            _pulseVal = pulseMax;
            _pulseRising = false;
        }
    }
    else
    {
        if (_pulseVal < pulseMin)
        {
            _pulseVal = pulseMin;
            _pulseRising = true;
        }
        else
        {
            _pulseVal -= 1;
        }
    }
    uint32_t color = _ring.Color((R * _pulseVal) / pulseMax, (G * _pulseVal) / pulseMax, (B * _pulseVal) / pulseMax);
    _ring.fill(color);
    _ring.show();
}

void LED::update()
{
    unsigned long now = millis();
    LEDState currentState = _stateManager.getState();
    switch (currentState)
    {
    case LEDState::SPIN_RAINBOW:
        if (now - _stateStartTime >= EVENT_ANIMATION_MS)
        {
            _stateManager.setState(LEDState::IDLE);
            _ring.clear();
            _ring.show();
        }
        else
        {
            animateRainbowEffect();
        }
        break;
    case LEDState::SPIN_GREEN:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _stateManager.setState(LEDState::IDLE);
            _ring.clear();
            _ring.show();
        }
        else
        {
            animateTailFade(0, 255, 0);
        }
        break;
    case LEDState::SPIN_YELLOW:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _stateManager.setState(LEDState::IDLE);
            _ring.clear();
            _ring.show();
        }
        else
        {
            animateTailFade(255, 255, 0);
        }
        break;
    case LEDState::SPIN_RED:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _stateManager.setState(LEDState::IDLE);
            _ring.clear();
            _ring.show();
        }
        else
        {
            animateTailFade(255, 0, 0);
        }
        break;
    case LEDState::PULSE_RED:
        animatePulse(255, 0, 0);
        break;
    case LEDState::PULSE_BLUE:
        animatePulse(0, 64, 255);
        break;
    case LEDState::IDLE:
        displaySolidColor(_stateManager.customR, _stateManager.customG, _stateManager.customB, 255);
        break;
    case LEDState::OFF:
        displaySolidColor(0, 0, 0, 0);
        break;
    default:
        _ring.clear();
        _ring.show();
        break;
    }
}