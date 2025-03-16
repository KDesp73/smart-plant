#pragma once

#include "DHT_U.h"
#include "state.h"

#define DHTPIN 4
#define DHTTYPE DHT22
void read_dht22(DHT_Unified dht, Data* data);

#define LIGHT_PIN 32
void read_light(Data* data);

#define SOIL_PIN 33
void read_soil(Data* data);
