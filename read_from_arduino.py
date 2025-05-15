import serial
import time
import json
from datetime import datetime

# Update the port name as per your system
ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

while True:
    try:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            timestamp = datetime.now().isoformat()  # Local timestamp

            if line.startswith("{") and line.endswith("}"):
                data = json.loads(line)
                data['timestamp'] = timestamp
                print(json.dumps(data))
            else:
                print(f"[{timestamp}] Non-JSON line received:", line)
    except json.JSONDecodeError:
        print(f"[{datetime.now().isoformat()}] Failed to decode JSON:", line)
    except Exception as e:
        print(f"[{datetime.now().isoformat()}] Error:", e)
