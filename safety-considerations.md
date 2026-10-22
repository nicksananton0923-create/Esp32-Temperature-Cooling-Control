# Safety Considerations — ESP32 Temperature-Based Cooling Control System

## Mains Voltage Safety

If the cooling load is mains-powered, the same safety considerations apply as for any mains-switching project:

- Mains wiring by a competent person only
- Optocoupler isolation on the relay module
- Contactor with appropriate ratings
- Flyback diode (DC coil) or RC snubber (AC coil)
- Per-load fuse and RCD protection
- Lockable upstream isolator for LOTO
- EPO button that cuts mains independently of the ESP32
- Enclosure rated for the environment

## ESP32-Specific Considerations

The ESP32 is a 3.3 V logic device. The following are important safety considerations:

- **GPIO pins are NOT 5 V tolerant.** Connecting a 5 V signal to a GPIO pin can damage the ESP32. Use a level shifter if interfacing with 5 V logic.
- **ESP32 GPIO source/sink current is limited** (typically 12 mA per pin, 40 mA absolute maximum). Do not drive a relay coil directly from a GPIO pin — always use a relay module with optocoupler isolation.
- **Wi-Fi transmission draws significant current** (up to 500 mA peaks). The 5 V supply must be capable of supplying this without drooping. Use a supply rated for at least 1 A continuous.
- **The ESP32's onboard 3.3 V regulator is limited** (typically 600 mA). If powering many 3.3 V peripherals, use an external 3.3 V regulator.

## DHT22-Specific Considerations

- **The DHT22 is not waterproof.** Do not expose the sensor to direct water spray. If the environment is wet, mount the sensor in a vented enclosure.
- **The DHT22's accuracy is ±0.5 °C typical.** For applications requiring tighter control, use a different sensor (DS18B20, BME280, SHT31, PT100).
- **The DHT22's sampling rate is limited to 0.5 Hz.** Faster sampling requires a different sensor.
- **The DHT22's plastic housing can degrade under UV exposure.** If installed outdoors, shield from direct sunlight.

## Thermal Considerations

- The ESP32 dissipates up to 0.5 W during Wi-Fi transmission. In a sealed enclosure, this can raise the internal temperature significantly. Provide ventilation or use a thermally-conductive enclosure.
- The relay module dissipates ~0.5 W per active relay. In a multi-relay enclosure, this adds up.
- The contactor dissipates ~1–3 W when energised. Mount the contactor on a DIN rail with appropriate spacing from the ESP32.

## Fail-Safe Behaviour

The firmware's fail-safe behaviour on sensor failure is to leave the output unchanged. This is a deliberate choice: turning the output OFF on a sensor failure could allow a cooling load to overheat, while turning it ON indefinitely could waste energy or cause overcooling. The choice must be reviewed by the original designer in the context of the specific application.

If the application requires a different fail-safe behaviour (e.g. output OFF on sensor failure, or output ON on sensor failure), edit the firmware accordingly. The choice must be documented in this file.

## Out of Scope

This safety document does not cover:
- Refrigerant handling (if the cooling load is a refrigeration compressor)
- Pressure vessel safety (if the cooling load is a chiller)
- Food safety (if the cooling load is a food storage unit)
- Medical safety (if the cooling load is a medical storage unit)

These items are the responsibility of the application designer and are out of scope for the controller package.
