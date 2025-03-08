#include <Wire.h>                // For I2C communication
#include <LiquidCrystal_I2C.h>   // For LCD with I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 (may vary) for a 16 chars and 2 line display

// Pin definitions
const int currentSensorPin = A0;   // ACS712 current sensor connected to A0
const int voltageSensorPin = A1;   // ZMPT101B voltage sensor connected to A1

// Calibration constants (adjust as per your sensors)
const float calibrationFactorCurrent = 0.185; // For ACS712 5A (use 0.100 for 20A, 0.066 for 30A)
const float voltageReference = 5.0;           // Arduino reference voltage for analogRead (5V)

// Function to read current
float readCurrent() {
  int sensorValue = analogRead(currentSensorPin);
  float voltage = sensorValue * (voltageReference / 1023.0);  // Convert to voltage
  float current = (voltage - 2.5) / calibrationFactorCurrent; // Convert voltage to current
  return current;
}

// Function to read voltage
float readVoltage() {
  int sensorValue = analogRead(voltageSensorPin);
  float voltage = sensorValue * (voltageReference / 1023.0) * (250);  // Adjust scaling factor
  return voltage;
}

void setup() {
  Serial.begin(9600);       // Start serial communication
  lcd.begin(16,2);              // Initialize the LCD
  lcd.backlight();          // Turn on LCD backlight
}

void loop() {
  float current = readCurrent(); // Get current in amps
  float voltage = readVoltage(); // Get voltage in volts

  // Display on Serial Monitor (optional)
  Serial.print("Current: ");
  Serial.print(current, 3);  // Print current with 3 decimal places
  Serial.print(" A, Voltage: ");
  Serial.print(voltage, 2);  // Print voltage with 2 decimal places
  Serial.println(" V");

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current: ");
  lcd.print(current, 3);  // Display current
  lcd.print(" A");

  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);  // Display voltage
  lcd.print(" V");

  delay(1000);  // Update every second
}