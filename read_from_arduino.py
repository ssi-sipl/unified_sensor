import serial
import time
import paho.mqtt.client as mqtt
from config import *

# Replace '/dev/ttyUSB0' with the appropriate port
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)  # Give time for the connection to establish

try:
    client = mqtt.Client()
    if USE_AUTH == 1:
        client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)
    client.connect(MQTT_BROKER, MQTT_PORT)
    client.loop_start()
    mqtt_enabled = True
    print(f"Successfully connected to MQTT broker at {MQTT_BROKER}:{MQTT_PORT}")
    time.sleep(1)
except ConnectionRefusedError:
    print(f"Error: Could not connect to MQTT broker at {MQTT_BROKER}:{MQTT_PORT}. Connection refused.")
    exit(1)
except Exception as e:
    print(f"Error connecting to MQTT broker: {str(e)}")
    exit(1)

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            
            client.publish(MQTT_TOPIC, line)
except KeyboardInterrupt:
    print("\nClosing connections...")
    
    try:
        client.loop_stop()
        client.disconnect()
        print("MQTT connection closed successfully")
    except Exception as e:
        print(f"Error while disconnecting from MQTT broker: {str(e)}")
    try:
        ser.close()
        print("Serial connection closed successfully")
    except Exception as e:
        print(f"Error while closing serial connection: {str(e)}")
    print("Program terminated")

