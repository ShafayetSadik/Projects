# Remote Monitoring and Controlled Automated IoT System

Arduino-based aquarium automation project that combines sensing, local display, GSM messaging, and actuator control in a single monitoring setup.

## Integrated Functions

- pH sensing on `A0`
- Ultrasonic water-level sensing on `D7` and `D5`
- Temperature sensing on `D2`
- OLED status display at I2C address `0x3C`
- GSM communication over `SoftwareSerial` on `D9` and `D10`
- Motor outputs on `D6` and `D3`
- Temperature-control output on `D8`
- Feeder servo on `D11`

## Project Files

- `test1.ino` - integrated sketch with pH, water level, temperature, GSM, OLED, motor, and feeder logic
- `sen_gsm.ino` - sensor display and GSM control variant
- `ph-sonar-temp.ino` - sensor and OLED prototype
- `sending_receiving_final.ino` - GSM send/receive control sketch
- `gsmMotorfinal.ino` - GSM motor-control sketch
- `Automated Aquarium_Project Report_200021221,200021227,200021236,200021240,200021248.pdf` - final report

## Build

Install the required Arduino libraries:

- `Adafruit_SSD1306`
- `OneWire`
- `DallasTemperature`
- `SoftwareSerial`
- `Servo`

Then open the target `.ino` file in the Arduino IDE, select the correct board and serial port, review the hardcoded phone number and sensor thresholds, and upload.

## Notes

- `test1.ino` sends a pH alert SMS when the calculated pH rises above `10`.
- The feeder delay in `test1.ino` is `43200000` ms.
- The GSM-enabled sketches store the phone number in source and should be updated before deployment.
