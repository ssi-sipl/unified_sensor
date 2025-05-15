import serial
import time
import json
from datetime import datetime

# Update the port name accordingly
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

while True:
    try:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line.startswith("{") and line.endswith("}"):
                data = json.loads(line)
                data['timestamp'] = datetime.utcnow().isoformat() + "Z"
                print(json.dumps(data))
            else:
                print("Non-JSON line received:", line)
    except json.JSONDecodeError:
        print("Failed to decode JSON:", line)
    except Exception as e:
        print("Error:", e)
