# Remote Voltage Monitoring

ESP32-based voltage-monitoring project with multiple sketches covering battery sensing, Blynk reporting, status messaging, GPS passthrough, and switch-input testing.

## Repository Structure

- `final2/final2.ino` - dual calibrated voltage reporting with Blynk status messaging
- `final1/final1.ino` - single-voltage Blynk build with charging and collection messages
- `espcode/espcode.ino` - Blynk variant with separate charging and collection switches
- `claude2/claude2.ino` - voltage reporting with GPS sentence forwarding to Blynk
- `onlygps/onlygps.ino` - GPS serial passthrough test
- `switch/switch.ino` - button-input test on `GPIO25`
- `sending_receiving_final/sending_receiving_final.ino` - standalone voltage-divider measurement sketch
- `2021253482.pdf`, `pdf.pdf`, `FOG770BK02P2LSK.pdf`, `SE100Manual.pdf` - reference documents

## Technical Notes

- The ESP32 sketches read voltage on `GPIO34`.
- The Blynk builds use `WiFi.h` and `BlynkSimpleEsp32.h`.
- The GPS sketches use `Serial2` on `GPIO16` and `GPIO17`.
- Calibration is handled in code with fixed multipliers after the ADC reading.

## Build

1. Open the target sketch in the Arduino IDE.
2. Install ESP32 board support and the Blynk library.
3. Replace the hardcoded Wi-Fi and Blynk credentials before uploading.
4. Select the correct board and serial port.
5. Upload and verify the expected virtual-pin mapping in Blynk.
