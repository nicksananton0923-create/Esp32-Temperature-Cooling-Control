# Testing and Validation — ESP32 Temperature-Based Cooling Control System

## Test Status Summary

| Test ID | Test | Status | Performed by | Date |
|---|---|---|---|---|
| T-01 | Firmware compile test | NOT YET TESTED | — | — |
| T-02 | DHT22 reading verification | NOT YET TESTED | — | — |
| T-03 | Threshold crossing test (cooling ON at 24 °C) | NOT YET TESTED | — | — |
| T-04 | Threshold crossing test (cooling OFF at 27 °C) | NOT YET TESTED | — | — |
| T-05 | Threshold crossing test (cooling ON at 31 °C) | NOT YET TESTED | — | — |
| T-06 | Relay actuation test | NOT YET TESTED | — | — |
| T-07 | Sensor failure handling test | NOT YET TESTED | — | — |
| T-08 | 24-hour endurance test | NOT YET TESTED | — | — |

No test has been performed on this package. The procedures below must be executed before any deployment.

## Test Procedures

### T-01 Firmware Compile Test
1. Install the ESP32 board package in the Arduino IDE.
2. Install the Adafruit DHT sensor library.
3. Open `src/cooling_control.ino`.
4. Select **Tools → Board → ESP32 Dev Module**.
5. Click **Verify/Compile**.
6. **Pass criterion:** compilation completes with no errors and no warnings.

### T-02 DHT22 Reading Verification
1. Upload the firmware to the ESP32.
2. Connect the DHT22 per the wiring table.
3. Open the Serial Monitor at 115200 baud.
4. Observe readings for at least 60 seconds.
5. **Pass criterion:** readings appear at the expected 2-second interval, temperature is plausible (within ±5 °C of a reference thermometer), humidity is plausible (within ±10 % RH of a reference hygrometer).

### T-03 Threshold Crossing Test (Low Band → ON)
1. Place the DHT22 in an environment below 25 °C (e.g. a refrigerator at 4 °C, an ice-water bath in a sealed bag).
2. Allow the temperature to stabilise.
3. Observe the Serial Monitor.
4. **Pass criterion:** the firmware reports `band=LOW` and `output=ON`.

### T-04 Threshold Crossing Test (Mid Band → OFF)
1. Place the DHT22 in an environment between 25 °C and 30 °C (e.g. a controlled room at 27 °C).
2. Allow the temperature to stabilise.
3. **Pass criterion:** the firmware reports `band=MID` and `output=OFF`.

### T-05 Threshold Crossing Test (High Band → ON)
1. Place the DHT22 in an environment above 30 °C (e.g. near a warm air source at 35 °C).
2. Allow the temperature to stabilise.
3. **Pass criterion:** the firmware reports `band=HIGH` and `output=ON`.

### T-06 Relay Actuation Test
1. Connect the relay module to the ESP32 per the wiring table.
2. Do NOT connect a load to the relay output.
3. Observe the relay's status LED or listen for the relay click.
4. **Pass criterion:** the relay actuates (LED on, click heard) when the firmware reports `output=ON` and de-actuates when the firmware reports `output=OFF`.

### T-07 Sensor Failure Handling Test
1. With the firmware running, disconnect the DHT22 data line.
2. Observe the Serial Monitor.
3. **Pass criterion:** the firmware prints an error message and leaves the output unchanged (does not turn OFF the load on a sensor failure).
4. Reconnect the DHT22 data line.
5. **Pass criterion:** the firmware resumes normal operation within 4 seconds.

### T-08 24-Hour Endurance Test
1. Configure the firmware with default parameters.
2. Connect the DHT22 and the relay module.
3. Place the DHT22 in an environment where the temperature fluctuates across the 25 °C and 30 °C thresholds (e.g. a room with day/night temperature variation).
4. Run continuously for 24 hours.
5. **Pass criterion:** no firmware crash, no memory leak, no relay failure, no sensor failure that does not recover automatically.
