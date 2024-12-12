// Declare and initialize variables
int sensorPin = A0; // Define the analog pin used for the sensor
int sensorValue = 0;

float sensorVoltage = 0.0;
float windSpeed = 0.0;

const float voltageConversionConstant = 0.004882814; // 5V / 1024
const int sensorDelay = 1000; // Delay in milliseconds

const float voltageMin = 0.4;  // Minimum sensor voltage (V)
const float windSpeedMin = 0.0; // Minimum wind speed (units)
const float voltageMax = 2.0;  // Maximum sensor voltage (V)
const float windSpeedMax = 32.0; // Maximum wind speed (units)

void setup() {
  Serial.begin(9600); // Initialize the serial communication
}

void loop() {
  // Read sensor value
  sensorValue = analogRead(sensorPin);

  // Convert ADC value to voltage
  sensorVoltage = sensorValue * voltageConversionConstant;

  // Calculate wind speed
  if (sensorVoltage <= voltageMin) {
    windSpeed = windSpeedMin; // No wind detected
  } else {
    windSpeed = (sensorVoltage - voltageMin) * windSpeedMax / (voltageMax - voltageMin);
  }

  // Print sensor readings to serial monitor
  Serial.print("Voltage: ");
  Serial.print(sensorVoltage);
  Serial.print(" V\t");

  Serial.print("Wind speed: ");
  Serial.print(windSpeed);
  Serial.println("m/s");

  // Wait before next measurement
  delay(sensorDelay);
}
