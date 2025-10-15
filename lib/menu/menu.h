#pragma once
#include <Arduino.h>
#include "led_segments.h"

#ifndef MENU_PRINT_INTERVAL_MS
#define MENU_PRINT_INTERVAL_MS 200 // Interval for printing menu state to Serial
#endif

enum MenuState
{
    MENU_SELECT_MODE = 0,
    MENU_ADJUST_BRIGHTNESS,
    MENU_ADJUST_COLOR
};

class Menu
{
public:
    Menu(LEDSegments &leds);

    void nextItem(); // Rotary CW
    void prevItem(); // Rotary CCW
    void select();   // Button press
    void back();     // (optioneel)

    void updateDisplay();
    void handleTick(int dir);

private:
    LEDSegments &_leds;
    MenuState _state;
    uint8_t _brightness;
    uint8_t _hue;
    unsigned long _lastPrint;
};