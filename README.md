# Arduino Weather Station with Wind Speed and BME280 Sensor

This project reads and outputs real-time weather data using:

- **Analog Wind Speed Sensor** (based on voltage readings)
- **BME280 Environmental Sensor** (temperature, pressure, humidity, altitude)

The data is output via serial in **JSON format**, making it ideal for integration with Python scripts, databases, or IoT dashboards.

## 📦 Hardware Required

- Arduino UNO / Nano / Compatible Board  
- BME280 Sensor (I2C - typically 0x76 address)  
- Analog Wind Speed Sensor (connected to A0)  
- Jumper Wires  
- USB Cable  

## 🧰 Libraries Used

Install the following libraries via Arduino Library Manager:

- `Adafruit BME280`
- `Adafruit Unified Sensor`


## 🔌 Circuit Diagram

| Arduino Pin | Connected To         |
|-------------|----------------------|
| A0          | Wind Speed Sensor OUT |
| VCC         | Both sensors VCC (3.3V/5V as required) |
| GND         | Common Ground        |
| SDA         | BME280 SDA           |
| SCL         | BME280 SCL           |
![Circuit Diagram](https://raw.githubusercontent.com/ssi-sipl/unified_sensor/main/circuit_image.png)

## 🧠 How It Works

1. The wind speed sensor outputs analog voltage corresponding to airflow. This voltage is mapped to m/s and then converted to km/h.
2. The BME280 sensor provides temperature, pressure, humidity, and estimated altitude.
3. All values are averaged (for wind), read, and printed to the Serial monitor as a JSON string every second.
4.At the end , connect the Arduino Nano with the Raspberry Pi 3B+ with the USB type A to Micro USB. 


On running ```read_from_arduino.py```, we get the data as below. 
## 🖨️ Sample Output

```json
{
  "wind_speed_kph": 12.35,
  "temperature_C": 28.40,
  "pressure_hPa": 1011.98,
  "altitude_m": 31.82,
  "humidity": 60.34
}
```
