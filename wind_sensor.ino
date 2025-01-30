#include <Arduino.h>

#define NUM_SAMPLES 10  // Number of readings to average

void setup() {
  Serial.begin(9600);
}

void loop() {
  float sensorValue = 0;

  // Take multiple sensor readings and average them
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sensorValue += analogRead(A0);
    delay(10);  // Short delay to stabilize readings
  }
  sensorValue /= NUM_SAMPLES;  // Compute the average

  // Serial.print("Averaged Analog Value = ");
  // Serial.println(sensorValue);

  // Convert raw ADC value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);
  // Serial.print("Voltage = ");
  // Serial.print(voltage, 2);
  // Serial.println(" V");

  // Convert voltage to wind speed (m/s)
  float wind_speed = mapfloat(voltage, 0.4, 2.0, 0, 32.4);
  wind_speed = max(0.0, wind_speed);  // Clamp negative values to zero

  // Convert m/s to km/h
  float speed_kmh = wind_speed * 3.6;

  Serial.print("Wind Speed = ");
  Serial.print(wind_speed, 2);
  Serial.println(" m/s");

  Serial.print("Wind Speed = ");
  Serial.print(speed_kmh, 2);
  Serial.println(" km/h");

  Serial.println(" ");
  delay(300);
}

// Function to map float values
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return max(0.0, (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
