# Errata for Controller PCB V1.00



1. Using a PT6315 based front panel, DOUT (SDOUT) is open drain and needs a pull-up adding to use it. To be added in the next version.
2. The two buttons have incorrect pitch to properly flush mount a VSG1024 button. To be changed to the common 4-pin square button type used everywhere.
3. Many standard negative voltage integrated controllers operate an anode range from Vbb- to Vcc+ are only rated to Vbb- = (Vcc+)-35 absolute max and (Vcc+)-30 nominal. A -36V Vbb- supply is therefore too high so a component update is needed to change ZD340 to 24V Zener and possibly increase R342. Positive voltage shift register drivers operate an anode range from 0V to Vbb+ and typically rated Vbb+ to 60V.
4. R828 \& R829 (390R) are too low and running hot. Calculated value indicates 820R is a better fit.



## Design Improvements for the Next Version



1. The filament bias circuit should be after the fuses so that an external DC power supply still has the option to utilize the bias circuit without connecting through the unused transformer fuses.
2. Though there was an intent to be able to use the Vcc+/Vcc- instead of the diode regulator for IC803 (XR1091), the tracks \& jumpers to support it were forgotten.
3. D3SBA20 0.3" pitch bridges use a pin spacing not common. Many current 3A bridges are 0.15" or 0.2" even pin pitch. Diotec GBA10 series has 0.4/0.3/0.3, 10x for 85 cents each at DigiKey. The long pin will likely bend in.
4. Some I2C modules are 3.3V so it may make sense to route out the 3.3V Nano output and have it jumper selectable for the I2C ports.
5. Some consumer front panels use DC filament power and it would be clearer to rename FIL1 to FIL+ and FIL2 to FIL-.
6. When using a SMPSU from consumer electronics to power the board, not enough 5V power is consumed to keep the Vbb rail at voltage. Two 1W dummy load resistors can be added on Vcc+ to accommodate.
7. The 16MHz, 32K ROM, 2K SRAM on the Atmel based Nano is looking a bit tight for 16 displays. To consider supporting the Nano ESP32 with 2x240MHz, 384Kb ROM, 512Kb SRAM but it's 3.3V only all up and not 5V input tolerant. Other options in this form factor include Nano R4 \& Nano RP2040, or adding a 2nd Atmel Nano.
8. R332, R342, R1x1, R1x2, R828, R829 should be 1W but were placed as 0.25W so the pads, holes and spacing are two small. They should be 0.6" pitch.
9. If 1W glass BZV85 Zener diodes are used, the pads, holes and spacing are too small. They should be 0.4" pitch (standard resistor size).
10. C332 \& C342 470uF/63V are larger than their outline, obscuring their reference designator and are touching component outlines of several nearby components including Q330, Q340 \& JP334.
11. Adding two 1R 1W resistors in line with FIL1 and FIL2 would allow the filament current draw to be measured, similar to R332 \& R342.
12. It's not possible to use both positive \& negative voltage driver boards at the same time so we could save redundant PCB real estate by using a single Vbb supply configurable for either Vbb+ or Vbb-.
13. Without a display connected, the filament bias has no return path. A high value resistor to the opposing rail (e.g. Vcc+ or GND for negative voltage systems and Vbb+ for positive voltage systems) would allow the bias voltage to work with no display connected. e.g. Kenwood VR-615 has a R820 10K from fil bias to GND.
14. Adding two 10R 1W resistors inline with unregulated DC similar to R332 \& R342 would allow the Vcc+/Vcc- current draw to be measured.
15. The Arduino Nano USB cable fouls VR310 \& VR320.
16. The inductor pitch and holes are slightly too small for AL0410. They still fit, just.
17. For negative voltage front panels, the fil resistors are on the Controller PCB. This makes each port somewhat specific to a particular front panel.
18. To get from ~50V unregulated DC to -24V results in high power dissipation on the TIP transistor, from 4W for 36V to 7W for 24V. One idea is to use two stages for the regulation ~50V to 36V and then 36V to 24V using two TIP transistor stages in series. How a reference is set could have a useful side effect - if a positive regulation stage is used and the resulting +24V set as reference, then the intermediate "36V" stage becomes a regulated +12V.
19. Futaba datasheets for a few displays and several service manuals show -28V as typical rather than -24V for Vbb-.
