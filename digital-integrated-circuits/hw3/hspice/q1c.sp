* CMOS Inverter VTC - Design C
* s=1, k=3, Wn=1u, Wp=3u, CL=14.8fF

.option post=2 nomod
.temp 27

VDD vdd 0 DC 1.8
VIN in 0 DC 0

.model NMOD NMOS LEVEL=1 VTO=0.5 GAMMA=0 TOX=4n NSUB=1e17
.model PMOD PMOS LEVEL=1 VTO=-0.5 GAMMA=0 TOX=4n NSUB=1e17

MP_INV out in vdd vdd PMOD W=3u L=0.18u
MN_INV out in 0   0   NMOD W=1u L=0.18u

CLOAD out 0 14.8f

.dc VIN 0 1.8 0.001

.probe dc V(in) V(out)
.print dc V(in) V(out)

.measure dc VOH_C FIND V(out) AT=0
.measure dc VOL_C FIND V(out) AT=1.8
.measure dc VM_C FIND V(in) WHEN V(out)=V(in)

.end