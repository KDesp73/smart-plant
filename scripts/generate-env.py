import os
from dotenv import load_dotenv

def strip_quotes(value):
    if value.startswith('"') and value.endswith('"'):
        return value[1:-1]
    return value

load_dotenv()

print("generate-env.py")

wifi_ssid            = strip_quotes(os.getenv("WIFI_SSID", ""))
wifi_pass            = strip_quotes(os.getenv("WIFI_PASS", ""))
mqtt_server          = strip_quotes(os.getenv("MQTT_SERVER", ""))
mqtt_port            = strip_quotes(os.getenv("MQTT_PORT", 0))
mqtt_topic           = strip_quotes(os.getenv("MQTT_TOPIC", ""))
mqtt_username        = strip_quotes(os.getenv("MQTT_USERNAME", ""))
mqtt_password        = strip_quotes(os.getenv("MQTT_PASSWORD", ""))
pushbullet_api_key   = strip_quotes(os.getenv("PUSHBULLET_API_KEY", ""))
pushbullet_device_id = strip_quotes(os.getenv("PUSHBULLET_DEVICE_ID", ""))

print("Loaded values:")
print(f"- WIFI_SSID: {wifi_ssid}")
print(f"- WIFI_PASS: {'*' * len(wifi_pass)}")
print(f"- MQTT_SERVER: {mqtt_server}")
print(f"- MQTT_PORT: {mqtt_port}")
print(f"- MQTT_TOPIC: {mqtt_topic}")
print(f"- MQTT_USERNAME: {mqtt_username}")
print(f"- MQTT_PASSWORD: {mqtt_password}")
print(f"- PUSHBULLET_API_KEY: {pushbullet_api_key}")
print(f"- PUSHBULLET_DEVICE_ID: {pushbullet_device_id}")

# Generate the env.h file
env_file_path = "include/env.h"

with open(env_file_path, "w") as env_file:
    env_file.write("#pragma once\n\n")

    env_file.write(f'#define WIFI_SSID "{wifi_ssid}"\n')
    env_file.write(f'#define WIFI_PASS "{wifi_pass}"\n')

    env_file.write(f'#define MQTT_SERVER "{mqtt_server}"\n')
    env_file.write(f'#define MQTT_PORT {mqtt_port}\n')
    env_file.write(f'#define MQTT_TOPIC "{mqtt_topic}"\n')
    env_file.write(f'#define MQTT_USERNAME "{mqtt_username}"\n')
    env_file.write(f'#define MQTT_PASSWORD "{mqtt_password}"\n')

    env_file.write(f'#define PUSHBULLET_API_KEY "{pushbullet_api_key}"\n')
    env_file.write(f'#define PUSHBULLET_DEVICE_ID "{pushbullet_device_id}"\n')

print(f"Generated {env_file_path} successfully.")
