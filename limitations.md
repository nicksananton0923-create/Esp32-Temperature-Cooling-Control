# Limitations — ESP32 Temperature-Based Cooling Control System

## Logic Limitations

- **Non-monotonic control logic (intentional).** The cooling output is ON below 25 °C and above 30 °C, OFF in the middle. The rationale must be confirmed by the original designer.
- **No hysteresis.** Threshold crossings at exactly 25 °C or 30 °C may cause output toggling due to sensor noise.
- **No humidity-based control.** The DHT22 reports humidity but the firmware does not use it.
- **No PID control.** All switching is on/off, not proportional.

## Sensor Limitations

- **DHT22 accuracy is ±0.5 °C typical.** Threshold crossings may be uncertain by up to ±0.5 °C.
- **DHT22 sampling rate is 0.5 Hz maximum.** Faster sampling requires a different sensor.
- **DHT22 is not waterproof.** Wet environments require a vented enclosure.
- **DHT22 has known reliability issues** with some clones. Genuine DHT22 modules from reputable suppliers are recommended.

## Hardware Limitations

- **Pin assignments are NOT VERIFIED.** The defaults in the firmware are placeholders and must be confirmed against the original design.
- **Relay module type is assumed, not confirmed.** Active-low assumption must be verified.
- **No contactor ratings are confirmed.** The BOM ratings are typical values.
- **No environmental rating is confirmed.** Enclosure rating must be selected for the installation environment.
- **No redundancy.** A failure of any single component stops the controller.

## Firmware Limitations

- **No data logging.** Temperature history is not retained.
- **No remote monitoring.** Wi-Fi is not used in v1.
- **No OTA update.** Firmware updates require a wired connection.
- **No watchdog.** A firmware crash will leave the controller in its last state until manual reset.

## Scope Limitations

This package does not cover:
- Refrigerant handling
- Pressure vessel safety
- Food safety
- Medical safety
- Compliance with specific industry standards

These items are out of scope and are the responsibility of the application designer.
