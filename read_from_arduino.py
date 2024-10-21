import serial
import time

# Replace '/dev/ttyUSB0' with the appropriate port
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)  # Give time for the connection to establish

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
