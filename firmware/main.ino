#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int VOLTAGE_PIN = A0;
const int TEMP_PIN = A1;
const float R1 = 30000.0;
const float R2 = 7500.0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("By: Shreyas K");    
  lcd.setCursor(0, 1);
  lcd.print("BLDEA College");    
  delay(3000);                   
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EV BATTERY MON");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // --- Voltage Measurement ---
  int rawVoltage = analogRead(VOLTAGE_PIN);
  float vOut = (rawVoltage * 5.0) / 1023.0;
  float batteryVoltage = vOut * ((R1 + R2) / R2);

  // --- Temperature Measurement (TMP36 Sensor) ---
  int rawTemp = analogRead(TEMP_PIN);
  float tempVolts = (rawTemp * 5.0) / 1023.0;
  
  // TMP36 conversion: Subtract 0.5V offset, then multiply by 100
  float tempC = (tempVolts - 0.5) * 100.0;

 
  lcd.setCursor(0, 0);
  lcd.print("Volt: ");
  lcd.print(batteryVoltage, 1);
  lcd.print("V   ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);
  lcd.print((char)223); 
  lcd.print("C  ");
  delay(1000);
}
