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
    uint32_t waterInterval;
    float light_min;
    float light_max;
    float moisture_min;
    float moisture_max;
    float temperature_min;
    float temperature_max;
    float humidity_min;
    float humidity_max;
} PlantNeeds;

void needs_print(const PlantNeeds* needs);

typedef struct {
    Data data;
    PlantNeeds needs;
} State;

static inline bool needsWater(const State* state)
{
    return state->data.moisture < state->needs.moisture_min;
}
static inline bool tooMuchWater(const State* state)
{
    return state->data.moisture > state->needs.moisture_max;
}
static inline bool needsLight(const State* state)
{
    return state->data.light < state->needs.light_min; 
}
static inline bool tooMuchLight(const State* state)
{
    return state->data.light > state->needs.light_max; 
}
static inline bool needsWarmth(const State* state)
{
    return state->data.temperature < state->needs.temperature_min;
}
static inline bool tooMuchWarmth(const State* state)
{
    return state->data.temperature > state->needs.temperature_max;
}
static inline bool needsHumidity(const State* state)
{
    return state->data.humidity < state->needs.humidity_min;
}
static inline bool tooMuchHumidity(const State* state)
{
    return state->data.humidity > state->needs.humidity_max;
}    

#ifndef PLANT_LIGHT_MIN
    #define PLANT_LIGHT_MIN 0
#endif // PLANT_LIGHT_MIN
#ifndef PLANT_LIGHT_MAX
    #define PLANT_LIGHT_MAX 0
#endif // PLANT_LIGHT_MAX
#ifndef PLANT_MOISTURE_MIN
    #define PLANT_MOISTURE_MIN 0
#endif // PLANT_MOISTURE_MIN
#ifndef PLANT_MOISTURE_MAX
    #define PLANT_MOISTURE_MAX 0
#endif // PLANT_MOISTURE_MAX
#ifndef PLANT_HUMIDITY_MIN
    #define PLANT_HUMIDITY_MIN 0
#endif // PLANT_HUMIDITY_MIN
#ifndef PLANT_HUMIDITY_MAX
    #define PLANT_HUMIDITY_MAX 0
#endif // PLANT_HUMIDITY_MAX
#ifndef PLANT_TEMPERATURE_MIN
    #define PLANT_TEMPERATURE_MIN 0
#endif // PLANT_TEMPERATURE_MIN
#ifndef PLANT_TEMPERATURE_MAX
    #define PLANT_TEMPERATURE_MAX 0
#endif // PLANT_TEMPERATURE_MAX
#ifndef PLANT_WATERING_INTERVAL
    #define PLANT_WATERING_INTERVAL 0
#endif // PLANT_WATERING_INTERVAL

