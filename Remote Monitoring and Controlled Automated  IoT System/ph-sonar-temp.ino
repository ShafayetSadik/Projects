#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define TRIG_PIN 7
#define ECHO_PIN 6
#define ONE_WIRE_BUS 2
#define TEMP_ALERT_PIN 8

float calibration_value = 30.77;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;

OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);

void setup() 
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TEMP_ALERT_PIN, OUTPUT);
  
  sensors.begin();
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,0);
  display.println("EEE");
  display.setCursor(50,10);
  display.println("4518");
  display.display();
  delay(2000);
}

void loop() {
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 
 long duration, distance;
 digitalWrite(TRIG_PIN, LOW);  
 delayMicroseconds(2); 
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10); 
 digitalWrite(TRIG_PIN, LOW);
 duration = pulseIn(ECHO_PIN, HIGH);
 distance = (duration/2) / 29.1;

 sensors.requestTemperatures(); 
 float tempC = sensors.getTempCByIndex(0) - 5;
 
 if(tempC < 15) {
   digitalWrite(TEMP_ALERT_PIN, HIGH);
 } else {
   digitalWrite(TEMP_ALERT_PIN, LOW);
 }
 
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

 delay(1000);
}