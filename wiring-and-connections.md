# Wiring and Connections — ESP32 Temperature-Based Cooling Control System

## Pin Assignments

**STATUS: PROPOSED — NOT VERIFIED.** The pin assignments below are placeholders. Confirm against the original sketch before wiring.

| Function | ESP32 Pin | Status | Notes |
|---|---|---|---|
| DHT22 data | GPIO 4 | PROPOSED — NOT VERIFIED | Default placeholder; supports any GPIO |
| Relay module input | GPIO 5 | PROPOSED — NOT VERIFIED | Default placeholder; supports any GPIO |
| Serial Monitor TX | GPIO 1 (U0TXD) | IMPLEMENTED | 115200 baud |
| Serial Monitor RX | GPIO 3 (U0RXD) | IMPLEMENTED | 115200 baud |
| Onboard LED | GPIO 2 | PROPOSED | Used for status in future versions |
| (future) Pause button | GPIO 12 | PROPOSED | Not implemented in v1 |
| (future) Status buzzer | GPIO 13 | PROPOSED | Not implemented in v1 |

## DHT22 Wiring

The DHT22 (AM2302) module has three or four pins depending on the breakout board. The most common configuration is:

```
ESP32 3V3  ──────►  DHT22 VCC
ESP32 GND  ──────►  DHT22 GND
ESP32 GPIO4 ─┬────►  DHT22 DATA
             │
            10 kΩ resistor
             │
ESP32 3V3  ──┘
```

The 10 kΩ pull-up resistor is required for reliable single-wire communication, especially for cable lengths over 30 cm. Some DHT22 breakout boards include the pull-up resistor on the board; check the board's documentation before adding an external resistor.

## Relay Module Wiring

The relay module is assumed to be optocoupler-isolated and active-low. The wiring is:

```
ESP32 5V (or 3V3)  ──────►  Relay module VCC
ESP32 GND          ──────►  Relay module GND (input side)
ESP32 GPIO5        ──────►  Relay module IN
```

If the relay module has a separate JD-VCC jumper for isolation, remove the jumper and feed JD-VCC from a separate 5 V supply with its own ground. This provides true galvanic isolation.

**Important:** ESP32 GPIO pins are 3.3 V logic. If the relay module requires a 5 V input signal (some modules specify 5 V on the IN pin), use a level shifter or a transistor driver. Most optocoupler-isolated modules accept 3.3 V input because the optocoupler's LED forward voltage is around 1.2 V; verify against the module's datasheet.

## Contactor Wiring (mains load)

For a 24 V DC coil contactor:

```
24 V DC + ─────► Flyback diode cathode ─────► Contactor coil +
                                                      │
24 V DC − ─────► Flyback diode anode      Contactor coil −
                                                      │
Relay COM ────► ───────────────────────────────────────┘
Relay NO  ────► (returns to 24 V DC − through the coil)
```

For a 230 V AC coil contactor, replace the flyback diode with an RC snubber (0.1 µF X2 capacitor in series with 100 Ω resistor) across the coil.

## Mains Wiring

```
RCD output L ──► MCB ──► Contactor NO ──► Cooling load L
RCD output N ───────────────────────────► Cooling load N
PE bus ──────────────────────────────────► Cooling load PE
```

## DHT22 Placement

The DHT22 must be mounted in a location that reflects the temperature of the controlled space, not the temperature of the cooling load's outlet or the ESP32's heat. Recommended placement:

- At least 30 cm from the cooling load's outlet airflow
- At least 10 cm from the ESP32 (which dissipates ~0.5 W during Wi-Fi transmission)
- Shielded from direct sunlight
- Away from heat sources (transformers, power supplies, motors)
- In a vented enclosure if the environment is humid or wet

The DHT22's plastic housing is not waterproof. Do not expose the sensor to direct water spray.
