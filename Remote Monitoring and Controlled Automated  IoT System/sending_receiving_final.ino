#include "SoftwareSerial.h"

SoftwareSerial mySerial(9, 10);  // SoftwareSerial instance for SIM800L module
String cmd = "";
const int controlPin = 6;  // Digital pin 6 for control

void setup() {
  pinMode(controlPin, OUTPUT);
  mySerial.begin(9600);  // Initialize SoftwareSerial
  Serial.begin(9600);   // Initialize Serial for debugging
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT");  // Sends an ATTENTION command, reply should be OK
  updateSerial();
  mySerial.println("AT+CMGF=1");  // Configuration for sending SMS
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0");  // Configuration for receiving SMS
  updateSerial();
  
  // Sending SMS
  mySerial.println("AT+CMGS=\"+8801601313077\"");  // Replace with the destination phone number
  updateSerial();
  mySerial.print("safwanchodu");  // Replace with your desired message
  updateSerial();
  mySerial.write(26);  // Send Ctrl+Z to indicate the end of the message
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
      digitalWrite(controlPin, HIGH);  // Set digital pin 6 to 5V
    } else if (message == 'n') {
      digitalWrite(controlPin, LOW);  // Set digital pin 6 to 0V
    }
  }
  delay(500);
   while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
