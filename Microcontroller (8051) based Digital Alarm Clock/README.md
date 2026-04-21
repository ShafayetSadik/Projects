# Microcontroller (8051) Based Digital Alarm Clock

An 8051 assembly project for a digital alarm clock with a 16x2 LCD, 4x4 keypad, buzzer, and alarm indicator LED. The project includes both the firmware source and a Proteus simulation project.

## Overview

This system implements a simple real-time clock on an `AT89C52` microcontroller. The current time is shown on the LCD, and the user can:

- set the current time
- configure an alarm
- enable or disable the alarm
- stop or snooze the alarm
- solve a small keypad challenge before the snooze menu appears

The firmware is written in 8051 assembly and stored in [`EEE4706_PROJECT-FINAL.asm`](./EEE4706_PROJECT-FINAL.asm). The Proteus simulation project is [`alarm_clock_B2_G2.pdsprj`](./alarm_clock_B2_G2.pdsprj).

## Features

- Real-time clock display in `HH:MM:SS` format
- Manual time entry using the keypad
- Alarm time entry in `HH:MM` format
- Alarm enable flag stored from keypad input (`0` or `1`)
- Alarm indicator on the LCD and LED output
- Buzzer activation when alarm time matches the current time
- Fixed challenge prompt before alarm resolution (`07` in the current code)
- Snooze options for `1`, `2`, or `3` minutes, or `0` to stop the alarm

## Hardware Mapping

The pin usage is defined near the top of the assembly source:

- `P1` -> LCD data port
- `P3.0` -> LCD `RS`
- `P3.1` -> LCD `EN`
- `P2` -> 4x4 keypad port
- `P3.7` -> buzzer
- `P3.6` -> alarm-set LED

The Proteus project archive indicates the simulated MCU is `AT89C52`.

## Keypad Controls

The keypad layout in the code is:

```text
1 2 3 A
4 5 6 B
7 8 9 C
* 0 # D
```

Main controls used by the firmware:

- `D` toggles between clock view and time edit mode
- `*` enters alarm setup mode
- `0-9` are used for numeric entry
- `A`, `B`, `C`, and `#` exist in the keypad map but are not used by the current firmware flow

Alarm workflow:

- Enter alarm hour and minute
- Enter alarm enable state: `0` = disabled, `1` = enabled
- When the alarm triggers, the LCD asks for the fixed 2-digit secret key `07`
- After entering the correct key, choose one of the following:
- `0` to stop the alarm
- `1` to snooze for 1 minute
- `2` to snooze for 2 minutes
- `3` to snooze for 3 minutes

## Project Files

- [`EEE4706_PROJECT-FINAL.asm`](./EEE4706_PROJECT-FINAL.asm) - main 8051 assembly source
- [`alarm_clock_B2_G2.pdsprj`](./alarm_clock_B2_G2.pdsprj) - Proteus project
- [`DIGITAL ALARM CLOCK_B2_G2.pdf`](./DIGITAL%20ALARM%20CLOCK_B2_G2.pdf) - project report/documentation

## How to Run

### Option 1: Proteus simulation

1. Open `alarm_clock_B2_G2.pdsprj` in Proteus.
2. Load the project as-is and start the simulation.
3. Use the keypad in the schematic to set the time and alarm.

### Option 2: Rebuild the firmware

1. Open `EEE4706_PROJECT-FINAL.asm` in an 8051 assembler such as Keil `A51`.
2. Build the source to generate a `.HEX` file.
3. Load the generated firmware into the `AT89C52` in Proteus.
4. Run the simulation.

## Firmware Notes

- Timekeeping is driven by `Timer 1` interrupt logic in the assembly source.
- The current time is stored in RAM locations for hours, minutes, seconds, and sub-seconds.
- Alarm comparison is performed against hour and minute values.
- The displayed alarm challenge uses a fixed expected value defined in the code (`07`).
