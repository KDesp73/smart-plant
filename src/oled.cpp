#include "oled.h"
#include "state.h"

void oled_dashboard(Oled oled, const State* state)
{
    oled.clearBuffer();
    oled.setFont(u8g2_font_6x13_tr);

    // Row 1: Text info
    oled.setCursor(5, 12);
    oled.print("Soil: ");
    oled.print(state->data.moisture);
    oled.print("%  Temp: ");
    oled.print(state->data.temperature);
    oled.print("C");

    // Row 2: Light and Water
    oled.setCursor(5, 25);
    oled.print("Light: ");
    oled.print(state->data.light);
    oled.print("% Water: ");
    oled.print(state->waterPump ? "ON" : "OFF");

    // Moisture bar
    oled.drawXBMP(5, 38, 16, 16, icon_moisture);
    oled.drawFrame(25, 40, 100, 8);
    oled.drawBox(25, 40, state->data.moisture, 8); 

    // Light Icon + Progress Bar
    oled.drawXBMP(5, 53, 16, 16, icon_light);
    oled.drawFrame(25, 55, 100, 8);
    oled.drawBox(25, 55, state->data.light, 8);  

    oled.sendBuffer();
}
