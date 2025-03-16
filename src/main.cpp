#include "esp32-hal.h"
#include "light.h"
#include "mqtt.h"
#include "oled.h"
#include "state.h"
#include "temperature.h"
#include "timer.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include "PubSubClient.h"
#include <U8g2lib.h>
#include <WiFi.h>
#include <Wire.h>

// Initialize OLED (I2C, SSD1306)
Oled oled(U8G2_R0, /* SCL=*/ 22, /* SDA=*/ 21, /* RST=*/ U8X8_PIN_NONE);
DHT_Unified dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

State state = {0};

uint32_t delayMS;

void setup() {
    Serial.begin(115200);
    delay(2000);
    oled.begin();
    dht.begin();

    // mqtt_init(&client);

    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;
}

void loop() {
    // if (!client.connected()) {
    //     connect_mqtt(&client);
    // }
    // client.loop();

    EVERY_MS(sensorsTimer, 2000, {
        read_dht22(dht, &state.data);
        read_light(&state.data);
        data_print(&state.data);
    })

    oled_dashboard(oled, &state);

    update_state(&state);

    // EVERY_MS(mqttTimer, 5000, {
    //     publish_data(&client, &state.data);
    // })
}
