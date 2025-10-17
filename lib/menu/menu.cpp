// #include "menu.h"

// Menu::Menu(LEDSegments &leds)
//     : _leds(leds),
//       _state(MENU_SELECT_MODE),
//       _brightness(128),
//       _hue(0),
//       _lastPrint(0)
// {
// }

// void Menu::handleTick(int dir)
// {
//     switch (_state)
//     {
//     case MENU_SELECT_MODE:
//     {
//         int newMode = (int)_leds.getMode() + dir;
//         if (newMode < 0)
//             newMode = MODE_COUNT - 1;
//         if (newMode >= MODE_COUNT)
//             newMode = 0;
//         _leds.setMode((LedMode)newMode);
//         break;
//     }
//     case MENU_ADJUST_BRIGHTNESS:
//         _brightness = constrain(_brightness + dir * 8, 0, 255);
//         _leds.setBrightness(_brightness);
//         break;
//     case MENU_ADJUST_COLOR:
//         _hue = (_hue + dir * 4) & 0xFF;
//         _leds.setColor(Adafruit_NeoPixel::ColorHSV(_hue * 256));
//         break;
//     }
// }

// void Menu::select()
// {
//     _state = (MenuState)(((int)_state + 1) % 3);
// }

// void Menu::updateDisplay()
// {
//     unsigned long now = millis();
//     if (now - _lastPrint < MENU_PRINT_INTERVAL_MS)
//         return;
//     _lastPrint = now;

//     Serial.print(F("[MENU] State="));
//     switch (_state)
//     {
//     case MENU_SELECT_MODE:
//         Serial.print(F("Mode select: "));
//         switch (_leds.getMode())
//         {
//         case MODE_STATIC_COLOR:
//             Serial.println(F("Static Color"));
//             break;
//         case MODE_BREATHE:
//             Serial.println(F("Breathe"));
//             break;
//         case MODE_RAINBOW:
//             Serial.println(F("Rainbow"));
//             break;
//         }
//         break;
//     case MENU_ADJUST_BRIGHTNESS:
//         Serial.print(F("Brightness="));
//         Serial.println(_brightness);
//         break;
//     case MENU_ADJUST_COLOR:
//         Serial.print(F("Hue="));
//         Serial.println(_hue);
//         break;
//     }
// }

#include "menu.h"

Menu::Menu(LEDSegments &leds)
    : _leds(leds),
      _state(MENU_SELECT_MODE),
      _brightness(128),
      _hue(0),
      _lastPrint(0) {}

void Menu::handleTick(int dir)
{
    switch (_state)
    {
    case MENU_SELECT_MODE:
    {
        int newMode = (int)_leds.getMode() + dir;
        if (newMode < 0)
            newMode = MODE_COUNT - 1;
        if (newMode >= MODE_COUNT)
            newMode = 0;
        _leds.setMode((LedMode)newMode);
        break;
    }
    case MENU_ADJUST_BRIGHTNESS:
        _brightness = constrain(_brightness + dir * 8, 0, 255);
        _leds.setBrightness(_brightness);
        break;
    case MENU_ADJUST_COLOR:
        _hue = (_hue + dir * 4) & 0xFF;
        _leds.setColor(Adafruit_NeoPixel::ColorHSV(_hue * 256));
        break;
    }
}

void Menu::select()
{
    _state = (MenuState)(((int)_state + 1) % 3);
}

void Menu::updateSerialDebug()
{
    unsigned long now = millis();
    if (now - _lastPrint < MENU_PRINT_INTERVAL_MS)
        return;
    _lastPrint = now;

    Serial.print(F("[DBG] "));
    switch (_state)
    {
    case MENU_SELECT_MODE:
        Serial.print(F("Mode="));
        Serial.println((int)_leds.getMode());
        break;
    case MENU_ADJUST_BRIGHTNESS:
        Serial.print(F("Brightness="));
        Serial.println(_brightness);
        break;
    case MENU_ADJUST_COLOR:
        Serial.print(F("Hue="));
        Serial.println(_hue);
        break;
    }
}

const __FlashStringHelper *Menu::stateLabel() const
{
    switch (_state)
    {
    case MENU_SELECT_MODE:
        return F("Mode");
    case MENU_ADJUST_BRIGHTNESS:
        return F("Brightness");
    case MENU_ADJUST_COLOR:
        return F("Color");
    }
    return F("?");
}

const __FlashStringHelper *Menu::modeName(LedMode m) const
{
    switch (m)
    {
    case MODE_STATIC_COLOR:
        return F("Static");
    case MODE_BREATHE:
        return F("Breathe");
    case MODE_RAINBOW:
        return F("Rainbow");
    default:
        return F("Unknown");
    }
}