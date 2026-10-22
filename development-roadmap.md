# Development Roadmap — ESP32 Temperature-Based Cooling Control System

## v1.0 (current — PROPOSED starting point)

- Three-band control logic (preserved verbatim)
- DHT22 sensor interface
- Single relay output
- Serial Monitor diagnostics
- Documentation package

## v1.1 (planned)

- Add configurable hysteresis to the threshold values (with explicit approval from the original designer).
- Add a hardware watchdog timer.
- Add a status LED on GPIO 2.
- Add a pause button on GPIO 12.

## v1.2 (planned)

- Add an OLED display (0.96 inch, SSD1306) for local readout of temperature, humidity, band, and output state.
- Add an SD card data logger for temperature history.
- Add a real-time clock (DS3231) for accurate timestamping.

## v2.0 (planned)

- Add Wi-Fi telemetry via MQTT to a local broker (e.g. Mosquitto on a Raspberry Pi).
- Add a web dashboard (e.g. Grafana) for historical visualisation.
- Add OTA (over-the-air) firmware update capability.

## v2.1 (planned)

- Migrate from DHT22 to BME280 (I²C) for better accuracy and reliability.
- Add humidity-based control mode.
- Add PID control mode for tighter temperature regulation around a setpoint.

## v3.0 (future)

- Migrate to an industrial-grade controller for production deployment.
- Add redundant sensors.
- Add redundant power supplies.
- Add UPS for ride-through during short mains interruptions.
- Add compliance with relevant standards (e.g. IEC 61010 for electrical measurement equipment).
