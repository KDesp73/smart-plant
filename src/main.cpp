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
    .needs = {
        .waterInterval   = PLANT_WATERING_INTERVAL,
        .light_min       = PLANT_LIGHT_MIN,
        .light_max       = PLANT_LIGHT_MAX,
        .moisture_min    = PLANT_MOISTURE_MIN,
        .moisture_max    = PLANT_MOISTURE_MAX,
        .temperature_min = PLANT_TEMPERATURE_MIN,
        .temperature_max = PLANT_TEMPERATURE_MAX,
        .humidity_min    = PLANT_HUMIDITY_MIN,
        .humidity_max    = PLANT_HUMIDITY_MAX
    }
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

    needs_print(&state.needs);
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

    EVERY_MS(wateringTimer, state.needs.waterInterval, {
        if(needsWater(&state)) {
            send_notification("Plant Watering Alert", "The plant needs watering!");
        }
        if(tooMuchWater(&state)) {
            send_notification("Plant Watering Alert", "The plant is drowning!");
        }
    })

    EVERY_MS(envTimer, 10000, {
        if(needsLight(&state)) {
            send_notification("Plant Lighting Alert", "The plant needs more light!");
        }
        if(tooMuchLight(&state)) {
            send_notification("Plant Lighting Alert", "The plant needs less light!");
        }
        if(needsWarmth(&state)) {
            send_notification("Plant Temperature Alert", "The plant is cold!");
        }
        if(tooMuchWarmth(&state)) {
            send_notification("Plant Temperature Alert", "The plant is burning!");
        }
        if(needsHumidity(&state)) {
            send_notification("Plant Humidity Alert", "The environment is not humid enough!");
        }
        if(tooMuchHumidity(&state)) {
            send_notification("Plant Humidity Alert", "The environment is too humid!");
        }
    })

    if(mqttEnabled) {
        EVERY_MS(mqttTimer, 30000, {
            publish_data(&client, &state.data);
        })
    }
}
