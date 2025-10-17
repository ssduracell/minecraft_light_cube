// // #pragma once
// // #include <Arduino.h>
// // #include "led_segments.h"

// // #ifndef MENU_PRINT_INTERVAL_MS
// // #define MENU_PRINT_INTERVAL_MS 200 // Interval for printing menu state to Serial
// // #endif

// // enum MenuState
// // {
// //     MENU_SELECT_MODE = 0,
// //     MENU_ADJUST_BRIGHTNESS,
// //     MENU_ADJUST_COLOR
// // };

// // class Menu
// // {
// // public:
// //     Menu(LEDSegments &leds);

// //     void nextItem(); // Rotary CW
// //     void prevItem(); // Rotary CCW
// //     void select();   // Button press
// //     void back();     // (optioneel)

// //     void updateDisplay();
// //     void handleTick(int dir);

// // private:
// //     LEDSegments &_leds;
// //     MenuState _state;
// //     uint8_t _brightness;
// //     uint8_t _hue;
// //     unsigned long _lastPrint;
// // };

// #include <Arduino.h>
// #include "Config.h"
// #include <Rotary.h>
// #include <Button.h>
// #include "LEDSegments.h"
// #include "Menu.h"
// #include "DisplayUI.h"

// Rotary encoder(PIN_ENC_A, PIN_ENC_B);
// Button button(PIN_BTN, true, BUTTON_DEBOUNCE_MS);
// LEDSegments leds(PIN_LED);
// Menu menu(leds);
// DisplayUI ui;

// long lastPos = 0;

// void setup()
// {
//     Serial.begin(SERIAL_BAUD);
//     Serial.println("\n=== Boot ===");

//     encoder.begin();
//     button.begin();
//     leds.begin();

//     Wire.begin(); // NodeMCU: SDA=D2, SCL=D1
//     if (!ui.begin())
//     {
//         Serial.println(F("[ERR] OLED init failed (addr 0x3C?)"));
//     }
//     else
//     {
//         Serial.println(F("[OK] OLED ready"));
//     }
// }

// void loop()
// {
//     long pos = encoder.read();
//     long delta = pos - lastPos;
//     if (delta != 0)
//     {
//         int dir = (delta > 0) ? +1 : -1;
//         menu.handleTick(dir);
//         lastPos = pos;
//     }

//     if (button.fell())
//     {
//         menu.select();
//     }

//     // Serial blijft debug-only en rustig
//     menu.updateSerialDebug();

//     // LEDs & Display updaten
//     leds.update();
//     ui.render(menu, leds);

//     delay(1);
// }
#pragma once
#include <Arduino.h>
#include "led_segments.h"
#include "config.h"

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

    void handleTick(int dir); // rotary delta
    void select();            // button press
    void updateSerialDebug(); // alleen seriële debug

    // === UI getters ===
    MenuState state() const { return _state; }
    uint8_t brightness() const { return _brightness; }
    uint8_t hue() const { return _hue; }
    LedMode currentMode() const { return _leds.getMode(); }
    const __FlashStringHelper *stateLabel() const;
    const __FlashStringHelper *modeName(LedMode m) const;

private:
    LEDSegments &_leds;
    MenuState _state;
    uint8_t _brightness;
    uint8_t _hue;
    unsigned long _lastPrint;
};