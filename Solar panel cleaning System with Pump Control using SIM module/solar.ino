#include "SoftwareSerial.h"
SoftwareSerial mySerial(9, 10);
String cmd = "";
const int controlPin = 6;

void setup() {
  pinMode(controlPin, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT");
  updateSerial();
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0");
  updateSerial();
}

void loop() {
  updateSerial();
}

void updateSerial() {

  cmd = "";
  while (mySerial.available()) {
    cmd += (char)mySerial.read();
    if (cmd != "") {
      cmd.trim();
    }
  }
  Serial.print(cmd);
  Serial.println("");
  if (cmd != "") {
    char message = cmd.charAt(cmd.length() - 1);
    Serial.println(message);
    if (message == 'm') {
      digitalWrite(controlPin, HIGH);
    } else if (message == 'n') {
      digitalWrite(controlPin, LOW);
    }
  }
  delay(500);
}
