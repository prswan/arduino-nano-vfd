# Power Notes



## Vbb

* Universal VFD V1.00: Sony DVP-NS725P + Panasonic DVD-RV32, 2 x UCN5818AF, R1,R2,R3,R4 10R.
* Universal VFD Controller V1.00: Insignia NS-R2001 Transformer, Vbb+ @ 36.1VDC, R332 10R.



### Measurements

* Vbb DC unregulated in: 53.5VDC
* Quiescent: 0.174V drop across R332 (10R) => 0.017A or 17mA. TIP41C warm.
* All Seg On DVD-RV32: 0.195V drop across R332 (10R) => 0.020A or 20mA. TIP41C warm.
* All Pins On DVD-RV32: 0.350V drop across R332 (10R) => 0.035A or 35mA. TIP41C hot.
* Calculated Power TIP41C: (53.5 - 36.1) \* 0.035 = 0.609W
* Calculated Power R332: 0.35 \* 0.035 = 0.012W



### Theoretical Calculations @ 36V

* 1 display @ 35mA max => 8 displays 0.28A max
* Voltage drop over R332 (10R) => 2.8V
* Voltage drop over TIP41C => (53.5 - 36.1 - 2.8) = 14.6V
* Calculated Power TIP41C: 4.08W
* Calculated Power R332: 0.784W
* Conclusion: TIP41C will need a 4W+ heatsink.



### Theoretical Calculations @ 24V

* 1 display @ 35mA max => 8 displays 0.28A max
* Voltage drop over R332 (10R) => 2.8V
* Voltage drop over TIP41C => (53.5 - 24.1 - 2.8) = 26.6V
* Calculated Power TIP41C: 7.4W
* Calculated Power R332: 0.784W
* Conclusion: TIP41C will need a 7W+ heatsink.



## Fil

* Universal VFD V1.00: Sony DVP-NS725P + Panasonic DVD-RV32, 2 x UCN5818AF, R1,R2,R3,R4 10R.
* Universal VFD Controller V1.00: Insignia NS-R2001 Transformer, Fil @ 4.24VAC



### Measurements

* DVP-NS725P: @ VFD Fil 1.84VAC, across 10R 0.920VAC => 0.092A or 92mA
* DVP-NS725P original fil measurement in the player: 2.89VDC
* DVD-RV32: @ VFD Fil 2.63VAC, across 10R 0.127VAC => 0.013A or 13mA
* DVD-RV32 original fil measurement in the player: 3.86VDC
* Substituting FS351 for 10R, across it 1.245VAC (both displays dim) => 0.124A or 124mA



### Theoretical Calculations

* 1 display pair @ 124mA max => 8 display pairs 0.99A max



## XR-1091 +/- 5V

* Universal VFD V1.00: Sony DVP-NS725P + Panasonic DVD-RV32, 2 x UCN5818AF, R1,R2,R3,R4 10R.
* Universal VFD Controller V1.00: Insignia NS-R2001 Transformer, VccAC @ 16.6VAC, VccUNREG @ 22.0VDC



### Measurements

* Voltage drop over R829 (390R) => (22.0 - 5.0) => 17VDC
* Current through R829: => 0.043A or 43mA
* Power dissipation R829: => 0.731W (and its hot)



### Theoretical Calculations

* XR-1091 datasheet, typical supply current: 10mA, max supply current 18mA
* For 17V of drop over R829 and 18mA minimum current: R829 = 944 Ohms \& power 0.306W
* Selecting E12 R829 820R: 17V drop === 0.021A or 21mA and power 0.357W
* Selecting E12 R829 680R: 17V drop === 0.025A or 25mA and power 0.425W



