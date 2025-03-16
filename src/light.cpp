#include "light.h"
#include "esp32-hal-adc.h"

void read_light(Data* data)
{
    int sensor_value = analogRead(LIGHT_PIN);

    float voltage = sensor_value * (5.0 / 1024.0);

    float percentage = 0.0;

    if (voltage <= 0.4) {
        percentage = 100.0; // Brightest
    } else if (voltage >= 5.0) {
        percentage = 0.0; // Darkest
    } else {
        // Map voltage range (0.4V - 5V) to percentage (100% - 0%)
        percentage = ((5.0 - voltage) / (5.0 - 0.4)) * 100.0;
    }

    data->light = percentage;
}

