# Seismic V3

Arduino sketch for a timed PWM output sequence with LCD status display and an indicator LED.

## Hardware Mapping

- PWM output on `D9`
- Indicator LED on `D7`
- `16x2` I2C LCD at address `0x27`

## Runtime Behavior

- Starts at PWM value `170`
- Increases by `1` every second
- Caps at `201`
- Holds that value for `15` seconds
- Sets the output to `0` after the hold period

The sketch also prints the current speed to the serial monitor at `9600` baud and mirrors the value on the LCD.

## Project Files

- `seismic_v3.ino` - Arduino sketch

## Build

Install `LiquidCrystal_I2C`, open `seismic_v3.ino` in the Arduino IDE, select the target board and port, and upload.
