#pragma once

#include "WString.h"
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
} State;

void update_state(State* state);
