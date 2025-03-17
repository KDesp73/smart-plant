#include "state.h"
#include "HardwareSerial.h"
#include <ArduinoJson.h>

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
    Serial.println("\n=============================\n");
    Serial.printf("Temp: %fC\n", data->temperature);
    Serial.printf("RH: %f%%\n", data->humidity);
    Serial.printf("Light: %f%%\n", data->light);
    Serial.printf("Soil: %f%%\n", data->moisture);
}

void needs_print(const PlantNeeds* needs)
{
    Serial.println("Plant Needs");
    Serial.printf("Watering interval: %u seconds\n", needs->waterInterval);
    Serial.printf("Light range: %.2f - %.2f lux\n", needs->light_min, needs->light_max);
    Serial.printf("Moisture range: %.2f%% - %.2f%%\n", needs->moisture_min, needs->moisture_max);
    Serial.printf("Temperature range: %.2f - %.2f °C\n", needs->temperature_min, needs->temperature_max);
    Serial.printf("Humidity range: %.2f%% - %.2f%%\n", needs->humidity_min, needs->humidity_max);
}
