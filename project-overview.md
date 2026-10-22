# Project Overview — ESP32 Temperature-Based Cooling Control System

## Summary

This project implements a single-output cooling controller based on the ESP32 and a DHT22 temperature sensor. The control logic uses three temperature bands and is preserved verbatim from the original specification.

| Temperature range | Cooling output |
|---|---|
| T < 25 °C | ON |
| 25 °C ≤ T ≤ 30 °C | OFF |
| T > 30 °C | ON |

## Status

This is a PROPOSED design package. The hardware has not been verified against an inspected original sketch. The firmware is an IMPLEMENTED starting point that compiles on an ESP32 with the standard Arduino ESP32 board package. No physical test has been performed, so all test items are NOT YET TESTED.

## Why ESP32

The ESP32 was chosen by the original designer. It provides 3.3 V logic, integrated Wi-Fi and BLE, multiple GPIO pins, and ample processing power for a simple temperature controller. The Wi-Fi capability is not used in v1 but is available for future telemetry improvements.

## Audience

The package is intended for the original designer (to confirm or correct pin assignments), for portfolio review by instructors or prospective employers, and for any engineer continuing development of the controller. It is not intended for direct deployment in a safety-critical cooling application without engineering review.
