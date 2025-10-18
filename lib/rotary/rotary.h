#pragma once
#include <Arduino.h>

class Rotary
{
public:
    Rotary(uint8_t pinA, uint8_t pinB, uint8_t led_green, uint8_t led_red);

    void begin();

    // Safe read van absolute positie in 'ticks' (transities)
    long read();

    // Reset naar 0
    void reset();

    // Wordt aangeroepen door de ISRs
    void handleISR();

    // LED status
    void setGreenLED(bool on);
    void setRedLED(bool on);

private:
    uint8_t _pinA, _pinB;
    uint8_t _led_green, _led_red;
    volatile long _position;     // in transitie-ticks
    volatile uint8_t _lastState; // 2-bit (A<<1 | B)
};