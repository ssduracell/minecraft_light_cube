#include "display_ui.h"

DisplayUI::DisplayUI()
    : _d(OLED_WIDTH, OLED_HEIGHT, &Wire, -1) {}

bool DisplayUI::begin()
{
    if (!_d.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR, false, false))
    {
        return false;
    }
    _d.clearDisplay();
    _d.setTextColor(SSD1306_WHITE);
    _d.setTextSize(1);
    _d.setCursor(0, 0);
    _d.println(F("OLED init..."));
    _d.display();
    return true;
}

void DisplayUI::render(const Menu &menu, const LEDSegments &leds)
{
    unsigned long now = millis();
    if (now - _lastDraw < OLED_UPDATE_INTERVAL_MS)
        return;
    _lastDraw = now;

    _d.clearDisplay();
    drawHeader();
    drawMenu(menu);
    drawFooter(menu, leds);
    _d.display();
}

void DisplayUI::drawHeader()
{
    _d.setTextSize(1);
    _d.setCursor(0, 0);
    _d.println(F("LED Controller"));
    _d.drawLine(0, 10, OLED_WIDTH, 10, SSD1306_WHITE);
}

void DisplayUI::drawMenu(const Menu &menu)
{
    // Drie regels: Mode / Brightness / Color — highlight actuele state
    const int y0 = 14;
    const int lh = 16;

    auto drawRow = [&](int row, const __FlashStringHelper *label, const String &val, bool sel)
    {
        int16_t y = y0 + row * lh;
        if (sel)
            _d.fillRect(0, y - 1, OLED_WIDTH, lh, SSD1306_WHITE);
        _d.setCursor(4, y);
        _d.setTextSize(1);
        if (sel)
            _d.setTextColor(SSD1306_BLACK);
        else
            _d.setTextColor(SSD1306_WHITE);
        _d.print(label);
        _d.print(F(": "));
        _d.println(val);
        if (sel)
            _d.setTextColor(SSD1306_WHITE);
    };

    // Mode value
    String modeVal;
    modeVal.reserve(12);
    switch (menu.currentMode())
    {
    case MODE_STATIC_COLOR:
        modeVal = F("Static");
        break;
    case MODE_BREATHE:
        modeVal = F("Breathe");
        break;
    case MODE_RAINBOW:
        modeVal = F("Rainbow");
        break;
    default:
        modeVal = F("?");
        break;
    }

    drawRow(0, F("Mode"), modeVal, menu.state() == MENU_SELECT_MODE);

    // Brightness + bar
    String br = String(menu.brightness());
    drawRow(1, F("Brightness"), br, menu.state() == MENU_ADJUST_BRIGHTNESS);
    drawBar(64, 14 + 1 * lh + 8, 60, 6, menu.brightness()); // kleine bar rechts

    // Color (Hue 0..255)
    String hue = String(menu.hue());
    drawRow(2, F("Color(H)"), hue, menu.state() == MENU_ADJUST_COLOR);
    drawBar(64, 14 + 2 * lh + 8, 60, 6, menu.hue());
}

void DisplayUI::drawFooter(const Menu & /*menu*/, const LEDSegments & /*leds*/)
{
    _d.drawLine(0, OLED_HEIGHT - 12, OLED_WIDTH, OLED_HEIGHT - 12, SSD1306_WHITE);
    _d.setCursor(0, OLED_HEIGHT - 10);
    _d.setTextSize(1);
    _d.print(F("Rotate: change  | Press: next"));
}

void DisplayUI::drawBar(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t value)
{
    _d.drawRect(x, y, w, h, SSD1306_WHITE);
    int16_t fillw = (int32_t)value * (w - 2) / 255;
    _d.fillRect(x + 1, y + 1, fillw, h - 2, SSD1306_WHITE);
}