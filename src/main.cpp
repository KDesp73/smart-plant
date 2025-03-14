#include "state.h"
#include "oled.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>

// Initialize OLED (I2C, SSD1306)
Oled oled(U8G2_R0, /* SCL=*/ 22, /* SDA=*/ 21, /* RST=*/ U8X8_PIN_NONE);

// Dummy sensor values TODO: Replace with actual sensor readings
State state = {
    .data = {
        .temperature = 22,
        .moisture = 40,
        .light = 85
    },
    .waterPump = false
};


void setup() {
    oled.begin();
}

void loop() {
    oled_dashboard(oled, &state);

    collect_data(&state.data);
    update_state(&state);

    delay(1000); // Update every second
}
