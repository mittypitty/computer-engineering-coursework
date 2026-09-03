* Q5 - CMOS Inverter VTC

.option post=2 nomod
.temp 27

.param VSUP=3.3
.param WN=1u
.param WP=1u
.param LN=1u
.param LP=1u

VSUPPLY supply 0 DC 'VSUP'
VINPUT input 0 DC 0

* Given transistor characteristics
* Since W/L=1, KP is equal to the specified beta value
.model NMOS_MODEL NMOS LEVEL=1 VTO=0.5 KP=1.5m LAMBDA=0
.model PMOS_MODEL PMOS LEVEL=1 VTO=-0.6 KP=1m LAMBDA=0

* CMOS inverter
MP_PULLUP output input supply supply PMOS_MODEL W=WP L=LP
MN_PULLDOWN output input 0 0 NMOS_MODEL W=WN L=LN

* The capacitor does not change the DC transfer characteristic
C_OUTPUT output 0 10f

* Sweep input from 0V to 3.3V
.dc VINPUT 0 3.3 0.001

.probe dc V(input) V(output) I(VSUPPLY)
.print dc V(input) V(output) I(VSUPPLY)

* DC measurements
.measure dc VOH_SIM FIND V(output) AT=0
.measure dc VOL_SIM FIND V(output) AT=3.3
.measure dc VM_SIM FIND V(input)
+ WHEN V(output)=V(input) CROSS=1

.end