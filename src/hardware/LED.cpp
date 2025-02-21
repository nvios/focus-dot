#include "hardware/LED.h"
#include "hardware/Display.h"
#include <math.h>

const unsigned long LED::EVENT_ANIMATION_MS = 60000;
const unsigned long LED::VOC_ANIMATION_MS = 20000;
const unsigned long LED::VOC_RED_PULSE_MS = 300000;

LED::LED(uint8_t pin, uint16_t numPixels)
    : _ring(numPixels, pin, NEO_GRB + NEO_KHZ800),
      _currentLEDState(LEDState::IDLE), _stateStartTime(0),
      _activeLed(0), _lastTailUpdate(0), _pulseVal(0), _pulseRising(true) {}

void LED::begin()
{
    _ring.begin();
    _ring.clear();
    _ring.show();
    _currentLEDState = LEDState::IDLE;
}

void LED::setLEDState(LEDState newState)
{
    _currentLEDState = newState;
    _stateStartTime = millis();
    _activeLed = 0;
    _lastTailUpdate = 0;
    _pulseVal = 0;
    _pulseRising = true;
}

void LED::update()
{
    unsigned long now = millis();
    switch (_currentLEDState)
    {
    case LEDState::SPIN_RAINBOW:
        if (now - _stateStartTime >= EVENT_ANIMATION_MS)
            _currentLEDState = LEDState::IDLE;
        else
            animateRainbowTail();
        break;
    case LEDState::SPIN_GREEN:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
            _currentLEDState = LEDState::IDLE;
        else
            animateSolidTail(0, 255, 0);
        break;
    case LEDState::SPIN_YELLOW:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
            _currentLEDState = LEDState::IDLE;
        else
            animateSolidTail(255, 255, 0);
        break;
    case LEDState::SPIN_RED:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _currentLEDState = LEDState::PULSE_RED;
            _stateStartTime = now;
        }
        else
        {
            animateSolidTail(255, 0, 0);
        }
        break;
    case LEDState::PULSE_RED:
        if (now - _stateStartTime >= VOC_RED_PULSE_MS)
            _currentLEDState = LEDState::IDLE;
        else
            animatePulse(255, 0, 0);
        break;
    case LEDState::PULSE_BLUE:
            animatePulse(0, 64, 255);
        break;
    case LEDState::SOLID_BLUE:
        displaySolidColor(0, 0, 255, 30);
        break;
    case LEDState::IDLE:
    default:
        _ring.clear();
        _ring.show();
        break;
    }
}

void LED::animateTailFade(std::function<uint32_t(int)> colorFunc, uint8_t tailLen, unsigned long stepTime)
{
    if (millis() - _lastTailUpdate >= stepTime)
    {
        _lastTailUpdate = millis();
        _activeLed = (_activeLed + 1) % _ring.numPixels();
        _ring.clear();
        for (int i = 0; i < _ring.numPixels(); i++)
        {
            int dist = (_activeLed + _ring.numPixels() - i) % _ring.numPixels();
            if (dist < tailLen)
            {
                uint8_t intensity = (uint8_t)(pow((float)(tailLen - 1 - dist) / (tailLen - 1), 2) * 50);
                uint32_t color = colorFunc(i);
                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;
                _ring.setPixelColor(i, (r * intensity) / 255, (g * intensity) / 255, (b * intensity) / 255);
            }
        }
        _ring.show();
    }
}

void LED::animateRainbowTail()
{
    animateTailFade([&](int i) -> uint32_t
                    {
        uint16_t pixelHue = i * (65535L / _ring.numPixels());
        return _ring.ColorHSV(pixelHue, 255, 255); });
}

void LED::animateSolidTail(uint8_t R, uint8_t G, uint8_t B)
{
    animateTailFade([&](int) -> uint32_t
                    { return _ring.Color(R, G, B); });
}

void LED::animatePulse(uint8_t R, uint8_t G, uint8_t B)
{
    _pulseVal = _pulseRising ? _pulseVal + 5 : _pulseVal - 5;
    if (_pulseVal >= 255)
    {
        _pulseVal = 255;
        _pulseRising = false;
    }
    else if (_pulseVal <= 0)
    {
        _pulseVal = 0;
        _pulseRising = true;
    }
    _ring.fill(_ring.Color((R * _pulseVal) / 255, (G * _pulseVal) / 255, (B * _pulseVal) / 255));
    _ring.show();
}

void LED::displaySolidColor(uint8_t R, uint8_t G, uint8_t B, uint8_t brightness)
{
    _ring.fill(_ring.Color((R * brightness) / 255, (G * brightness) / 255, (B * brightness) / 255));
    _ring.show();
}