#include <Arduino.h>

#define NUM_SAMPLES 15 //the higher this number , the more accurate the reading 
#define SIGNAL A0 //yellow wire 

void setup() {
  Serial.begin(9600);
}

void loop() {
  float sensorValue = 0; 

  for (int i = 0; i < NUM_SAMPLES; i++) {
    sensorValue += analogRead(SIGNAL);
    delay(5);
  }
  sensorValue /= NUM_SAMPLES;

  float voltage = sensorValue * (5.0 / 1023.0);

  float wind_speed = mapfloat(voltage, 0.4, 2.0, 0, 32.8); 
  wind_speed = max(0.0f, wind_speed);

  float speed_ms = wind_speed;

  // JSON Output to be print to Raspberry Pi 
  Serial.print("{\"wind_speed_mps\": ");
  Serial.print(speed_ms, 3);
  Serial.println("}");

  delay(200);
}

//main function of wind speed calculation; dont touch! 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return max(0.0f, (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
