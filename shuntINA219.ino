#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  Serial.begin(9600);
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1); // Halt if INA219 is not found
  }
  ina219.setCalibration_32V_2A(); // or any other calibration
}

void loop() {
  float busVoltage = ina219.getBusVoltage_V();
  float shuntVoltage = ina219.getShuntVoltage_mV();
  float current = ina219.getCurrent_mA();
  float loadVoltage = busVoltage + (shuntVoltage / 1000.0);

  Serial.print("Voltage: "); Serial.print(loadVoltage); Serial.println(" V");
  Serial.print("Current: "); Serial.print(current); Serial.println(" mA");
  Serial.println();

  delay(1000); // delay between readings
}
