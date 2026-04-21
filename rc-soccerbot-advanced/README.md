# RC Soccer Bot Advanced

Arduino-based RC soccer bot firmware with direct PPM receiver input and IBT-2 / BTS7960 motor-driver control.

## Hardware Mapping

- PPM receiver input on digital pin `2`
- Right motor driver pins: `6` and `5`
- Left motor driver pins: `10` and `9`

## Control Logic

- Reads `8` PPM channels through `PPMReader`
- Uses channel `3` for lateral demand
- Uses channel `1` for rotation demand
- Uses channel `5` as the arm/disarm threshold
- Mixes lateral and rotation inputs into left and right motor demand values
- Stops both motors when the arm condition is not met

## Project Files

- `rc-soccerbot.ino` - main Arduino sketch
- `Motor.h` / `Motor.cpp` - IBT-2 motor-driver wrapper
- `PPMReader.h` / `PPMReader.cpp` - PPM input reader
- `rc-soccerbot.rar` - archived project file

## Build

Open `rc-soccerbot.ino` in the Arduino IDE, compile with the bundled source files, and upload to the target controller board.
