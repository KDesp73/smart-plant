import os
from dotenv import load_dotenv

class ConfigGenerator:
    def __init__(self, env_file=".env"):
        # Load environment variables from the .env file
        load_dotenv(env_file)
        self.config = {}

    def strip_quotes(self, value):
        """Strips quotes from the value if they exist."""
        if value.startswith('"') and value.endswith('"'):
            return value[1:-1]
        return value

    def add_variable(self, key, default_value):
        """Adds a variable to the config dictionary with optional default."""
        value = self.strip_quotes(os.getenv(key, default_value))
        self.config[key] = value

    def generate_header(self, output_file="include/env.h"):
        """Generates the env.h file with the current config."""
        with open(output_file, "w") as env_file:
            env_file.write("#pragma once\n\n")

            for key, value in self.config.items():
                if isinstance(value, int):  # If it's an integer, do not quote it
                    env_file.write(f'#define {key} {value}\n')
                else:
                    env_file.write(f'#define {key} "{value}"\n')

        print(f"Generated {output_file} successfully.")

# Example usage:

# Create a config generator instance
gen = ConfigGenerator()

# Add variables, with optional default values
gen.add_variable("WIFI_SSID", "")
gen.add_variable("WIFI_PASS", "")
gen.add_variable("MQTT_SERVER", "")
gen.add_variable("MQTT_PORT", 0)
gen.add_variable("MQTT_TOPIC", "")
gen.add_variable("MQTT_USERNAME", "")
gen.add_variable("MQTT_PASSWORD", "")
gen.add_variable("PUSHBULLET_API_KEY", "")
gen.add_variable("PUSHBULLET_DEVICE_ID", "")

# Print the loaded values (for debugging purposes)
print("Loaded values:")
for key, value in gen.config.items():
    if key == "WIFI_PASS":
        # Mask the password for privacy
        print(f"- {key}: {'*' * len(value)}")
    else:
        print(f"- {key}: {value}")

# Generate the env.h file
gen.generate_header()
