* Q5 - Three CMOS inverters with different PMOS/NMOS width ratios

.option post=2 probe nomod
.temp 27

.param VDDVAL=1.8
.param LCH=45n
.param WNOM=1u

VDD vdd 0 DC 'VDDVAL'
VIN vin 0 DC 0

* Case 1: balanced inverter, Wp = 2.5 Wn
MP1 out_bal vin vdd vdd PMOS W=2.5u L=LCH
MN1 out_bal vin 0   0   NMOS W=1u   L=LCH

* Case 2: strong pull-up, Wp = 8 Wn
MP2 out_high vin vdd vdd PMOS W=8u L=LCH
MN2 out_high vin 0   0   NMOS W=1u L=LCH

* Case 3: weak pull-up, Wp = 0.5 Wn
MP3 out_low vin vdd vdd PMOS W=0.5u L=LCH
MN3 out_low vin 0   0   NMOS W=1u   L=LCH

.model NMOS NMOS LEVEL=1 VTO=0.5 KP=100u LAMBDA=0.02
.model PMOS PMOS LEVEL=1 VTO=-0.5 KP=40u  LAMBDA=0.02

* DC sweep for VTC
.dc VIN 0 1.8 0.001

.probe dc V(vin) V(out_bal) V(out_high) V(out_low)
.print dc V(vin) V(out_bal) V(out_high) V(out_low)

.measure dc VM_BAL  FIND V(vin) WHEN V(out_bal)=V(vin)
.measure dc VM_HIGH FIND V(vin) WHEN V(out_high)=V(vin)
.measure dc VM_LOW  FIND V(vin) WHEN V(out_low)=V(vin)

.end