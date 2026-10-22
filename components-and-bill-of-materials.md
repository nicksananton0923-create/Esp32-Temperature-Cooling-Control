# Components and Bill of Materials — ESP32 Temperature-Based Cooling Control System

## Bill of Materials

All items in this BOM are PROPOSED. No item has been confirmed against an inspected original parts list.

| Ref | Component | Quantity | Rating / Part | Status | Notes |
|---|---|---|---|---|---|
| U1 | ESP32 development board | 1 | ESP32-DevKitC or similar | PROPOSED | 3.3 V logic, Wi-Fi + BLE |
| U2 | DHT22 (AM2302) sensor | 1 | ±0.5 °C typical, 0–100 % RH | PROPOSED | Single-wire digital |
| R1 | 10 kΩ resistor | 1 | 1/4 W, ±5 % | PROPOSED | DHT22 data line pull-up to 3.3 V |
| U3 | 1-channel relay module (optocoupler-isolated) | 1 | 5 V or 3.3 V coil, 10 A contact | PROPOSED | Active-low assumed; verify |
| K1 | Contactor (if mains load) | 1 | Coil per local mains; contact per load | PROPOSED | Mains-side switching |
| D1 | Flyback diode (DC coil) or RC snubber (AC coil) | 1 | 1N4007 / 0.1 µF + 100 Ω | PROPOSED | Across contactor coil |
| F1 | MCB or fuse | 1 | Per load current | PROPOSED | Per-load protection |
| F0 | RCD / GFCI | 1 | 30 mA trip | PROPOSED | Earth leakage protection |
| PS1 | 5 V DC regulated supply | 1 | ≥ 500 mA | PROPOSED | ESP32 + relay module |
| ENC1 | Enclosure | 1 | IP54+ if not in controlled environment | PROPOSED | Per installation |

## Sensor Selection Notes

The DHT22 was chosen by the original designer. Its characteristics:

- Temperature range: −40 °C to +80 °C
- Temperature accuracy: ±0.5 °C typical (±2 °C maximum across range)
- Humidity range: 0–100 % RH
- Humidity accuracy: ±2 % RH typical (±5 % RH maximum)
- Sampling rate: maximum 0.5 Hz (one reading every 2 seconds)
- Output: single-wire digital, proprietary protocol

If higher accuracy or faster sampling is required, consider:

- **DS18B20** (1-Wire): ±0.5 °C, faster, more reliable, no humidity
- **BME280** (I²C / SPI): ±1 °C temperature, ±3 % RH humidity, faster sampling
- **SHT31** (I²C): ±0.3 °C temperature, ±2 % RH humidity, faster sampling
- **PT100** (RTD): ±0.1 °C or better with appropriate signal conditioning

Migration to a different sensor is a v2.0 future improvement.
