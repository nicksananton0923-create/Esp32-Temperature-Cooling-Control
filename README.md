# ESP32 Temperature-Based Cooling Control System

## Table of Contents
1. [Project Purpose](#1-project-purpose)
2. [Problem Statement](#2-problem-statement)
3. [Project Objectives](#3-project-objectives)
4. [Current Project Status](#4-current-project-status)
5. [Confirmed Technologies and Components](#5-confirmed-technologies-and-components)
6. [Proposed Components](#6-proposed-components)
7. [System Operation](#7-system-operation)
8. [Architecture or Workflow](#8-architecture-or-workflow)
9. [Installation or Setup Instructions](#9-installation-or-setup-instructions)
10. [Testing Status](#10-testing-status)
11. [Safety Considerations](#11-safety-considerations)
12. [Known Limitations](#12-known-limitations)
13. [Future Improvements](#13-future-improvements)
14. [Repository Structure](#14-repository-structure)
15. [Licence Information](#15-licence-information)
16. [Status Label Convention](#16-status-label-convention)

## 1. Project Purpose

This project implements an ESP32-based controller that switches a cooling output based on temperature readings from a DHT22 sensor. The control logic uses three temperature bands and preserves the original design intent exactly: the cooling output is energised below 25 °C, de-energised between 25 °C and 30 °C, and energised above 30 °C. The project documents the proposed hardware, the firmware implementation, the wiring and isolation requirements, and the test plan that must be completed before any deployment. The package is intended to support portfolio review and continued development rather than immediate deployment in a real cooling application.

## 2. Problem Statement

Small-scale cooling applications such as equipment enclosures, grow tents, beverage coolers, and prototype environmental chambers often need a simple, inexpensive controller that switches a cooling load based on a single temperature reading. Commercial PID controllers are available but are over-specified and expensive for these applications. A microcontroller-based solution with a single sensor and a single relay output fills the gap. The trade-off is that such a controller is not a substitute for a certified industrial temperature controller in regulated or safety-critical applications. The non-monotonic control logic preserved in this project (cooling ON below 25 °C and above 30 °C, OFF in the middle band) is intentional and must be confirmed by the original designer before deployment.

## 3. Project Objectives

- Preserve the three-band control logic exactly as specified by the original designer.
- Provide a compilable ESP32 Arduino sketch implementing the logic.
- Document the DHT22 sensor interface and the relay output interface.
- Document safe relay and contactor interfaces for the cooling load.
- Provide a test plan covering threshold crossings, relay actuation, and endurance.
- Clearly mark all hardware as PROPOSED and all tests as NOT YET TESTED.
- Provide safety, limitations, and future-improvements documentation.

## 4. Current Project Status

| Item | Status |
|---|---|
| ESP32 as main controller | PROPOSED |
| DHT22 temperature/humidity sensor | PROPOSED |
| Relay module for cooling output | PROPOSED |
| Three-band control logic | IMPLEMENTED (preserved verbatim) |
| Pin assignments | PROPOSED — NOT VERIFIED |
| Firmware compile | NOT YET TESTED |
| Hardware build | NOT VERIFIED |
| Physical testing | NOT YET TESTED |

## 5. Confirmed Technologies and Components

No hardware has been confirmed against an inspected original sketch. The following technologies are proposed:

- ESP32 development board (e.g. ESP32-DevKitC, 3.3 V logic, Wi-Fi + BLE)
- DHT22 (AM2302) temperature and humidity sensor, single-wire digital interface
- 1-channel or 4-channel relay module with optocoupler isolation
- Contactor for the cooling load if mains-powered
- Regulated 5 V DC supply for the ESP32 and relay module
- 10 kΩ pull-up resistor for the DHT22 data line

Because no original sketch has been inspected for this portfolio entry, none of the above can be marked CONFIRMED. The control logic itself is preserved verbatim from the original specification, but the pin numbers in the firmware are PROPOSED placeholders that must be confirmed against the original design.

## 6. Proposed Components

| Component | Role | Notes |
|---|---|---|
| ESP32 development board | Main controller | 3.3 V logic, Wi-Fi + BLE |
| DHT22 (AM2302) sensor | Temperature and humidity measurement | ±0.5 °C typical accuracy |
| 10 kΩ resistor | DHT22 data line pull-up to 3.3 V | Required for reliable single-wire communication |
| 1-channel relay module (optocoupler-isolated) | Switches the cooling load | Active-low assumed; verify |
| Contactor (if mains load) | Mains-side load switching | Coil rating per local mains |
| Flyback diode / RC snubber | Inductive load protection | Across the contactor coil |
| 5 V DC regulated supply | ESP32 + relay module power | ≥ 500 mA |
| Enclosure (IP54+) | Cabinet protection | If installed outside a controlled environment |

## 7. System Operation

The controller reads the DHT22 temperature every 2 seconds and switches the cooling output based on the three-band logic. The control logic is intentionally non-monotonic and is preserved verbatim from the original specification. The truth table is:

| Temperature range | Cooling output | Band label |
|---|---|---|
| T < 25 °C | ON | Low band |
| 25 °C ≤ T ≤ 30 °C | OFF | Mid band |
| T > 30 °C | ON | High band |

At each temperature reading, the firmware prints the current temperature, humidity, the active band, and the cooling output state to the Serial Monitor at 115200 baud. This supports commissioning and debugging. The control logic does not include hysteresis: if the temperature sits exactly at 25 °C or 30 °C, the output may toggle on successive readings due to sensor noise. A future improvement is to add configurable hysteresis to the threshold values; this is listed in the development roadmap but is intentionally NOT implemented in v1 because the original designer's logic must be preserved.

## 8. Architecture or Workflow

The system architecture follows the same layered isolation pattern as the STP four-relay project. The ESP32 operates at 3.3 V logic and drives a single digital output to the input side of a relay module. The relay module uses an optocoupler for galvanic isolation. The relay output switches a contactor coil, which in turn switches the mains supply to the cooling load. The DHT22 sensor is connected to the ESP32 via a single-wire digital interface with a 10 kΩ pull-up resistor to 3.3 V. The DHT22 is powered from the ESP32's 3.3 V rail (the DHT22 accepts 3.3 V to 5.5 V; check the specific module's datasheet).

```
[DHT22] --single-wire--> [ESP32 GPIO]
                            |
                            v
                       [State machine: 3-band logic]
                            |
                            v
                       [ESP32 GPIO]
                            |
                            v
                  [Relay module (opto)]
                            |
                            v
                  [Contactor coil] --> [Cooling load]
```

Power supply architecture: a single mains input feeds a 5 V DC regulated supply for the ESP32 and relay module. The ESP32's onboard regulator steps this down to 3.3 V for the DHT22. The mains load is fed via the contactor and is fused independently of the low-voltage supply.

## 9. Installation or Setup Instructions

The firmware can be compiled and uploaded using the Arduino IDE with the ESP32 board support package installed. Steps:

1. Install the ESP32 board package in the Arduino IDE (Boards Manager → search "esp32" by Espressif).
2. Install the `DHT sensor library` by Adafruit (Library Manager → search "DHT sensor library").
3. Open `src/cooling_control.ino` in the Arduino IDE.
4. Select **Tools → Board → ESP32 Dev Module** (or your specific ESP32 board).
5. Select the correct COM port.
6. Edit the pin assignments at the top of the sketch if needed — the defaults are PROPOSED placeholders.
7. Edit the threshold values at the top of the sketch only if the original designer has approved a change. The defaults (25 °C and 30 °C) MUST NOT be changed without explicit approval per the project brief.
8. Upload the sketch.
9. Open the Serial Monitor at 115200 baud to view temperature, humidity, band, and cooling output state.
10. Before connecting any load, dry-run the relay output and confirm it actuates at the expected temperature thresholds.

Hardware setup must only be performed by a person competent to work with mains voltage if the cooling load is mains-powered.

## 10. Testing Status

All tests are currently **NOT YET TESTED**. No physical test has been performed on this package. The test plan in `docs/testing-and-validation.md` covers:

1. Firmware compile test (Arduino IDE with ESP32 board package)
2. DHT22 reading verification
3. Threshold crossing test (heat gun / ice pack)
4. Relay actuation test
5. Multi-cycle endurance test
6. Thermal inspection under load

Each test must be performed and the results recorded in this README before any deployment is considered.

## 11. Safety Considerations

If the cooling load is mains-powered (e.g. a refrigerator compressor, a fan on mains, a Peltier array on mains), the same safety considerations apply as for the STP four-relay project:

- Mains wiring by a competent person only
- Optocoupler isolation on the relay module
- Contactor with appropriate coil voltage and contact rating
- Flyback diode (DC coil) or RC snubber (AC coil)
- Per-load fuse and RCD protection
- Lockable upstream isolator for LOTO
- EPO button that cuts mains independently of the ESP32
- Enclosure rated for the environment

Additional DHT22-specific considerations:

- The DHT22 must be mounted away from direct heat sources and away from the cooling load's airflow, to ensure the reading reflects the ambient temperature rather than the load's outlet temperature.
- The DHT22's plastic housing is not waterproof. If the installation environment is humid or wet, the sensor must be mounted inside a breathable enclosure (e.g. a Stevenson screen or a simple vented plastic box).
- The DHT22's ±0.5 °C typical accuracy means the threshold crossing may be uncertain by up to ±0.5 °C. For applications requiring tighter control, a DS18B20 (±0.5 °C) or a PT100 (much higher accuracy with appropriate signal conditioning) should be used instead.

ESP32-specific considerations:

- The ESP32's GPIO pins are 3.3 V logic and are NOT 5 V tolerant. Connecting a 5 V signal to a GPIO pin can damage the ESP32.
- The ESP32's Wi-Fi radio draws significant current during transmission. The 5 V supply must be capable of at least 500 mA continuous to avoid brown-outs.
- The ESP32 has no watchdog enabled by default in the Arduino framework; enabling the hardware watchdog is a recommended future improvement.

## 12. Known Limitations

- **Non-monotonic control logic (intentional).** The cooling output is ON below 25 °C and above 30 °C, OFF in the middle. This is preserved verbatim from the original specification. The rationale must be confirmed by the original designer. If the rationale is no longer valid, a future version may switch to a more conventional two-band logic (OFF below threshold, ON above threshold).
- **No hysteresis.** If the temperature sits at exactly 25 °C or 30 °C, sensor noise may cause the output to toggle on successive readings. Adding configurable hysteresis is listed as a future improvement.
- **DHT22 accuracy is ±0.5 °C typical.** The threshold crossing may be uncertain by up to ±0.5 °C. Higher accuracy requires a different sensor.
- **No humidity-based control.** The DHT22 also reports humidity, but the current firmware does not use the humidity reading. Humidity-based control is listed as a future improvement.
- **No data logging.** Temperature history is not retained.
- **No remote monitoring.** Although the ESP32 has Wi-Fi, the firmware does not use it. Adding Wi-Fi telemetry is a future improvement.
- **Single point of failure.** A failure of the ESP32, the DHT22, the relay, or the power supply will stop the controller. This is acceptable for an educational or small-scale application but is not acceptable for a critical cooling load.

## 13. Future Improvements

- Add configurable hysteresis to the threshold values (with explicit approval from the original designer).
- Add Wi-Fi telemetry via MQTT to a local broker.
- Add an OLED display (0.96 inch, SSD1306) for local readout.
- Add an SD card data logger for temperature history.
- Add a real-time clock (RTC) for accurate timestamping.
- Migrate the DHT22 to a DS18B20 (1-Wire) or a BME280 (I²C) for better accuracy and reliability.
- Add a hardware watchdog timer.
- Add an OTA (over-the-air) firmware update capability.
- Add a PID control mode for tighter temperature regulation around a setpoint.

## 14. Repository Structure

```
05-esp32-temperature-cooling-control/
├── README.md
├── LICENSE
├── docs/
│   ├── project-overview.md
│   ├── requirements.md
│   ├── system-architecture.md
│   ├── logic-and-operation.md
│   ├── components-and-bill-of-materials.md
│   ├── wiring-and-connections.md
│   ├── testing-and-validation.md
│   ├── safety-considerations.md
│   ├── development-roadmap.md
│   └── limitations.md
└── src/
    └── cooling_control.ino
```

## 15. Licence Information

Released under the MIT Licence. See the `LICENSE` file for the full text.

## 16. Status Label Convention

This project uses the following status labels throughout its documentation. Each label has a strict meaning and is not used interchangeably with any other label.

| Label | Meaning |
|---|---|
| **CONFIRMED** | Directly supported by available project information or inspected source code. |
| **PROPOSED** | A suggested design or implementation. Has not been verified against built hardware. |
| **NOT VERIFIED** | Information that has not been confirmed. Requires verification before use. |
| **IMPLEMENTED** | A feature or system that has actually been created and exists in the source code. |
| **TESTED** | A test that has genuinely been performed with recorded results. |
| **NOT YET TESTED** | Code, hardware, or functionality that still requires testing. |

If a section does not carry any status label, the content of that section is informational prose and does not make a claim of verification, testing, or implementation.
