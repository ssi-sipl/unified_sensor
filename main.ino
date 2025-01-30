
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define NUM_SAMPLES 10  // Number of readings to average for wind sensor
#define SEALEVELPRESSURE_HPA (1023.25)  // Adjust to your local pressure

Adafruit_BME280 bme;  // BME280 sensor object

void setup() {
  Serial.begin(9600);

  // Initialize BME280 sensor
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read and process wind speed sensor data
  float sensorValue = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sensorValue += analogRead(A0);
    delay(10);  // Short delay to stabilize readings
  }
  sensorValue /= NUM_SAMPLES;

  // Convert raw ADC value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Convert voltage to wind speed (m/s)
  float wind_speed = mapfloat(voltage, 0.4, 2.0, 0, 32.4);
  wind_speed = max(0.0, wind_speed);  // Clamp negative values to zero

  // Convert wind speed to km/h
  float speed_kmh = wind_speed * 3.6;

  // Read BME280 sensor data
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;  // Convert Pa to hPa
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();

  // Print wind speed data
  Serial.print("Wind Speed = ");
  Serial.print(wind_speed, 2);
  Serial.println(" m/s");

  Serial.print("Wind Speed = ");
  Serial.print(speed_kmh, 2);
  Serial.println(" km/h");

  Serial.println(" ");

  // Print BME280 sensor data
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println();

  delay(1000);  // Delay before next readings
}

// Function to map float values
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return max(0.0, (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
