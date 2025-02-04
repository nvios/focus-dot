#include "hardware/LED.h"
#include "hardware/Display.h"

// Initialize static constants
const unsigned long LED::EVENT_ANIMATION_MS = 60000;
const unsigned long LED::VOC_ANIMATION_MS = 60000;
const unsigned long LED::VOC_RED_PULSE_MS = 300000;

// Constructor
LED::LED(uint8_t pin, uint16_t numPixels)
    : _ring(numPixels, pin, NEO_GRB + NEO_KHZ800),
      _currentLEDState(LEDState::IDLE),
      _stateStartTime(0),
      _activeLed(0),
      _lastTailUpdate(0),
      _pulseVal(0),
      _pulseRising(true)
{
}

// Initialize the LED strip
void LED::begin()
{
    _ring.begin();
    _ring.clear();
    _ring.show();
    _currentLEDState = LEDState::IDLE;
}

// Set the current LED state and reset animation variables
void LED::setLEDState(LEDState newState)
{
    _currentLEDState = newState;
    _stateStartTime = millis();
    // Reset animation variables
    _activeLed = 0;
    _lastTailUpdate = 0;
    _pulseVal = 0;
    _pulseRising = true;
}

// Update LEDs based on the current state
void LED::update()
{
    unsigned long now = millis();

    switch (_currentLEDState)
    {
    case LEDState::EVENT_RAINBOW:
        if (now - _stateStartTime >= EVENT_ANIMATION_MS)
        {
            _currentLEDState = LEDState::IDLE;
        }
        else
        {
            animateRainbowTail();
        }
        break;

    case LEDState::VOC_GREEN:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _currentLEDState = LEDState::IDLE;
        }
        else
        {
            animateSolidTail(0, 255, 0);
        }
        break;

    case LEDState::VOC_YELLOW:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _currentLEDState = LEDState::IDLE;
        }
        else
        {
            animateSolidTail(255, 255, 0);
        }
        break;

    case LEDState::VOC_RED:
        if (now - _stateStartTime >= VOC_ANIMATION_MS)
        {
            _currentLEDState = LEDState::VOC_RED_PULSE;
            _stateStartTime = now;
        }
        else
        {
            animateSolidTail(255, 0, 0);
        }
        break;

    case LEDState::VOC_RED_PULSE:
        if (now - _stateStartTime >= VOC_RED_PULSE_MS)
        {
            _currentLEDState = LEDState::IDLE;
        }
        else
        {
            animateRedPulse();
        }
        break;

    case LEDState::IDLE:
    default:
        _ring.clear();
        _ring.show();
        break;
    }
}

// Animate a tail fade with a given color function
void LED::animateTailFade(std::function<uint32_t(int)> colorFunc, uint8_t tailLen, unsigned long stepTime)
{
    unsigned long now = millis();
    if (now - _lastTailUpdate >= stepTime)
    {
        _lastTailUpdate = now;
        _activeLed = (_activeLed + 1) % _ring.numPixels();

        _ring.clear();
        for (int i = 0; i < _ring.numPixels(); i++)
        {
            int dist = (_activeLed + _ring.numPixels() - i) % _ring.numPixels();
            if (dist < tailLen)
            {
                uint8_t b = ((tailLen - 1 - dist) * 255) / (tailLen - 1);
                uint32_t color = colorFunc(i);

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b_ = (color)&0xFF;

                r = (r * b) / 255;
                g = (g * b) / 255;
                b_ = (b_ * b) / 255;
                _ring.setPixelColor(i, r, g, b_);
            }
        }
        _ring.show();
    }
}

// Animate a rainbow tail
void LED::animateRainbowTail()
{
    animateTailFade(
        [&](int i) -> uint32_t
        {
            uint16_t pixelHue = i * (65535L / _ring.numPixels());
            return _ring.ColorHSV(pixelHue, 255, 255);
        });
}

// Animate a solid color tail
void LED::animateSolidTail(uint8_t R, uint8_t G, uint8_t B)
{
    animateTailFade([&](int i) -> uint32_t
                    { return _ring.Color(R, G, B); });
}

// Animate a red pulse effect
void LED::animateRedPulse()
{
    if (_pulseRising)
    {
        _pulseVal += 5;
        if (_pulseVal >= 255)
        {
            _pulseVal = 255;
            _pulseRising = false;
        }
    }
    else
    {
        _pulseVal -= 5;
        if (_pulseVal <= 0)
        {
            _pulseVal = 0;
            _pulseRising = true;
        }
    }

    _ring.fill(_ring.Color(_pulseVal, 0, 0));
    _ring.show();
}