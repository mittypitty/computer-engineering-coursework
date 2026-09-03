* AOI21 Gate - Transient Verification

.option post=2
.option probe
.temp 25

* Parameters
.param VSUP=1.8
.param LCH=0.18u
.param WN1=2u
.param WN2=1u
.param WP1=6.8u
.param CLOAD=50f

* Supply
VDD_SUP vdd 0 1.8

* Input waveforms (A slowest, C fastest)
VIN_C c 0 PULSE(0 1.8 0 50p 50p 5n 10n)
VIN_B b 0 PULSE(0 1.8 0 50p 50p 10n 20n)
VIN_A a 0 PULSE(0 1.8 0 50p 50p 20n 40n)

* MOS Models
.model NCH nmos level=1 vto=0.4 kp=170u gamma=0.4 phi=0.6
.model PCH pmos level=1 vto=-0.4 kp=50u gamma=0.4 phi=0.6

* Pull-Up Network
MP1 y c p_int vdd PCH W=6.8u L=0.18u
MP2 p_int a vdd vdd PCH W=6.8u L=0.18u
MP3 p_int b vdd vdd PCH W=6.8u L=0.18u

* Pull-Down Network
MN1 y a n_int 0 NCH W=2u L=0.18u
MN2 n_int b 0 0 NCH W=2u L=0.18u
MN3 y c 0 0 NCH W=1u L=0.18u

* Load capacitor
C1 y 0 50f

* Transient simulation
.tran 10p 45n

* Save signals
.probe v(a) v(b) v(c) v(y)

.end
