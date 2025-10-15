#include "rotary.h"

#if defined(ESP8266)
#define ISR_ATTR ICACHE_RAM_ATTR
#else
#define ISR_ATTR
#endif

// Quadrature transitie-tabel (delta op basis van vorige en huidige 2-bit toestand)
// Index = (lastState<<2) | newState
// Waardes: -1, 0, +1 (half-step resolutie)
static const int8_t kDelta[16] = {
    0, -1, +1, 0,
    +1, 0, 0, -1,
    -1, 0, 0, +1,
    0, +1, -1, 0};

static Rotary *s_instanceA = nullptr; // simpele singleton-koppeling voor ISRs
static Rotary *s_instanceB = nullptr;

static void ISR_ATTR isrA()
{
    if (s_instanceA)
        s_instanceA->handleISR();
}
static void ISR_ATTR isrB()
{
    if (s_instanceB)
        s_instanceB->handleISR();
}

Rotary::Rotary(uint8_t pinA, uint8_t pinB)
    : _pinA(pinA), _pinB(pinB), _position(0), _lastState(0) {}

void Rotary::begin()
{
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);

    uint8_t a = digitalRead(_pinA);
    uint8_t b = digitalRead(_pinB);
    _lastState = (a << 1) | b;

    // Koppel beide ISRs (CHANGE op A en B)
    s_instanceA = this;
    s_instanceB = this;
    attachInterrupt(digitalPinToInterrupt(_pinA), isrA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(_pinB), isrB, CHANGE);
}

long Rotary::read()
{
    noInterrupts();
    long val = _position;
    interrupts();
    return val;
}

void Rotary::reset()
{
    noInterrupts();
    _position = 0;
    interrupts();
}

void Rotary::handleISR()
{
    uint8_t a = digitalRead(_pinA);
    uint8_t b = digitalRead(_pinB);
    uint8_t newState = (a << 1) | b;

    uint8_t idx = (_lastState << 2) | (newState & 0x03);
    _lastState = newState;

    int8_t d = kDelta[idx];
    if (d != 0)
    {
        _position += d;
    }
}