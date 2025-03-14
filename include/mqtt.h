#pragma once

#include "PubSubClient.h"
#include "state.h"

#ifndef WIFI_SSID
    #define WIFI_SSID ""
#endif // WIFI_SSID

#ifndef WIFI_PASS
    #define WIFI_PASS ""
#endif // WIFI_PASS

#ifndef MQTT_SERVER
    #define MQTT_SERVER ""
#endif // MQTT_SERVER

#ifndef MQTT_PORT
    #define MQTT_PORT 0
#endif // MQTT_PORT

#ifndef MQTT_TOPIC
    #define MQTT_TOPIC ""
#endif // MQTT_TOPIC

void connect_wifi();
void connect_mqtt(PubSubClient client);
void publish_data(PubSubClient client, const Data* data);

