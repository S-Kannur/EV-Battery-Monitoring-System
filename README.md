# EV Battery & Thermal Monitoring System

An Arduino-based real-time telemetry node designed to monitor electric vehicle (EV) battery pack health, voltage levels (up to 25V DC), and pack temperature using hardware-calibrated analog sensing and firmware signal filtering.


Real-World Engineering Problems & Solutions

In real-world Electric Vehicles (EVs) and Energy Storage Systems (ESS), raw sensor readings are noisy and lithium chemistry requires strict operational limits. This project addresses four critical hardware and telemetry challenges:

1. Preventing Thermal Runaway & Battery Degradation
* The Problem: Lithium-ion and LFP cells experience severe capacity loss—or catastrophic thermal runaway—if operated above 45°C or over-discharged below safe voltage thresholds.
* The Solution: Continuous dual-parameter monitoring (Voltage + Temperature) provides real-time telemetry required for early safety alerts and automated load disconnects.

 2. High-Noise Signal Distortion on Bench & Vehicle Wiring
* The Problem: Switching noise from power converters and long breadboard wires causes analog-to-digital converter (ADC) jitter, making raw readings flicker erratically.
* The Solution: Implemented software-level moving average filtering to smooth out high-frequency noise without requiring expensive external active filters.

 3. Microcontroller Supply Rail (VREF) Drift
* The Problem: USB and onboard 5V regulators rarely output a perfect 5.000V (often hovering between 4.75V and 4.88V), introducing systematic measurement errors into standard ADC formulas.
* The Solution: Programmed dynamic VREF rail calibration variables, allowing the system to scale calculations against the true DMM-measured supply voltage.

 4. Resistor Tolerance Error Scaling
* The Problem: Standard 5% tolerance resistors in a voltage divider (30kΩ / 7.5kΩ) introduce up to ±1.25V of error when stepping down 25V signals.
* The Solution: Used multimeter-verified resistance values (R1, R2) directly in the voltage transfer function to maintain ±0.05V measurement accuracy.



Hardware Requirements

* Microcontroller: Arduino Uno (ATmega328P)
* Display: 16x2 LCD with PCF8574 I2C Backpack
* Temperature Sensor: TMP36 Analog Temperature Sensor
* Voltage Divider: 30kΩ (R1) and 7.5kΩ (R2) Resistors (5:1 reduction ratio)
* Power Supply: Variable DC Power Supply / 12V–25V Battery Pack


### Circuit Schematic
[Circuit Diagram](hardware/schematic.png)

How to Run & Calibrate

1. Measure Bench Variables: Use a Digital Multimeter (DMM) to measure your Arduino's exact 5V rail voltage and the precise resistance of R1 and R2.
2. Update Calibration Constants: Open `firmware/main.ino` and update the constants:
   ```cpp
   float vRef = 4.88;    // Measured rail voltage
   float r1 = 29850.0;   // Measured R1 resistance
   float r2 = 7480.0;    // Measured R2 resistance
