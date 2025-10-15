#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#ifndef TOTAL_LEDS
#define TOTAL_LEDS 72 // Default total number of LEDs
#endif

enum LedMode
{
    MODE_STATIC_COLOR = 0,
    MODE_BREATHE,
    MODE_RAINBOW,
    MODE_COUNT
};

class LEDSegments
{
public:
    explicit LEDSegments(uint8_t pin);

    void begin();
    void update();

    // Mode management
    void setMode(LedMode m);
    LedMode getMode() const { return _mode; }

    void setBrightness(uint8_t b);
    void setColor(uint32_t color);

private:
    Adafruit_NeoPixel _strip;
    LedMode _mode;
    uint8_t _brightness;
    uint32_t _color;
    unsigned long _lastUpdate;
    uint16_t _rainbowOffset;

    void showStatic();
    void showBreathe();
    void showRainbow();
};