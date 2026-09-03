* CMOS Inverter Leakage - Design C
* Change VINLEVEL to 0 or 1.8

.option post=2 nomod
.temp 27

.param VINLEVEL=1.8

VDD vdd 0 DC 1.8
VIN in 0 DC 'VINLEVEL'

.model NMOD NMOS LEVEL=1 VTO=0.5 GAMMA=0 TOX=4n NSUB=1e17 JS=100
.model PMOD PMOS LEVEL=1 VTO=-0.5 GAMMA=0 TOX=4n NSUB=1e17 JS=100

MP_INV out in vdd vdd PMOD W=3u L=0.18u
+ AD=0.54p AS=0.54p PD=6.36u PS=6.36u

MN_INV out in 0 0 NMOD W=1u L=0.18u
+ AD=0.18p AS=0.18p PD=2.36u PS=2.36u

.op

.print op V(in) V(out) I(VDD)

.end