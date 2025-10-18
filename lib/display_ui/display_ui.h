#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <sh1106.h>
#include "config.h"
#include "menu.h"
#include "led_segments.h"

#ifndef OLED_WIDTH
#define OLED_WIDTH 128 // Default OLED width
#endif
#ifndef OLED_HEIGHT
#define OLED_HEIGHT 64 // Default OLED height
#endif
#ifndef OLED_ADDR
#define OLED_ADDR 0x3C // Default I2C address for SSD1306
#endif
#ifndef OLED_UPDATE_INTERVAL_MS
#define OLED_UPDATE_INTERVAL_MS 100 // Default update interval for OLED
#endif

class DisplayUI
{
public:
    DisplayUI();
    bool begin(); // init SSD1306
    void render(const Menu &menu, const LEDSegments &leds);

private:
    Adafruit_SSD1306 _d;
    unsigned long _lastDraw = 0;

    void drawHeader();
    void drawMenu(const Menu &menu);
    void drawFooter(const Menu &menu, const LEDSegments &leds);
    void drawBar(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t value /*0..255*/);
};