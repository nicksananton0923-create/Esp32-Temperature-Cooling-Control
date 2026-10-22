/*
 * ESP32 Temperature-Based Cooling Control System
 * ==============================================
 *
 * CONTROL LOGIC (PRESERVED VERBATIM — DO NOT CHANGE WITHOUT APPROVAL):
 *   T < 25 °C        → cooling output ON
 *   25 °C ≤ T ≤ 30 °C → cooling output OFF
 *   T > 30 °C        → cooling output ON
 *
 * Hardware:
 *   - ESP32 development board (3.3 V logic)
 *   - DHT22 (AM2302) temperature/humidity sensor
 *   - 1-channel relay module (optocoupler-isolated, active-low assumed)
 *
 * Status: PROPOSED
 * Tested: NOT YET TESTED
 *
 * Released under the MIT License.
 */

#include <DHT.h>

// ---------------------------------------------------------------------------
// Pin assignments
// STATUS: PROPOSED — NOT VERIFIED.
// Confirm against the original sketch before wiring.
// ---------------------------------------------------------------------------
#define PIN_DHT22_DATA     4
#define PIN_RELAY_COOLING  5

// ---------------------------------------------------------------------------
// Sensor configuration
// ---------------------------------------------------------------------------
#define DHT_TYPE           DHT22
#define READ_INTERVAL_MS   2000UL

// ---------------------------------------------------------------------------
// Control thresholds — PRESERVED VERBATIM FROM ORIGINAL SPECIFICATION.
// DO NOT CHANGE WITHOUT EXPLICIT APPROVAL FROM THE ORIGINAL DESIGNER.
// ---------------------------------------------------------------------------
#define TEMP_THRESHOLD_LOW   25.0f   // °C
#define TEMP_THRESHOLD_HIGH  30.0f   // °C

// ---------------------------------------------------------------------------
// Relay active level
// Most low-cost relay modules are active-LOW (LOW = relay ON).
// If your module is active-HIGH, set this to false.
// STATUS: PROPOSED — verify against the actual relay module's datasheet.
// ---------------------------------------------------------------------------
#define RELAY_ACTIVE_LOW   true

// ---------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------
static DHT dht(PIN_DHT22_DATA, DHT_TYPE);
static bool coolingOutputState = false;   // current output state (true = ON)
static unsigned long lastReadMs = 0;

// ---------------------------------------------------------------------------
// Helper: write the cooling output relay
// ---------------------------------------------------------------------------
static void setCoolingOutput(bool on) {
  coolingOutputState = on;
  bool level = RELAY_ACTIVE_LOW ? !on : on;
  digitalWrite(PIN_RELAY_COOLING, level ? HIGH : LOW);
}

// ---------------------------------------------------------------------------
// Helper: determine the active band from a temperature reading
// ---------------------------------------------------------------------------
// Returns: 0 = LOW (T < 25), 1 = MID (25 <= T <= 30), 2 = HIGH (T > 30)
static int determineBand(float temperatureC) {
  if (temperatureC < TEMP_THRESHOLD_LOW)  return 0;  // LOW
  if (temperatureC > TEMP_THRESHOLD_HIGH) return 2;  // HIGH
  return 1;                                            // MID
}

// ---------------------------------------------------------------------------
// Arduino setup
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println(F("[COOL] ESP32 cooling controller boot"));
  Serial.println(F("[COOL] WARNING: pin assignments are NOT VERIFIED."));
  Serial.println(F("[COOL] WARNING: confirm against original sketch before wiring."));
  Serial.println(F("[COOL] control logic preserved verbatim (per user spec):"));
  Serial.println(F("[COOL]   T < 25 C       -> output ON"));
  Serial.println(F("[COOL]   25 <= T <= 30  -> output OFF"));
  Serial.println(F("[COOL]   T > 30 C       -> output ON"));

  pinMode(PIN_RELAY_COOLING, OUTPUT);
  setCoolingOutput(false);   // safe state on power-on

  dht.begin();
  Serial.println(F("[COOL] DHT22 initialised."));
  Serial.println(F("[COOL] entering main loop."));
}

// ---------------------------------------------------------------------------
// Arduino loop
// ---------------------------------------------------------------------------
void loop() {
  unsigned long now = millis();

  if (now - lastReadMs < READ_INTERVAL_MS) {
    return;
  }
  lastReadMs = now;

  // Read DHT22
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println(F("[COOL] ERROR: DHT22 read failed — output unchanged"));
    return;
  }

  // Determine band
  int band = determineBand(t);
  const char* bandName = (band == 0) ? "LOW" : (band == 1) ? "MID" : "HIGH";

  // Apply control logic (preserved verbatim)
  //   LOW  -> ON
  //   MID  -> OFF
  //   HIGH -> ON
  bool newOutputState = (band == 0 || band == 2);

  if (newOutputState != coolingOutputState) {
    setCoolingOutput(newOutputState);
  }

  // Print diagnostics
  Serial.print(F("[COOL] T="));
  Serial.print(t, 1);
  Serial.print(F(" C  RH="));
  Serial.print(h, 1);
  Serial.print(F(" %  band="));
  Serial.print(bandName);
  Serial.print(F("  output="));
  Serial.println(coolingOutputState ? F("ON") : F("OFF"));
}
