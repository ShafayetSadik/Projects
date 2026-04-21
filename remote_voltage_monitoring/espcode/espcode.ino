#define BLYNK_TEMPLATE_ID "TMPL67KhZXmMI"
#define BLYNK_TEMPLATE_NAME "volsen"
#define BLYNK_AUTH_TOKEN "bJDST8UzXcwlr8pQXWlig_fr6EUD6g9t"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Define your Wi-Fi credentials
char ssid[] = "redshift";         // Wi-Fi SSID
char pass[] = "cgpafour";         // Wi-Fi Password

#define CHARGING_SWITCH_PIN V30
#define CHARGING_MESSAGE_PIN V31
#define COLLECTION_SWITCH_PIN V32
#define COLLECTION_MESSAGE_PIN V33

const int sensorPin = 34;
const float calibrationFactor = 12.0 / 2.35;

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  pinMode(sensorPin, INPUT);
}

BLYNK_WRITE(CHARGING_SWITCH_PIN) {
  // Get the state of the charging switch
  int switchState = param.asInt();
  
  if (switchState == 1) {
    // Switch is ON, display "Battery is charging" message
    Blynk.virtualWrite(CHARGING_MESSAGE_PIN, "Battery is charging");
    Serial.println("Charging Switch ON: Battery is charging");
  } else {
    // Switch is OFF, clear the message
    Blynk.virtualWrite(CHARGING_MESSAGE_PIN, "");
    Serial.println("Charging Switch OFF: Message cleared");
  }
}

BLYNK_WRITE(COLLECTION_SWITCH_PIN) {
  // Get the state of the collection switch
  int switchState = param.asInt();
  
  if (switchState == 1) {
    // Switch is ON, display "Battery is now at collection point" message
    Blynk.virtualWrite(COLLECTION_MESSAGE_PIN, "Battery is now at collection point");
    Serial.println("Collection Switch ON: Battery is now at collection point");
  } else {
    // Switch is OFF, clear the message
    Blynk.virtualWrite(COLLECTION_MESSAGE_PIN, "");
    Serial.println("Collection Switch OFF: Message cleared");
  }
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = (sensorValue / 4095.0) * 3.3;
  
  float actualVoltage = voltage * calibrationFactor;
  
  Blynk.virtualWrite(V0, actualVoltage);
  Serial.print("Actual Voltage: ");
  Serial.println(actualVoltage);
  
  // Always show "Battery Discharging" on V2
  Blynk.virtualWrite(V2, "Battery Discharging");
  
  Blynk.run();
}