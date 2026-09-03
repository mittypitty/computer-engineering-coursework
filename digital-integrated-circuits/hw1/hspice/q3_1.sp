* AOI21 Gate - DC Transfer Analysis

.option post=2
.temp 25

* Power supply
VDD_SUP vdd 0 DC 1.8

* Inputs
VA a 0 DC 0
VB b 0 DC 0
VC c 0 DC 0

* MOS models
.model nmos_mod nmos level=1 vto=0.4 kp=170u gamma=0.4 phi=0.6
.model pmos_mod pmos level=1 vto=-0.4 kp=50u gamma=0.4 phi=0.6

* -------- Pull-Up Network --------
MP1 y c pnode vdd pmos_mod W=6.8u L=0.18u
MP2 pnode a vdd vdd pmos_mod W=6.8u L=0.18u
MP3 pnode b vdd vdd pmos_mod W=6.8u L=0.18u

* -------- Pull-Down Network --------
MN1 y a nnode 0 nmos_mod W=2u L=0.18u
MN2 nnode b 0 0 nmos_mod W=2u L=0.18u
MN3 y c 0 0 nmos_mod W=1u L=0.18u

* DC sweep (transfer characteristic)
.dc VC 0 1.8 0.01

* Save signals
.probe dc v(c) v(y) i(VDD_SUP)

.end
