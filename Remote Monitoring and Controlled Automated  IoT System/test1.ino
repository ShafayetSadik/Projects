#include <Wire.h>  //libraries
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SoftwareSerial.h"
#include <Servo.h>
 Servo myservo;
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define TRIG_PIN 7
#define ECHO_PIN 5
#define ONE_WIRE_BUS 2
#define TEMP_ALERT_PIN 8


float calibration_value = 34.50; //for ph
int phval = 0;//ph
unsigned long int avgval;//ph
int buffer_arr[10], temp;//ph


OneWire oneWire(ONE_WIRE_BUS);//temp
DallasTemperature sensors(&oneWire);//temp


SoftwareSerial mySerial(9, 10);//for gsm
String cmd = "";//gsm

const int motor1 = 6; //for motor
const int motor2 = 3;//motor

bool msg_sent_ph = false; //boolean variable



void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TEMP_ALERT_PIN, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);

  myservo.attach(11); //servo
  sensors.begin();

  mySerial.begin(9600);

  //display
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50, 0);
  display.println("EEE");
  display.setCursor(50, 10);
  display.println("4518");
  display.display();
  delay(1000);

   //gsm initiating
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
 //ph
  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(A0);
    delay(30);
  }
 
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = -5.70 * volt + calibration_value;
 


 //phlogic to gsm
  if (ph_act > 10 && msg_sent_ph == false) {
    mySerial.println("AT+CMGS=\"+8801601313077\"");
    updateSerial();
    mySerial.print("Boss I'm dying.");
    updateSerial();
    mySerial.write(26);

    msg_sent_ph = true;
  }

  if(ph_act <= 5)
    msg_sent_ph = false;

 //distance
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;


 //Check water level value
  if (distance >=12) {
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, HIGH);
  } else if (distance <= 4) {
    digitalWrite(motor2, LOW);
  }
  
  //temparature depended heater mechanism
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0) - 5;

  if (tempC < 25) {
    digitalWrite(TEMP_ALERT_PIN, HIGH);
  } else {
    digitalWrite(TEMP_ALERT_PIN, LOW);
  }

 //OLED display output

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("pH Value:");
  display.setCursor(60, 0);
  display.println(ph_act);
  display.setCursor(0, 10);
  display.println("Water Level:");
  display.setCursor(70, 10);
  display.println(distance);
  display.setCursor(0, 20);
  display.println("Temperature:");
  display.setCursor(80, 20);
  display.println(tempC);
  display.display();

  //for serial monitor
  Serial.print("pH Value: ");
  Serial.println(ph_act);
  Serial.print("Distance: ");
  Serial.println(distance);



  updateSerial();

  delay(1000);

 //feeder mechanism
  myservo.write(45);  // move servo to 45 degrees
  delay(43200000);  // wait for 2 minutes

  
  myservo.write(0);  // move servo to 0 degrees (anticlockwise)
  delay(1000);  // wait for 1 second

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
      digitalWrite(motor1, HIGH);  // Set digital pin 6 to 5V
    }
  }
  delay(500);

  while (Serial.available()) {
    mySerial.write(Serial.read());
  }

  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
















