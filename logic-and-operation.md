# Logic and Operation — ESP32 Temperature-Based Cooling Control System

## Control Logic Truth Table

The control logic uses three temperature bands. The logic is preserved verbatim from the original specification and MUST NOT be changed without explicit approval.

| Temperature range | Cooling output | Band label |
|---|---|---|
| T < 25 °C | ON | LOW |
| 25 °C ≤ T ≤ 30 °C | OFF | MID |
| T > 30 °C | ON | HIGH |

## Non-Monotonic Behaviour

The logic is intentionally non-monotonic: the cooling output is ON at both low and high temperatures, and OFF only in the middle band. This is unusual for a cooling controller (typically a cooling controller is OFF below a threshold and ON above it). The rationale must be confirmed by the original designer. Possible rationales include:

- The cooling load may be a ventilator that brings in outside air to prevent condensation when the ambient temperature is low (below 25 °C), and to provide cooling when the ambient temperature is high (above 30 °C).
- The cooling load may be a heat exchanger that operates in two regimes: a dehumidification regime at low temperatures and a cooling regime at high temperatures.
- The cooling output may be a pump that circulates coolant to keep a process within a narrow band; below 25 °C the coolant may be too cold for the process and needs warming via the cooling circuit's bypass.

None of these rationales is confirmed. The original designer should document the actual rationale in this file before deployment.

## Threshold Crossings

The thresholds are 25 °C and 30 °C, with no hysteresis. This means:

- If the temperature sits at exactly 25.0 °C, the band is MID and the output is OFF.
- If the temperature sits at exactly 30.0 °C, the band is MID and the output is OFF.
- If the temperature fluctuates between 24.9 °C and 25.1 °C due to sensor noise, the output will toggle between ON and OFF on successive readings.

Adding configurable hysteresis (e.g. switch from OFF to ON at 24.5 °C and from ON to OFF at 25.5 °C) is listed as a future improvement but is NOT implemented in v1 because the original designer's logic must be preserved.

## Sensor Failure Handling

If the DHT22 read fails (e.g. sensor disconnected, communication error, checksum failure), the firmware:

1. Prints an error message to the Serial Monitor.
2. Leaves the cooling output in its current state.
3. Retries on the next scheduled reading.

This is a fail-safe-with-caution behaviour: the controller does not turn the output OFF on a sensor failure (which could allow a cooling load to overheat), but it also does not turn the output ON indefinitely (which could waste energy or cause overcooling). The behaviour is configurable by editing the firmware.

## Serial Monitor Output

At each reading, the firmware prints a line like:

```
[COOL] T=24.3 C  RH=58.0 %  band=LOW  output=ON
```

or on error:

```
[COOL] ERROR: DHT22 read failed (code -2)  output unchanged
```

This format is suitable for capturing to a log file via a serial terminal program for later analysis.
