* NAND2 DC Analysis - VTC

.option post
.temp 25

* MOS models
.model nmod nmos level=1 vto=0.4 kp=170u gamma=0.4 phi=0.6
.model pmod pmos level=1 vto=-0.4 kp=50u gamma=0.4 phi=0.6

* Supply
VDD_SUP vdd 0 1.8

* Inputs
VA a 0 0
VB b 0 1.8

* NAND structure
MPA out a vdd vdd pmod W=1.7u L=0.18u
MPB out b vdd vdd pmod W=1.7u L=0.18u

MNA out a n1 0 nmod W=1u L=0.18u
MNB n1 b 0 0 nmod W=1u L=0.18u

* DC sweep
.dc VA 0 1.8 0.01

.probe dc v(a) v(out) i(VDD_SUP)

.end
