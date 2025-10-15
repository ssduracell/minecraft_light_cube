#pragma once
#include <Arduino.h>

class Button
{
public:
    explicit Button(uint8_t pin, bool pullup = true, uint16_t debounceMs = 15);

    void begin();

    // Call in loop(); geeft edge-events terug
    bool fell(); // HIGH->LOW (met INPUT_PULLUP: knop ingedrukt)
    bool rose(); // LOW->HIGH

    // Huidige stabiele staat
    bool isPressed() const { return _stableState == _activeLevel; }

private:
    uint8_t _pin;
    bool _usePullup;
    uint16_t _debounceMs;
    uint8_t _activeLevel; // 0 als pullup, 1 anders

    // debounce state
    uint8_t _stableState;
    uint8_t _lastRead;
    uint32_t _lastChangeMs;
    bool _fellEvent;
    bool _roseEvent;

    void update();
};