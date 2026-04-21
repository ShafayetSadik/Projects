// ESP32's TX2 is GPIO17, RX2 is GPIO16
int RX2Pin = 16;
int TX2Pin = 17;

// Default baud of NEO-6M is 9600
int GPSBaud = 9600;

void setup() {
  // Start the primary Serial port for debugging
  Serial.begin(9600);

  // Start Serial2 on the ESP32 at the GPS module's baud rate
  Serial2.begin(GPSBaud, SERIAL_8N1, RX2Pin, TX2Pin);
}

void loop() {
  // Display GPS data from Serial2 when available
  while (Serial2.available() > 0) {
    Serial.write(Serial2.read());
  }
}
