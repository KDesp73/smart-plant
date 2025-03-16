#pragma once

#include "WString.h"
#include <cstdint>
typedef struct {
    float temperature;
    float humidity;
    float moisture;
    float light;
} Data;

void data_print(const Data* data);
String data_serialize(const Data* data);

typedef struct {
    Data data;
    bool waterPump;
    uint32_t waterInterval;
} State;

void update_state(State* state);

#define MOISTURE_THRESHOLD 30.0f
