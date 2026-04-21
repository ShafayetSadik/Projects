#define BLYNK_TEMPLATE_ID "TMPL67KhZXmMI"
#define BLYNK_TEMPLATE_NAME "volsen"
#define BLYNK_AUTH_TOKEN1 "bJDST8UzXcwlr8pQXWlig_fr6EUD6g9t"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Define your Wi-Fi credentials
char ssid[] = "RRRRR";         // Wi-Fi SSID
char pass[] = "cockybitch7";   // Wi-Fi Password

#define SWITCH_PIN V30
#define MESSAGE_PIN V31

const int sensorPin = 34;
const float calibrationFactor1 = 12.0 / 3;
const float calibrationFactor2 = 12.0 / 2.4;

bool switchState = false;
unsigned long switchToggleTime = 0;
bool secondMessageShown = false;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN1, ssid, pass);
  pinMode(sensorPin, INPUT);
  
  // Show initial message
  Blynk.virtualWrite(MESSAGE_PIN, "Battery 2: Charging");
}

BLYNK_WRITE(SWITCH_PIN) {
  switchState = param.asInt();
  switchToggleTime = millis();
  secondMessageShown = false;
  
  if (switchState) {
    // Switch is turned ON
    Blynk.virtualWrite(MESSAGE_PIN, "Battery 2: Charging");
    Serial.println("Switch ON: Battery is Charging now");
  } else {
    // Switch is turned OFF, message will be updated after 5 seconds
    Serial.println("Switch OFF: Message will update in 5 seconds");
  }
}

void loop() {
  Blynk.run();
  
  int sensorValue = analogRead(sensorPin);
  float voltage = (sensorValue / 4095.0) * 3.3;
  float actualVoltage1 = voltage * calibrationFactor1;
  float actualVoltage2 = voltage * calibrationFactor2;
  
  Blynk.virtualWrite(V0, actualVoltage1);
  Serial.print("Actual Voltage 1: ");
  Serial.println(actualVoltage1);
  
  Blynk.virtualWrite(V40, actualVoltage2);
  Serial.print("Actual Voltage 2: ");
  Serial.println(actualVoltage2);
  
  // Always show "Battery Discharging" on V2
  Blynk.virtualWrite(V2, "Battery 1: Discharging");
  
  // Check if it's time to show the updated message
  if (!switchState && !secondMessageShown && millis() - switchToggleTime > 5000) {
    Blynk.virtualWrite(MESSAGE_PIN, "Battery 2: Charged.At collection point");
    Serial.println("Updated message: Battery is charged. Battery is at collection point");
    secondMessageShown = true;
  }
}