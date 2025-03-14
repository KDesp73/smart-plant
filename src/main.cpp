#include "state.h"
#include "oled.h"
#include "temperature.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <U8g2lib.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Initialize OLED (I2C, SSD1306)
Oled oled(U8G2_R0, /* SCL=*/ 22, /* SDA=*/ 21, /* RST=*/ U8X8_PIN_NONE);

#define DHTPIN 4
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);


// Dummy sensor values TODO: Replace with actual sensor readings
State state = {
    .data = {
        .temperature = 22,
        .moisture = 40,
        .light = 85
    },
    .waterPump = false
};

uint32_t delayMS;

void setup() {
    Serial.begin(115200);
    oled.begin();
    dht.begin();

    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;
}

void loop() {
    read_dht22(dht, &state.data);

    oled_dashboard(oled, &state);

    update_state(&state);

    delay(1000); // Update every second
}
