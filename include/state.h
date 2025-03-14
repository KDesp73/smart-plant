#pragma once

typedef struct {
    float temperature;
    float humidity;
    float moisture;
    float light;
} Data;

typedef struct {
    Data data;
    bool waterPump;
} State;

void update_state(State* state);
