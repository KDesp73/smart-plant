#include "state.h"

void collect_data(Data* data)
{
    // Simulate sensor changes (replace with real sensor readings)
    data->moisture = (data->moisture + 1) % 100;
    data->light = (data->light - 1) % 100;
}

void update_state(State* state)
{
    state->waterPump = (state->data.moisture < 30);  // Auto turn ON if soil moisture is low
    
}

