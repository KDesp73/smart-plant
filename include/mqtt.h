#pragma once

#include "PubSubClient.h"
#include "env.h"
#include "state.h"

#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)

void connect_wifi();
void connect_mqtt(PubSubClient* client);
void publish_data(PubSubClient* client, const Data* data);

static inline void mqtt_init(PubSubClient* client)
{
    const char* server = MQTT_SERVER;
    const long port = MQTT_PORT;
    connect_wifi();
    client->setServer(server, port);
    connect_mqtt(client);
}
