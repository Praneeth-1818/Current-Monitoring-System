// === Configuration ===
const int CURRENT_PIN = 34; // GPIO34 (A0)
const int VOLTAGE_PIN = 35; // GPIO35 (A1)

// Shunt and Amplifier parameters
const float SHUNT_CURRENT = 300.0; // A
const float SHUNT_VOLTAGE = 75.0; // mV
const float AMPLIFIER_GAIN = 40.0; // LM358 gain
const float VOLTAGE_REF = 3300.0; // ESP32 ADC reference (mV)
const int BIT_RESOLUTION = 12;
const int ADC_MAX = (1 << BIT_RESOLUTION) - 1;

const int ITERATION = 50;

// Voltage divider for 100.8V using 295k + 10k
const float R1 = 10000.0;
const float R2 = 295000.0;
const float VOLTAGE_DIVIDER_RATIO = (R1 + R2) / R1; // ~30.5

void setup() {
  Serial.begin(115200);
  analogReadResolution(BIT_RESOLUTION);
  delay(500);
  Serial.println("ESP32 Current & Voltage Monitoring with LM358");
}

void loop() {
  float current = getCurrent();
  float voltage = getVoltage();
  float power = voltage * current;

  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V\t");

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.print(" A\t");

  Serial.print("Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  delay(1000);
}

// === Get Current via amplified voltage ===
float getCurrent() {
  float sum = 0;
  for (int i = 0; i < ITERATION; i++) {
    int raw = analogRead(CURRENT_PIN);
    float voltage_mV = raw * (VOLTAGE_REF / ADC_MAX);
    float shuntVoltage_mV = voltage_mV / AMPLIFIER_GAIN;
    float current = (shuntVoltage_mV * SHUNT_CURRENT) / SHUNT_VOLTAGE;
    sum += current;
    delay(5);
  }
  return sum / ITERATION;
}

// === Get Voltage via divider ===
float getVoltage() {
  float sum = 0;
  for (int i = 0; i < ITERATION; i++) {
    int raw = analogRead(VOLTAGE_PIN);
    float voltage_mV = raw * (VOLTAGE_REF / ADC_MAX);
    float actualVoltage = (voltage_mV / 1000.0) * VOLTAGE_DIVIDER_RATIO;
    sum += actualVoltage;
    delay(5);
  }
  return sum / ITERATION;
}