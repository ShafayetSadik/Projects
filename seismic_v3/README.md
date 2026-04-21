# Seismic V3

Arduino sketch for driving a simple seismic-motion style output using PWM, with status shown on a 16x2 I2C LCD and an indicator LED.

## Project Layout

```text
.
|-- README.md
`-- seismic_v3.ino
```

## Overview

The sketch:

- outputs a PWM signal on Arduino pin `9`
- turns on an indicator LED on pin `7`
- shows runtime status and speed on a `16x2` I2C LCD
- logs the current speed to the serial monitor at `9600` baud

The LCD is configured at I2C address `0x27`.

## Dependencies

This project uses the following Arduino libraries:

- `Wire.h`
- `LiquidCrystal_I2C.h`

Make sure the `LiquidCrystal_I2C` library is installed in the Arduino IDE before uploading.

## Pin Usage

- `D9`: PWM output (`potpin`)
- `D7`: LED output
- I2C LCD:
  - `SDA`: board I2C SDA pin
  - `SCL`: board I2C SCL pin
  - address: `0x27`

## Runtime Behavior

On startup the sketch:

1. initializes the PWM output and LED pin
2. initializes the LCD and shows a short boot screen
3. starts serial communication at `9600`

In the main loop it:

1. writes the current PWM value to pin `9`
2. keeps the LED on
3. increases `speeds` by `1` every second, starting from `170`
4. once the speed reaches `201`, it holds that value for `15` seconds
5. after that, it sets the speed to `0`

The LCD displays:

- `Running....`
- `Speed: <value>`

The same speed value is also printed to the serial monitor.

## Build and Upload

1. Open `seismic_v3.ino` in the Arduino IDE.
2. Select the correct board and COM port.
3. Install the required `LiquidCrystal_I2C` library if needed.
4. Upload the sketch to the Arduino.
5. Open the serial monitor at `9600` baud to view live speed values.

## Notes

- The current sketch uses `analogWrite()` on pin `9`, so the board must support PWM on that pin.
- The speed sequence does not automatically restart after reaching `0`. This is because `increment` is set to `0` once the top speed is reached and is never restored.
- If your LCD does not respond, verify the I2C address. Many modules use `0x27`, but some use `0x3F`.
