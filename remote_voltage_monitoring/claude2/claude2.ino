#define BLYNK_TEMPLATE_ID "TMPL67KhZXmMI"
#define BLYNK_TEMPLATE_NAME "volsen"
#define BLYNK_AUTH_TOKEN "bJDST8UzXcwlr8pQXWlig_fr6EUD6g9t"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Define your Wi-Fi credentials
char ssid[] = "redshift";         // Wi-Fi SSID
char pass[] = "cgpafour";         // Wi-Fi Password

const int sensorPin = 34;
const float calibrationFactor = 12.0 / 2.35;

int RX2Pin = 16;
int TX2Pin = 17;
int GPSBaud = 9600;

String gpsData = "";

void setup() {
  Serial.begin(115200);  // Increased baud rate for debugging
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  pinMode(sensorPin, INPUT);
  
  Serial2.begin(GPSBaud, SERIAL_8N1, RX2Pin, TX2Pin);
  Serial.println("GPS Serial initialized");
}

void loop() {
  // Voltage reading
  int sensorValue = analogRead(sensorPin);
  float voltage = (sensorValue / 4095.0) * 3.3;
  float actualVoltage = voltage * calibrationFactor;
  
  Blynk.virtualWrite(V0, actualVoltage);
  Serial.print("Actual Voltage: ");
  Serial.println(actualVoltage);

  // GPS reading
  gpsData = "";
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    gpsData += c;
    if (c == '\n') {
      // We have a complete NMEA sentence
      Serial.print("GPS Data: ");
      Serial.print(gpsData);
      Blynk.virtualWrite(V1, gpsData);
      gpsData = "";  // Clear the string for the next sentence
    }
  }

  Blynk.run();
  delay(1000);  // Small delay to prevent overwhelming Blynk server
}