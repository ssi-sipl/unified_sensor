#include <Arduino.h>

#define NUM_SAMPLES 8

void setup() {
  Serial.begin(9600);
}

void loop() {
  float sensorValue = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    sensorValue += analogRead(A0);
    delay(10);
  }
  sensorValue /= NUM_SAMPLES;

  float voltage = sensorValue * (5.0 / 1023.0);

  float wind_speed = mapfloat(voltage, 0.4, 2.0, 0, 32.4);
  wind_speed = max(0.0f, wind_speed);

  float speed_kmh = wind_speed * 3.6;

  // JSON Output (no timestamp)
  Serial.print("{\"wind_speed_kph\": ");
  Serial.print(speed_kmh, 2);
  Serial.println("}");

  delay(300);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return max(0.0f, (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
