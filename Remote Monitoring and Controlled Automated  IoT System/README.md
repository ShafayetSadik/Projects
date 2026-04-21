# Remote Monitoring and Controlled Automated IoT System

This repository contains an Arduino-based automated aquarium system that monitors water quality and tank conditions, displays live readings on an OLED, sends GSM alerts, and controls actuators such as a water pump, heater output, and feeder servo.

The most complete sketch in this project is `test1.ino`. The other `.ino` files are smaller prototype or subsystem tests used while building the final system.

## Features

- Measures pH using an analog pH sensor on `A0`
- Measures water level using an ultrasonic sensor
- Measures water temperature using a DS18B20-compatible 1-Wire sensor
- Shows live pH, water level, and temperature on a 128x64 OLED display
- Sends SMS alerts through a SIM800L GSM module when pH crosses a threshold
- Accepts GSM input for remote motor control logic
- Controls tank water level using motor/pump outputs
- Turns on a temperature output when water temperature drops below a threshold
- Drives a servo-based feeder

## Main Sketch

Use `test1.ino` as the starting point if you want the full integrated system.

Current behavior in `test1.ino`:

- Sends an SMS alert when calculated pH goes above `10`
- Resets the pH alert flag when pH goes back to `5` or lower
- Starts water-level control when measured distance is `>= 12`
- Stops one motor output when measured distance is `<= 4`
- Enables the temperature alert/heater output when temperature is below `25 C`
- Moves the feeder servo, then waits `43,200,000 ms` before the next cycle

Note: the feeder comment says "2 minutes", but the code delay is 12 hours.

## Hardware / Pin Map

The integrated sketch uses the following pins:

- `A0`: pH sensor analog output
- `D2`: DS18B20 data line
- `D3`: motor output 2
- `D5`: ultrasonic echo
- `D6`: motor output 1
- `D7`: ultrasonic trigger
- `D8`: temperature alert / heater control output
- `D9`: SIM800L RX/TX via `SoftwareSerial`
- `D10`: SIM800L RX/TX via `SoftwareSerial`
- `D11`: feeder servo

OLED configuration in the code:

- I2C OLED at address `0x3C`

## Libraries

Install these Arduino libraries before compiling:

- `Wire`
- `Adafruit_SSD1306`
- `OneWire`
- `DallasTemperature`
- `SoftwareSerial`
- `Servo`

Depending on your Arduino IDE setup, `Wire`, `SoftwareSerial`, and `Servo` may already be available.

## File Overview

- `test1.ino`: integrated aquarium automation sketch
- `sen_gsm.ino`: sensor monitoring plus GSM prototype
- `ph-sonar-temp.ino`: pH, water level, temperature, and OLED prototype
- `sending_receiving_final.ino`: GSM send/receive control prototype
- `gsmMotorfinal.ino`: GSM motor control prototype
- `Automated Aquarium_Project Report_200021221,200021227,200021236,200021240,200021248.pdf`: project report

## Setup

1. Open the desired `.ino` file in Arduino IDE.
2. Install the required libraries.
3. Connect the sensors and actuators according to the pin map above.
4. Update the hardcoded GSM phone number in the sketch before uploading.
5. Calibrate the pH sensor and adjust `calibration_value` for your probe.
6. Review threshold values for pH, water level, and temperature.
7. Upload the sketch to an Arduino-compatible board.

## Important Notes

- The GSM sketches contain hardcoded phone numbers and SMS text. Replace them before deployment.
- pH conversion uses a fixed `calibration_value`; expect to recalibrate for different probes and water conditions.
- `SoftwareSerial` and the pin choices suggest this project is intended for an Uno-class AVR board.
- The final sketch uses long `delay()` calls, which block the controller while waiting for the next feeder cycle.

## Future Improvements

- Replace blocking `delay()` calls with `millis()`-based scheduling
- Store thresholds and phone numbers in EEPROM or a config header
- Add separate manual and automatic pump/heater modes
- Add filtering and fault handling for unstable sensor readings
- Log readings to cloud or SD storage

## License

No license file is currently included in this repository.
