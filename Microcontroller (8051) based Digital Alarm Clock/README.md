# Microcontroller (8051) Based Digital Alarm Clock

8051-based digital alarm clock project that includes assembly firmware, a Proteus simulation, and the final project report.

## Hardware Overview

- `AT89C52` target microcontroller
- `16x2` LCD connected on `P1`
- `4x4` keypad connected on `P2`
- Buzzer on `P3.7`
- Alarm indicator output on `P3.6`

The firmware supports clock display, manual time entry, alarm entry, alarm enable and disable, and a snooze flow after alarm acknowledgement.

## Project Files

- `EEE4706_PROJECT-FINAL.asm` - main assembly source
- `alarm_clock_B2_G2.pdsprj` - Proteus project
- `DIGITAL ALARM CLOCK_B2_G2.pdf` - final report

## Firmware Behavior

- `D` switches between the clock screen and time-edit mode.
- `*` opens alarm setup.
- The alarm compares stored hour and minute values against the running clock.
- When the alarm triggers, the keypad value `07` must be entered before the snooze menu is shown.
- Snooze options available in the code are `0`, `1`, `2`, and `3`.

## Build and Run

1. Assemble `EEE4706_PROJECT-FINAL.asm` with an 8051 assembler such as Keil `A51`.
2. Load the generated program into the Proteus project.
3. Run the simulation and use the keypad to set the time and alarm.
