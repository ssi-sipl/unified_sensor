#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define NUM_SAMPLES 8
#define SEALEVELPRESSURE_HPA (1001.25)

Adafruit_BME280 bme;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return max(0.0f, (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void setup() {
  Serial.begin(9600);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Wind Speed Reading
  float sensorValue = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sensorValue += analogRead(A0);
    delay(10);
  }
  sensorValue /= NUM_SAMPLES;

  float voltage = sensorValue * (5.0 / 1023.0);
  float wind_speed = mapfloat(voltage, 0.4, 2.0, 0, 32.4);
  wind_speed = max(0.0f, wind_speed);
  float speed_kph = wind_speed * 3.6;

  // BME280 Readings
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();

  // JSON Output
  Serial.print("{");
  Serial.print("\"wind_speed_kph\": "); Serial.print(speed_kph, 2); Serial.print(", ");
  Serial.print("\"temperature_C\": "); Serial.print(temperature, 2); Serial.print(", ");
  Serial.print("\"pressure_hPa\": "); Serial.print(pressure, 2); Serial.print(", ");
  Serial.print("\"altitude_m\": "); Serial.print(altitude, 2); Serial.print(", ");
  Serial.print("\"humidity_pct\": "); Serial.print(humidity, 2);
  Serial.println("}");

  delay(1000);  // 1-second delay between readings
}
