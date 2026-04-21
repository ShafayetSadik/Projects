#include "SoftwareSerial.h"
SoftwareSerial mySerial(9, 10);
String cmd = "";
const int controlPin1 = 6;  // Digital pin 6 for control

void setup() {
  pinMode(controlPin1, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT");  // Sends an ATTENTION command, reply should be OK
  updateSerial();
  mySerial.println("AT+CMGF=1");  // Configuration for sending SMS
  updateSerial();

  mySerial.println("AT+CNMI=1,2,0,0,0");  // Configuration for receiving SMS
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
      cmd.trim();  // Remove added LF in transmit
    }
  }
  Serial.print(cmd);
  Serial.println("");
  if (cmd != "") {
    char message = cmd.charAt(cmd.length() - 1);
    Serial.println(message);
    if (message == 'm') {
      digitalWrite(controlPin1, HIGH);  // Set digital pin 6 to 5V
    } else if (message == 'n') {
      digitalWrite(controlPin1, LOW);  // Set digital pin 6 to 0V
    }
  }
  delay(500);

}
