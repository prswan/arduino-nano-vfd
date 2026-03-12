# Power Notes



## Setup

* Universal VFD V1.00: Sony DVP-NS725P + Panasonic DVD-RV32, 2 x UCN5818AF, R1,R2,R3,R4 10R. 
* Universal VFD Controller V1.00: Insignia NS-R2001 Transformer, Vbb+ @ 36.1VDC, R332 10R.



### Measurements

* Vbb DC unregulated in: 53.5VDC
* Quiescent: 0.174V drop across R332 (10R) => 0.017A or 17mA. TIP41C warm.
* All Seg On DVD-RV32: 0.195V drop across R332 (10R) => 0.020A or 20mA. TIP41C warm.
* All Pins On DVD-RV32: 0.350V drop across R332 (10R) => 0.035A or 35mA. TIP41C hot.
* Calculated Power TIP41C: (53.5 - 36.1) \* 0.035 = 0.609W
* Calculated Power R332: 0.35 \* 0.035 = 0.012W





