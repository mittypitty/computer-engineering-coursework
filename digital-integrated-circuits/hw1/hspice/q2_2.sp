* CMOS NAND2 Transient Simulation (Final Rock-Solid Version)

.option post=2 nomod
.temp 25

* ---- Parameters ----
.param VSUP=1.8
.param LCH=0.18u
.param WN=1u
.param WP=1.7u

* ---- Models ----
.model nmod nmos level=1 vto=0.4 kp=170u gamma=0.4 phi=0.6
.model pmod pmos level=1 vto=-0.4 kp=50u gamma=0.4 phi=0.6

* ---- Supply ----
* استفاده از عدد مستقیم در اینجا و پالس‌ها برای امنیت بالاتر
VDD_SUP vdd 0 DC 1.8

* ---- Input pulses ----
* برداشتن {} از دور مقادیر ولتاژ
VA a 0 PULSE(0 1.8 0 50p 50p 5n 10n)
VB b 0 PULSE(0 1.8 0 50p 50p 10n 20n)

* ---- Pull-up network (PMOS in parallel) ----
MP1 out a vdd vdd pmod W=1.7u L=0.18u
MP2 out b vdd vdd pmod W=1.7u L=0.18u

* ---- Pull-down network (NMOS in series) ----
MN1 out a mid 0 nmod W=1u L=0.18u
MN2 mid b 0 0 nmod W=1u L=0.18u

* ---- Load capacitor ----
CL out 0 50f

* ---- Transient Analysis ----
.tran 10p 30n

* ---- Save/probe waveforms ----
.probe tran v(a) v(b) v(out) i(VDD_SUP)

.end
