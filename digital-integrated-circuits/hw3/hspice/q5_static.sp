* Q5 - CMOS Inverter Static Power
.option post=2 nomod
.temp 27

.param VSUP=3.3
.param GIVEN_ILEAK=20n

VSUPPLY supply 0 DC 'VSUP'
VINPUT input 0 DC 3.3

.model NMOS_MODEL NMOS LEVEL=1 VTO=0.5 KP=1.5m LAMBDA=0
.model PMOS_MODEL PMOS LEVEL=1 VTO=-0.6 KP=1m LAMBDA=0

MP_PULLUP output input supply supply PMOS_MODEL W=1u L=1u
MN_PULLDOWN output input 0 0 NMOS_MODEL W=1u L=1u

* A very small DC sweep around Vin=3.3V
* This is used instead of .measure op for compatibility
.dc VINPUT 3.3 3.301 0.001

.probe dc V(input) V(output) I(VSUPPLY)
.print dc V(input) V(output) I(VSUPPLY)

* Raw current of the voltage source is usually negative
.measure dc IDD_RAW FIND I(VSUPPLY) AT=3.3

* Convert source current to positive consumed current
.measure dc IDD_SIM PARAM='-IDD_RAW'

* Static power obtained from LEVEL=1 simulation
.measure dc P_STATIC_SIM PARAM='VSUP*IDD_SIM'

* Static power calculated from the given 20nA leakage current
.measure dc P_STATIC_GIVEN PARAM='VSUP*GIVEN_ILEAK'

.end