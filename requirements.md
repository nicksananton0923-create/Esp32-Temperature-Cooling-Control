# Requirements — ESP32 Temperature-Based Cooling Control System

## Functional Requirements

| ID | Requirement | Status |
|---|---|---|
| FR-01 | The controller shall read the DHT22 temperature at a configurable interval (default 2 s). | IMPLEMENTED |
| FR-02 | The controller shall switch a single cooling output based on a three-band logic. | IMPLEMENTED |
| FR-03 | The three temperature bands shall be: T < 25 °C → ON; 25 °C ≤ T ≤ 30 °C → OFF; T > 30 °C → ON. | IMPLEMENTED (preserved verbatim) |
| FR-04 | The controller shall print temperature, humidity, active band, and output state to the Serial Monitor. | IMPLEMENTED |
| FR-05 | The controller shall enter a safe state (output OFF) on power-on. | IMPLEMENTED |
| FR-06 | The controller shall handle DHT22 read failures gracefully (output unchanged, error reported). | IMPLEMENTED |

## Non-Functional Requirements

| ID | Requirement | Status |
|---|---|---|
| NFR-01 | The firmware shall compile on the ESP32 Arduino core without third-party libraries except the Adafruit DHT library. | IMPLEMENTED |
| NFR-02 | The control logic shall be preserved exactly from the original specification; threshold values shall not be changed without explicit approval. | IMPLEMENTED |
| NFR-03 | The relay output shall be galvanically isolated from the ESP32 via an optocoupler. | PROPOSED |
| NFR-04 | Mains loads shall be switched via a contactor, not directly via the relay module. | PROPOSED |
| NFR-05 | The enclosure shall be rated for the installation environment. | PROPOSED |

## Out-of-Scope

- Wi-Fi telemetry (v1 does not use the ESP32's Wi-Fi)
- OLED display
- Data logging
- PID control
- Hysteresis
- Humidity-based control

These items are listed in `development-roadmap.md` as future improvements.
