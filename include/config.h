#pragma once

// --- Pins ---
#define PIN_ENC_A D5
#define PIN_ENC_B D6
#define PIN_BTN D7
#define PIN_LED D4 // WS2812/SK6812

// --- LED-config ---
#define LEDS_PER_SEGMENT 12
#define SEGMENT_COUNT 6
#define TOTAL_LEDS (LEDS_PER_SEGMENT * SEGMENT_COUNT)

// --- Debounce & timing ---
#define BUTTON_DEBOUNCE_MS 15
#define MENU_PRINT_INTERVAL_MS 400 // alleen serial debug throttling

// --- OLED (SSD1306 I2C) ---
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C
#define OLED_UPDATE_INTERVAL_MS 100