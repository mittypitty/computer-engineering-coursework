* Q4 - Pass transistor effect on inverter input and VTC

.option post=2 probe nomod
.temp 27

.param VDDVAL=1.8
.param LMIN=45n
.param WN=1u
.param WP=2u

VDD_SUP vdd 0 DC 'VDDVAL'
VSIG a 0 DC 0

* NMOS pass transistor
* HSPICE MOS order: drain gate source bulk model
* Gate is connected to VDD, input is a, degraded output is mid
M_PASS mid vdd a 0 NMOS W=WN L=LMIN

* CMOS inverter stage
M_P out mid vdd vdd PMOS W=WP L=LMIN
M_N out mid 0   0   NMOS W=WN L=LMIN

.model NMOS NMOS LEVEL=1 VTO=0.5 KP=100u LAMBDA=0.02
.model PMOS PMOS LEVEL=1 VTO=-0.5 KP=40u  LAMBDA=0.02

* DC sweep for VTC
.dc VSIG 0 1.8 0.001

.probe dc V(a) V(mid) V(out) I(VDD_SUP)
.print dc V(a) V(mid) V(out) I(VDD_SUP)

.measure dc VMID_HIGH FIND V(mid) AT=1.8
.measure dc VOUT_HIGH FIND V(out) AT=1.8
.measure dc IDD_HIGH FIND I(VDD_SUP) AT=1.8
.measure dc P_STATIC_HIGH PARAM='-VDDVAL*IDD_HIGH'

.end