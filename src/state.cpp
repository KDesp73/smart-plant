#include "state.h"
#include "HardwareSerial.h"
#include <ArduinoJson.h>

void update_state(State* state)
{
    state->waterPump = (state->data.moisture < 30);  // Auto turn ON if soil moisture is low
}
    
String data_serialize(const Data* data)
{
    JsonDocument doc;

    doc["humidity"] = data->humidity;
    doc["temperature"] = data->temperature;
    doc["light"] = data->light;
    doc["moisture"] = data->moisture;

    String json;
    serializeJson(doc, json);
    return json;
}

void data_print(const Data* data)
{
    Serial.printf("Temp: %fC\n", data->temperature);
    Serial.printf("RH: %f%%\n", data->humidity);
    Serial.printf("Light: %f%%\n", data->light);
    Serial.printf("Soil: %f%%\n", data->moisture);
}

