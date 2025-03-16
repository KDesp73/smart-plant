#include "mqtt.h"
#include "notification.h"
#include "oled.h"
#include "state.h"
#include "sensors.h"
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
#include <WiFiClientSecure.h>

Oled oled(U8G2_R0, /* SCL=*/ 22, /* SDA=*/ 21, /* RST=*/ U8X8_PIN_NONE);
DHT_Unified dht(DHTPIN, DHTTYPE);
WiFiClientSecure espClient;
PubSubClient client(espClient);

State state = {
    .waterInterval = 150000
};

uint32_t delayMS;

#define SWITCH_PIN 5
static bool mqttEnabled = false;

void setup() {
    Serial.begin(115200);
    delay(2000);
    oled.begin();
    dht.begin();
    pinMode(SWITCH_PIN, INPUT_PULLUP);

    espClient.setInsecure();
    mqtt_init(&client);

    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;
}

void loop() {
    mqttEnabled = (digitalRead(SWITCH_PIN) == LOW);

    if (!client.connected()) {
        connect_mqtt(&client);
    }
    client.loop();

    EVERY_MS(sensorsTimer, delayMS, {
        read_dht22(dht, &state.data);
        read_light(&state.data);
        read_soil(&state.data);
        data_print(&state.data);
    })

    oled_dashboard(oled, &state);

    update_state(&state);

    EVERY_MS(wateringTimer, state.waterInterval, {
        if(state.waterPump) {
            send_water_notification("The plant needs watering!");
        }
    })

    if(mqttEnabled) {
        EVERY_MS(mqttTimer, 30000, {
            publish_data(&client, &state.data);
        })
    }
}
