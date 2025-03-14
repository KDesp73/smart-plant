#include "mqtt.h"
#include "PubSubClient.h"
#include "state.h"
#include <WiFi.h>

void connect_wifi()
{
    Serial.printf("Connecting to %s", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected");
}

void connect_mqtt(PubSubClient client)
{
    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect("ESP32Client")) {
            Serial.println("Connected");
        } else {
            Serial.print("Failed, retrying in 5s...");
            delay(5000);
        }
    }
}

void publish_data(PubSubClient client, const Data* data)
{
    char payload[50];
    snprintf(payload, sizeof(payload), "{\"temp\": %.2f, \"hum\": %.2f}", data->temperature, data->humidity); // TODO: better serialization
    client.publish(MQTT_TOPIC, payload);
    Serial.println("Published: " + String(payload));
}
