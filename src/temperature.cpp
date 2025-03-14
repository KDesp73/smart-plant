#include "temperature.h"
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
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));

        data->temperature = event.temperature;
    }

    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
        data->humidity = 0;
    } else {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));

        data->humidity = event.relative_humidity;
    }

}

