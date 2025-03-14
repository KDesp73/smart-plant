import os
from dotenv import load_dotenv
Import("env")

load_dotenv()

print("env.py - Reading .env for MQTT related info")

wifi_ssid   = os.getenv("WIFI_SSID", "")
wifi_pass   = os.getenv("WIFI_PASS", "")
mqtt_server = os.getenv("MQTT_SERVER", "")
mqtt_port   = os.getenv("MQTT_PORT", 0)
mqtt_topic  = os.getenv("MQTT_TOPIC", "")

print(f"Loaded values:\n- WIFI_SSID: {wifi_ssid}\n- WIFI_PASS: {wifi_pass}\n- MQTT_SERVER: {mqtt_server}\n- MQTT_PORT: {mqtt_port}\n- MQTT_TOPIC: {mqtt_topic}")

if env.IsIntegrationDump():
   # stop the current script execution
   Return()

env.Append(CPPDEFINES=[
    ("WIFI_SSID", wifi_ssid),
    ("WIFI_PASS", wifi_pass),
    ("MQTT_SERVER", mqtt_server),
    ("MQTT_PORT", mqtt_port),
    ("MQTT_TOPIC", mqtt_topic)
])
