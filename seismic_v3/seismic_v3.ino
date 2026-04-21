#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int potpin = 9;       // speed output pin Arduino
int speeds = 170;     // initial speed
int increment = 1;    // speed increment
const int led = 7;

// Create a LiquidCrystal_I2C object with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  pinMode(potpin, OUTPUT); 
  pinMode(led, OUTPUT);
  analogWrite(potpin, 0);
  
  lcd.begin(); // Initialize the LCD
  lcd.backlight();  // Turn on backlight
  lcd.setCursor(4, 0);
  lcd.print("Seismic");
  lcd.setCursor(3, 1);
  lcd.print("");
  Serial.begin(9600); // Initialize serial communication
  delay(2000); // Boot screen for 2 seconds
  lcd.clear();
}

void loop() {
  analogWrite(potpin, speeds);
  digitalWrite(led, HIGH);
  speeds = speeds + increment;

  delay(1000); // Duration between speeds

  if (speeds >= 201) {
    speeds = 201; 
    increment = 0;
    delay(15000); // Continuous speed for 15 seconds
    speeds = 0; // After 15 seconds, speed is zero
  } 

  lcd.setCursor(0, 0);
  lcd.print("Running....    "); // Pad spaces to clear previous text
  lcd.setCursor(0, 1);
  lcd.print("Speed:         "); // Pad spaces to clear previous text
  lcd.setCursor(7, 1);
  lcd.print(speeds);  
  Serial.println(speeds);
}
