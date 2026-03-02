# Errata for Controller PCB V1.00





1. The filament bias circuit should be after the fuses so that an external DC power supply still has the option to utilize the bias circuit without connecting through the unused transformer fuses.
2. Though there was an intent to be able to use the Vcc+/Vcc- instead of the diode regulator for IC803 XR1091, the jumpers (and tracks) to support it were forgotten.
3. D3SBA20 0.3" pitch bridges use a pin spacing not common. Many current 3A bridges are 0.15" or 0.2" even pin pitch. Diotec GBA10 series has 0.4/0.3/0.3 (same as D5SBA20) 10x for 85 cents each at DigiKey. The long pin will likely bend out.
4. Some I2C modules are 3.3V so it may make sense to route out the 3.3V Nano output and have it jumper selectable for the I2C ports.
5. PT6315 DOUT (SDOUT) is open drain and needs a pull up adding to use it.
6. The two buttons have incorrect pitch to properly flush mount a VSG1024 button. They should be changed to the common 4-pin square button type used everywhere.
7. Some consumer front panels use DC filament power and it would be clearer to rename FIL1 to FIL+ and FIL2 to FIL-.





