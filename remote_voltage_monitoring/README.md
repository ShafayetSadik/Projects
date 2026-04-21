# Remote Voltage Monitoring

This repository contains a set of Arduino/ESP32 sketches for a remote battery-voltage monitoring prototype. The project focuses on reading battery voltage through an analog divider, publishing values to Blynk, and experimenting with status messaging, button/switch input, and GPS passthrough.

The codebase is not a single polished firmware package. It is a working repository of multiple iterations and test sketches, with `final2/final2.ino` appearing to be the latest Blynk-based monitoring variant.

## What The Project Does

- Reads analog voltage from a battery sensing circuit.
- Applies calibration factors to estimate the real battery voltage.
- Sends live values to a Blynk dashboard from an ESP32 over Wi-Fi.
- Updates charging / collection-point style status messages through Blynk virtual pins.
- Includes experimental sketches for GPS serial passthrough and simple switch testing.

## Repository Layout

- [`final2/final2.ino`](./final2/final2.ino): main two-voltage Blynk sketch. Reads the ADC on GPIO `34`, publishes two calibrated voltage values, and updates a battery status message based on a Blynk switch.
- [`final1/final1.ino`](./final1/final1.ino): earlier single-voltage Blynk version with charging and collection-point messages.
- [`espcode/espcode.ino`](./espcode/espcode.ino): earlier Blynk sketch using separate virtual switches for charging and collection status.
- [`claude2/claude2.ino`](./claude2/claude2.ino): voltage monitoring plus raw GPS NMEA forwarding to Blynk.
- [`onlygps/onlygps.ino`](./onlygps/onlygps.ino): GPS passthrough test using `Serial2`.
- [`switch/switch.ino`](./switch/switch.ino): simple physical button input test on GPIO `25`.
- [`sending_receiving_final/sending_receiving_final.ino`](./sending_receiving_final/sending_receiving_final.ino): basic voltage-divider measurement sketch using analog input and resistor scaling.
- `*.pdf`: hardware references and manuals kept alongside the firmware experiments.

## Hardware Used In The Sketches

Based on the code, the project is built around:

- ESP32 development board
- Voltage divider connected to an analog input
- Wi-Fi connectivity for Blynk
- Optional GPS module on UART2
- Optional push button / external switch

Common pin usage in the current sketches:

- `GPIO34`: analog voltage sensing
- `GPIO25`: button input test
- `GPIO16`: GPS RX2
- `GPIO17`: GPS TX2

## Blynk Mapping

The Blynk-enabled sketches use virtual pins such as:

- `V0`: main voltage value
- `V2`: battery discharge status text
- `V30`: switch input
- `V31`, `V32`, `V33`: status messages in earlier versions
- `V40`: second calibrated voltage in `final2`

You should align these pins with your Blynk template/dashboard before uploading.

## Development Setup

1. Install Arduino IDE or PlatformIO with ESP32 board support.
2. Install the required libraries:
   - `WiFi`
   - `Blynk`
3. Open the sketch you want to upload, most likely `final2/final2.ino`.
4. Set your Wi-Fi SSID and password.
5. Set your Blynk template ID, template name, and auth token.
6. Select the correct ESP32 board and serial port.
7. Upload the sketch and open Serial Monitor for debugging.

## Notes On Calibration

The sketches use simple multiplier-based calibration after reading the ESP32 ADC. For example:

- `final1` and `espcode` use a factor derived from `12.0 / 2.35`
- `final2` uses two different factors:
  - `12.0 / 3`
  - `12.0 / 2.4`

These values depend on the resistor divider, ADC behavior, and the real voltage range of the battery pack. They will likely need adjustment on actual hardware.

## Security And Cleanup

Some sketches currently contain hardcoded:

- Wi-Fi SSIDs
- Wi-Fi passwords
- Blynk auth tokens

These should be removed from source control and replaced with local configuration before using the project in a shared or public environment.

## Recommended Starting Point

If you want to continue this project, start with [`final2/final2.ino`](./final2/final2.ino) and then:

1. Move credentials into a separate local config file.
2. Standardize one final dashboard pin mapping.
3. Consolidate the older prototype sketches or archive them clearly.
4. Add a wiring diagram and real calibration measurements.
5. Decide whether GPS support belongs in the main firmware or a separate branch.

## Status

This repository currently looks like a prototype / research workspace rather than a finalized product release. That is useful for experimentation, but it means setup and calibration still depend on the target hardware and dashboard configuration.
