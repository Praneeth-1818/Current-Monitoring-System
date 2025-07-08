#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ACS_PIN A0  // ACS712 sensor output connected to Arduino A0
#define VREF 5.0    // Reference voltage (5V for Arduino Uno)
#define SENSITIVITY 0.066 // 66mV/A for ACS712-30A

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set LCD I2C address

void setup() {
    Serial.begin(9600);   // Start serial communication
    lcd.begin(16, 2);     // Initialize the LCD
    lcd.backlight();      // Turn on LCD backlight
    lcd.setCursor(0, 0);
    lcd.print("Current Sensor");
    delay(2000);
}

void loop() {
    int rawValue = analogRead(ACS_PIN);  // Read sensor value
    float voltage = (rawValue / 1023.0) * VREF;  // Convert to voltage
    float current = (voltage - 2.5) / SENSITIVITY;  // Convert to current (ACS712 is centered at 2.5V)

    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current:");
    lcd.setCursor(0, 1);
    lcd.print(current);
    lcd.print(" A");

    delay(1000);  // Refresh every 1 second
}



