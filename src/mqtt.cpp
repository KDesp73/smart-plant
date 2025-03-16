#include "mqtt.h"
#include "HardwareSerial.h"
#include "PubSubClient.h"
#include "env.h"
#include "state.h"
#include <WiFi.h>

void connect_wifi()
{
    delay(10);
    const char* ssid = WIFI_SSID;
    const char* pass = WIFI_PASS;
    Serial.printf("Connecting to %s", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void connect_mqtt(PubSubClient* client)
{
    while (!client->connected()) {
        Serial.print("Connecting to MQTT...");
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        if (client->connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
            Serial.println("Connected");
        } else {
            Serial.println("\nFailed, retrying in 5s...");
            Serial.printf("State: %d\n", client->state());
            delay(5000);
        }
    }
}

void publish_data(PubSubClient* client, const Data* data)
{
    String payload = data_serialize(data);

    const char* topic = MQTT_TOPIC;
    client->publish(topic, payload.c_str());
    Serial.println("Published: " + String(payload));
}
