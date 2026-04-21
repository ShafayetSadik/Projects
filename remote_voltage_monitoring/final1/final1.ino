#define BLYNK_TEMPLATE_ID "TMPL67KhZXmMI"
#define BLYNK_TEMPLATE_NAME "volsen"
#define BLYNK_AUTH_TOKEN1 "bJDST8UzXcwlr8pQXWlig_fr6EUD6g9t"




#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Define your Wi-Fi credentials
char ssid[] = "RRRRR";         // Wi-Fi SSID
char pass[] = "cockybitch7";         // Wi-Fi Password

#define SWITCH_PIN V30
#define CHARGING_MESSAGE_PIN V31
#define COLLECTION_MESSAGE_PIN V32

const int sensorPin = 34;
const float calibrationFactor = 12.0 / 2.35;

bool switchState = false;
unsigned long switchToggleTime = 0;
bool secondMessageShown = false;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN1, ssid, pass);
  
  
  
  pinMode(sensorPin, INPUT);
}

BLYNK_WRITE(SWITCH_PIN) {
  switchState = param.asInt();
  switchToggleTime = millis();
  secondMessageShown = false;
  
  if (switchState) {
    // Switch is turned ON
    Blynk.virtualWrite(CHARGING_MESSAGE_PIN, "Battery is Charging now");
    Blynk.virtualWrite(COLLECTION_MESSAGE_PIN, "");
    Serial.println("Switch ON: Battery is Charging now");
  } else {
    // Switch is turned OFF
    Blynk.virtualWrite(CHARGING_MESSAGE_PIN, "Your Battery is fully charged!");
    Blynk.virtualWrite(COLLECTION_MESSAGE_PIN, "");
    Serial.println("Switch OFF: Your Battery is fully charged!");
  }
}

void loop() {
  Blynk.run();

  int sensorValue = analogRead(sensorPin);
  float voltage = (sensorValue / 4095.0) * 3.3;
  float actualVoltage = voltage * calibrationFactor;
  
  Blynk.virtualWrite(V0, actualVoltage);
  Serial.print("Actual Voltage: ");
  Serial.println(actualVoltage);
  
  // Always show "Battery Discharging" on V2
  Blynk.virtualWrite(V2, "Battery Discharging");
  
  // Check if it's time to show the collection point message
  if (!switchState && !secondMessageShown && millis() - switchToggleTime > 5000) {
    Blynk.virtualWrite(COLLECTION_MESSAGE_PIN, "Battery is now at collection point!");
    Serial.println("Battery is now at collection point!");
    secondMessageShown = true;
  }
}