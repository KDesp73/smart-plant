#include "state.h"

void update_state(State* state)
{
    state->waterPump = (state->data.moisture < 30);  // Auto turn ON if soil moisture is low
    
}

