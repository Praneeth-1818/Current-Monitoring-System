const int currentPin = 34; // Analog pin for ACS712 output
const float sensitivity = 0.185; // For 5A module, 0.100 for 20A, 0.066 for 30A
const float adcResolution = 4095.0;
const float refVoltage = 3.3; // ESP32 ADC reference
const float zeroCurrentVoltage = 3.3 / 2; // 2.5V typical for ACS712 at 0A

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // ESP32 ADC is 12-bit
}

void loop() {
  int rawValue = analogRead(currentPin);
  float voltage = (rawValue / adcResolution) * refVoltage;
  float current = (voltage - zeroCurrentVoltage) / sensitivity;

  Serial.print("Raw ADC: "); Serial.print(rawValue);
  Serial.print(" | Voltage: "); Serial.print(voltage, 3);
  Serial.print(" V | Current: "); Serial.print(current, 3);
  Serial.println(" A");

  delay(500);
}