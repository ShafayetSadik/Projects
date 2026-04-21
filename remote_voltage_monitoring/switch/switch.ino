#define BLYNK_TEMPLATE_ID "TMPL67KhZXmMI"
#define BLYNK_TEMPLATE_NAME "volsen"
#define BLYNK_AUTH_TOKEN "bJDST8UzXcwlr8pQXWlig_fr6EUD6g9t"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Define your Wi-Fi credentials
char ssid[] = "redshift";         // Wi-Fi SSID
char pass[] = "cgpafour";         // Wi-Fi Password

const int BUTTON_PIN = 25; // ESP32 pin connected to button's pin

int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button

void setup() {
  Serial.begin(115200);                    // initialize serial
  pinMode(BUTTON_PIN, INPUT_PULLUP);     // set ESP32 pin to input pull-up mode

  currentButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  lastButtonState    = currentButtonState;      // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");
  }
}