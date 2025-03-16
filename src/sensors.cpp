#include "sensors.h"
#include "Adafruit_Sensor.h"
#include "DHT_U.h"

void read_dht22(DHT_Unified dht, Data* data)
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
        data->temperature = 0;
    } else {
        data->temperature = event.temperature;
    }

    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
        data->humidity = 0;
    } else {
        data->humidity = event.relative_humidity;
    }

}

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

void read_soil(Data* data)
{
    int _moisture,sensor_analog;
    sensor_analog = analogRead(SOIL_PIN);
    _moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
    
    data->moisture = _moisture;
}
