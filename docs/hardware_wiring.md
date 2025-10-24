# Wiring Diagram

## NodeMCU → Joystick

--------------------
3V3  → VCC
GND  → GND
A0   → VRX
D1   → VRY
D2   → SW

## NodeMCU → LED Strip

--------------------
D4 (GPIO2) → DIN
VIN (5V)   → LED 5V (from external power)
GND        → Common ground with power and joystick
