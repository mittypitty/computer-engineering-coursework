* inverter DC: current and power sweep
.option post=2 nomod accurate
.temp 25

.param VDDVAL = 1.0

.model nmos nmos level=1 vto=0.5 kp=120u
.model pmos pmos level=1 vto=-0.5 kp=60u

Vvdd vdd 0 DC VDDVAL
Vin  in  0 DC 0

Mpu out in vdd vdd pmos L=45n W=180n
Mpd out in 0   0   nmos L=45n W=90n

*================ SWEEP #0 ================
.dc Vin 0 1.0 1m
.probe dc v(in) v(out) i(Vvdd)
.print dc v(in) v(out) i(Vvdd) par('-i(Vvdd)') par('VDDVAL*(-i(Vvdd))')
.measure dc Idd_peak MAX par('-i(Vvdd)')


*================ SWEEP #1 ================
.alter LOW_VT_0P3
.model nmos nmos level=1 vto=0.3 kp=120u
.model pmos pmos level=1 vto=-0.3 kp=60u

.dc Vin 0 1.0 1m  
.probe dc v(in) v(out) i(Vvdd)
.print dc v(in) v(out) i(Vvdd) par('i(Vvdd)') par('VDDVAL*(-i(Vvdd))')
.measure dc Idd_peak MAX par('-i(Vvdd)')
.end
