#include "led_segments.h"

LEDSegments::LEDSegments(uint8_t pin)
    : _strip(TOTAL_LEDS, pin, NEO_GRB + NEO_KHZ800),
      _mode(MODE_STATIC_COLOR),
      _brightness(128),
      _color(_strip.Color(255, 0, 0)),
      _lastUpdate(0),
      _rainbowOffset(0)
{
}

void LEDSegments::begin()
{
    _strip.begin();
    _strip.setBrightness(_brightness);
    _strip.show();
}

void LEDSegments::setMode(LedMode m)
{
    _mode = m;
    _lastUpdate = 0;
}

void LEDSegments::setBrightness(uint8_t b)
{
    _brightness = constrain(b, 0, 255);
    _strip.setBrightness(_brightness);
}

void LEDSegments::setColor(uint32_t color)
{
    _color = color;
}

void LEDSegments::update()
{
    switch (_mode)
    {
    case MODE_STATIC_COLOR:
        showStatic();
        break;
    case MODE_BREATHE:
        showBreathe();
        break;
    case MODE_RAINBOW:
        showRainbow();
        break;
    }
}

void LEDSegments::showStatic()
{
    for (int i = 0; i < TOTAL_LEDS; i++)
        _strip.setPixelColor(i, _color);
    _strip.show();
}

void LEDSegments::showBreathe()
{
    unsigned long now = millis();
    float phase = (sin(now / 500.0) + 1) / 2; // 0-1
    uint8_t level = (uint8_t)(phase * _brightness);
    _strip.setBrightness(level);
    showStatic();
}

void LEDSegments::showRainbow()
{
    unsigned long now = millis();
    if (now - _lastUpdate < 30)
        return;
    _lastUpdate = now;

    for (int i = 0; i < TOTAL_LEDS; i++)
    {
        int pixelHue = (i * 256 / TOTAL_LEDS + _rainbowOffset) & 255;
        _strip.setPixelColor(i, _strip.gamma32(_strip.ColorHSV(pixelHue * 256)));
    }
    _strip.show();
    _rainbowOffset++;
}