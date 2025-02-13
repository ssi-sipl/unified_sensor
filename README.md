### 1. Install dependencies

```bash
pip install paho-mqtt
```

```bash
sudo apt install mosquitto
```

### 2. Run the script

```bash
python read_from_arduino.py
```

### 3. Run the MQTT subscriber

```bash
python mqtt_subscriber.py
```

### 4. Change the config.py file to your own values

```python
MQTT_BROKER = "your-mqtt-broker-address"  # Change this to your MQTT broker address
MQTT_PORT = 1883
MQTT_TOPIC = "topic_name"
USE_AUTH = 0 # NO:0 and YES:1
MQTT_USERNAME = "your_username"  # Add your MQTT username here
MQTT_PASSWORD = "your_password"  # Add your MQTT password here
```
