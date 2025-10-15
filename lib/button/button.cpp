#include "Button.h"

Button::Button(uint8_t pin, bool pullup, uint16_t debounceMs)
    : _pin(pin),
      _usePullup(pullup),
      _debounceMs(debounceMs),
      _activeLevel(pullup ? LOW : HIGH),
      _stableState(pullup ? HIGH : LOW),
      _lastRead(_stableState),
      _lastChangeMs(0),
      _fellEvent(false),
      _roseEvent(false) {}

void Button::begin()
{
    pinMode(_pin, _usePullup ? INPUT_PULLUP : INPUT);
}

void Button::update()
{
    uint8_t r = digitalRead(_pin);
    uint32_t now = millis();

    if (r != _lastRead)
    {
        _lastRead = r;
        _lastChangeMs = now;
    }

    if ((now - _lastChangeMs) >= _debounceMs)
    {
        if (_stableState != _lastRead)
        {
            // Edge gedebounced
            bool wasPressed = (_stableState == _activeLevel);
            _stableState = _lastRead;
            bool nowPressed = (_stableState == _activeLevel);

            _fellEvent = (!wasPressed && nowPressed);
            _roseEvent = (wasPressed && !nowPressed);
        }
    }
}

bool Button::fell()
{
    update();
    bool e = _fellEvent;
    _fellEvent = false;
    return e;
}

bool Button::rose()
{
    update();
    bool e = _roseEvent;
    _roseEvent = false;
    return e;
}