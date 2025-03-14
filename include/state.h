#pragma once

typedef struct {
    int temperature;
    int moisture;
    int light;
} Data;

typedef struct {
    Data data;
    bool waterPump;
} State;

void collect_data(Data* data);
void update_state(State* state);
