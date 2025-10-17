// #include <Arduino.h>
// #include "config.h"
// #include <rotary.h>
// #include <button.h>
// #include "led_segments.h"
// #include "menu.h"

// Rotary encoder(PIN_ENC_A, PIN_ENC_B);
// Button button(PIN_ENC_BTN, true, BUTTON_DEBOUNCE_MS);
// LEDSegments leds(PIN_LED);
// Menu menu(leds);

// long lastPos = 0;

// void setup()
// {
//   Serial.begin(SERIAL_BAUD);
//   Serial.println("\n=== LED Menu Controller ===");
//   encoder.begin();
//   button.begin();
//   leds.begin();
// }

// void loop()
// {
//   long pos = encoder.read();
//   long delta = pos - lastPos;
//   if (delta != 0)
//   {
//     int dir = (delta > 0) ? +1 : -1;
//     menu.handleTick(dir);
//     lastPos = pos;
//   }

//   if (button.fell())
//   {
//     menu.select();
//   }

//   menu.updateDisplay();
//   leds.update();

//   delay(1);
// }
#include <Arduino.h>
#include "config.h"
#include <rotary.h>
#include <button.h>
#include "led_segments.h"
#include "menu.h"
#include "display_ui.h"

Rotary encoder(PIN_ENC_A, PIN_ENC_B);
Button button(PIN_ENC_BTN, true, BUTTON_DEBOUNCE_MS);
LEDSegments leds(PIN_LED);
Menu menu(leds);
DisplayUI ui;

long lastPos = 0;

void setup()
{
  Serial.begin(SERIAL_BAUD);
  Serial.println("\n=== Boot ===");

  encoder.begin();
  button.begin();
  leds.begin();

  Wire.begin(); // NodeMCU: SDA=D2, SCL=D1
  if (!ui.begin())
  {
    Serial.println(F("[ERR] OLED init failed (addr 0x3C?)"));
  }
  else
  {
    Serial.println(F("[OK] OLED ready"));
  }
}

void loop()
{
  long pos = encoder.read();
  long delta = pos - lastPos;
  if (delta != 0)
  {
    int dir = (delta > 0) ? +1 : -1;
    menu.handleTick(dir);
    lastPos = pos;
  }

  if (button.fell())
  {
    menu.select();
  }

  // Serial blijft debug-only en rustig
  menu.updateSerialDebug();

  // LEDs & Display updaten
  leds.update();
  ui.render(menu, leds);

  delay(1);
}