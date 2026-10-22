# System Architecture — ESP32 Temperature-Based Cooling Control System

## Block Diagram

```
        +-----------+
        |   DHT22   |  single-wire digital
        |  sensor   |---------------+
        +-----------+               |
                                    v
                            +---------------+
                            |    ESP32      |
                            |  controller   |
                            |  3-band logic |
                            +-------+-------+
                                    |
                                    | GPIO (3.3 V logic)
                                    v
                            +---------------+
                            |  Relay module |
                            | (optocoupler) |
                            +-------+-------+
                                    |
                                    | dry contact
                                    v
                            +---------------+
                            |  Contactor    |
                            |     coil      |
                            +-------+-------+
                                    |
                                    | mains
                                    v
                            +---------------+
                            | Cooling load  |
                            | (fan / cooler)|
                            +---------------+
```

## Power Domains

- **Low-voltage domain:** 5 V DC regulated supply → ESP32 (via onboard 3.3 V regulator) → DHT22 (3.3 V) and relay module input side (5 V or 3.3 V, depending on module).
- **Mains domain:** 230 V AC (or local voltage) → contactor output → cooling load.

The two domains share only the protective earth (PE). All signal isolation between the ESP32 and the relay module is via the relay module's optocoupler. The contactor provides additional isolation between the relay module's dry contact and the mains load.

## Firmware Architecture

The firmware is a single-file Arduino sketch with a simple loop:

1. Every 2 seconds, read the DHT22 temperature and humidity.
2. If the read fails, print an error and leave the output unchanged.
3. Determine the active band (LOW / MID / HIGH) from the temperature.
4. Switch the cooling output ON or OFF based on the band.
5. Print temperature, humidity, band, and output state to Serial Monitor.

The firmware uses `millis()` for non-blocking timing rather than `delay()`, so the loop remains responsive. There is no state machine because the controller has no state other than the current band — each reading is processed independently.
