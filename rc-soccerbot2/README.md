# RC Soccer Bot 2

Arduino firmware for a serial-controlled soccer bot with a two-motor drive base.

## Hardware Mapping

- Right motor control on pins `3` and `4`
- Left motor control on pins `5` and `6`
- Serial command input at `9600` baud

## Control Commands

- `F` - forward
- `B` - backward
- `L` - left
- `R` - right
- `I` - forward-right
- `G` - forward-left
- `S` - stop

## Project Files

- `Soccer_bot.ino` - Arduino sketch

## Build

Open `Soccer_bot.ino` in the Arduino IDE, select the target board and serial port, and upload the sketch.
