* 6T SRAM Cell - Write '1' and Read Test

.option post=2
.option probe
.temp 25

.param VSUP=1.8
.param LCH=0.18u

* Transistor sizing
.param WPD=2u
.param WPU=3u
.param WAX=1u
.param CBL=100f

* Supply
VDD_SUP vdd 0 1.8

* Models
.model nmod nmos level=1 vto=0.4 kp=170u gamma=0.4 phi=0.6
.model pmod pmos level=1 vto=-0.4 kp=50u gamma=0.4 phi=0.6

***********************
* Bitlines
***********************
VBL  bl  0 PWL(0n 1.8 12n 1.8 12.1n 1.8 50n 1.8)
VBLB blb 0 PWL(0n 0 12n 0 15n 1.8 50n 1.8)

CBL1 bl 0 100f
CBL2 blb 0 100f

***********************
* Wordline
***********************
VWL wl 0 PWL(0n 0 2n 0 2.1n 1.8 12n 1.8 12.1n 0 25n 0 25.1n 1.8 35n 1.8 35.1n 0 50n 0)

***********************
* 6T SRAM Cell
***********************
* Inverter A
MP1 q  qb vdd vdd pmod W=3u L=0.18u
MN1 q  qb 0   0   nmod W=2u L=0.18u

* Inverter B
MP2 qb q vdd vdd pmod W=3u L=0.18u
MN2 qb q 0   0   nmod W=2u L=0.18u

* Access devices
MA1 q  wl bl  0 nmod W=1u L=0.18u
MA2 qb wl blb 0 nmod W=1u L=0.18u

***********************
* Initial condition
***********************
.ic v(q)=0 v(qb)=1.8

***********************
* Transient analysis
***********************
.tran 5p 50n UIC

.probe v(wl) v(bl) v(blb) v(q) v(qb)

.end
