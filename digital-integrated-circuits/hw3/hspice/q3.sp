* =========================================================
* Q3 - Transistor-Level CMOS Full Adder
* Static CMOS XOR, NAND+INV for AND, NOR+INV for OR
* =========================================================

.option post=2 nomod
.temp 27

* ---------------------------------------------------------
* Power supply and input patterns
* The eight input states are generated during 40ns
* ---------------------------------------------------------

VDD vdd 0 DC 1

VA   a   0 PULSE(0 1 0 10p 10p 20n 40n)
VB   b   0 PULSE(0 1 0 10p 10p 10n 20n)
VCIN cin 0 PULSE(0 1 0 10p 10p 5n  10n)

* ---------------------------------------------------------
* MOS models exactly according to the question
* ---------------------------------------------------------

.model NMOD NMOS LEVEL=1 VTO=0.5 KP=120u
.model PMOD PMOS LEVEL=1 VTO=-0.5 KP=60u

* =========================================================
* CMOS inverter
* Ports: input output vdd gnd
* =========================================================

.SUBCKT INV input output vdd gnd

MP_INV output input vdd vdd PMOD W=180n L=45n
MN_INV output input gnd gnd NMOD W=90n  L=45n

.ENDS INV

* =========================================================
* Two-input NAND
* PMOS devices are parallel
* NMOS devices are series
* Ports: a b output vdd gnd
* =========================================================

.SUBCKT NAND2 a b output vdd gnd

MP_NAND_A output a vdd vdd PMOD W=180n L=45n
MP_NAND_B output b vdd vdd PMOD W=180n L=45n

MN_NAND_A output a n_nand gnd NMOD W=90n L=45n
MN_NAND_B n_nand b gnd gnd NMOD W=90n L=45n

.ENDS NAND2

* =========================================================
* Two-input NOR
* PMOS devices are series
* NMOS devices are parallel
* Ports: a b output vdd gnd
* =========================================================

.SUBCKT NOR2 a b output vdd gnd

MP_NOR_A output a n_nor vdd PMOD W=180n L=45n
MP_NOR_B n_nor b vdd vdd PMOD W=180n L=45n

MN_NOR_A output a gnd gnd NMOD W=90n L=45n
MN_NOR_B output b gnd gnd NMOD W=90n L=45n

.ENDS NOR2

* =========================================================
* AND gate = NAND followed by inverter
* Ports: a b output vdd gnd
* =========================================================

.SUBCKT AND2 a b output vdd gnd

XNAND_STAGE a b nand_bar vdd gnd NAND2
XAND_INV nand_bar output vdd gnd INV

.ENDS AND2

* =========================================================
* OR gate = NOR followed by inverter
* Ports: a b output vdd gnd
* =========================================================

.SUBCKT OR2 a b output vdd gnd

XNOR_STAGE a b nor_bar vdd gnd NOR2
XOR_INV nor_bar output vdd gnd INV

.ENDS OR2

* =========================================================
* Static complementary CMOS XOR
*
* output = a XOR b
*
* Pull-up conducts for:
* a=0,b=1  or  a=1,b=0
*
* Pull-down conducts for:
* a=0,b=0  or  a=1,b=1
* =========================================================

.SUBCKT XOR2 a b output vdd gnd

* Generate complementary inputs

XINV_A a a_bar vdd gnd INV
XINV_B b b_bar vdd gnd INV

* ---------------------------------------------------------
* Pull-up network
* Branch 1: a=0 and b=1
* PMOS gates: a and b_bar
* ---------------------------------------------------------

MP_XOR_P1 n_pu1 a vdd vdd PMOD W=180n L=45n
MP_XOR_P2 output b_bar n_pu1 vdd PMOD W=180n L=45n

* ---------------------------------------------------------
* Pull-up branch 2: a=1 and b=0
* PMOS gates: a_bar and b
* ---------------------------------------------------------

MP_XOR_P3 n_pu2 a_bar vdd vdd PMOD W=180n L=45n
MP_XOR_P4 output b n_pu2 vdd PMOD W=180n L=45n

* ---------------------------------------------------------
* Pull-down branch 1: a=1 and b=1
* ---------------------------------------------------------

MN_XOR_N1 output a n_pd1 gnd NMOD W=90n L=45n
MN_XOR_N2 n_pd1 b gnd gnd NMOD W=90n L=45n

* ---------------------------------------------------------
* Pull-down branch 2: a=0 and b=0
* ---------------------------------------------------------

MN_XOR_N3 output a_bar n_pd2 gnd NMOD W=90n L=45n
MN_XOR_N4 n_pd2 b_bar gnd gnd NMOD W=90n L=45n

.ENDS XOR2

* =========================================================
* Full-Adder implementation
*
* p    = a XOR b
* g    = a AND b
* s    = p XOR cin
* u    = p AND cin
* cout = g OR u
* =========================================================

XXOR_AB a b p vdd 0 XOR2
XAND_AB a b g vdd 0 AND2

XXOR_SUM p cin s vdd 0 XOR2
XAND_PC  p cin u vdd 0 AND2

XOR_CARRY g u cout vdd 0 OR2

* ---------------------------------------------------------
* Required output loads
* ---------------------------------------------------------

CLOAD_SUM   s    0 1f
CLOAD_CARRY cout 0 1f

* ---------------------------------------------------------
* Transient analysis
* ---------------------------------------------------------

.tran 0.1n 40n

* ---------------------------------------------------------
* Waveform outputs
* ---------------------------------------------------------

.probe tran V(a) V(b) V(cin)
.probe tran V(p) V(g) V(u)
.probe tran V(s) V(cout)
.probe tran I(VDD)

.print tran V(a) V(b) V(cin) V(s) V(cout)

* Optional ASCII plot in LIS

.plot tran V(s) V(cout)

* =========================================================
* Automatic truth-table checking
*
* Input order generated by the given pulse sources:
*
* 2.5ns  : 111
* 7.5ns  : 110
* 12.5ns : 101
* 17.5ns : 100
* 22.5ns : 011
* 27.5ns : 010
* 32.5ns : 001
* 37.5ns : 000
* =========================================================

.measure tran state111_s
+ FIND V(s) AT=2.5n

.measure tran state111_cout
+ FIND V(cout) AT=2.5n

.measure tran state110_s
+ FIND V(s) AT=7.5n

.measure tran state110_cout
+ FIND V(cout) AT=7.5n

.measure tran state101_s
+ FIND V(s) AT=12.5n

.measure tran state101_cout
+ FIND V(cout) AT=12.5n

.measure tran state100_s
+ FIND V(s) AT=17.5n

.measure tran state100_cout
+ FIND V(cout) AT=17.5n

.measure tran state011_s
+ FIND V(s) AT=22.5n

.measure tran state011_cout
+ FIND V(cout) AT=22.5n

.measure tran state010_s
+ FIND V(s) AT=27.5n

.measure tran state010_cout
+ FIND V(cout) AT=27.5n

.measure tran state001_s
+ FIND V(s) AT=32.5n

.measure tran state001_cout
+ FIND V(cout) AT=32.5n

.measure tran state000_s
+ FIND V(s) AT=37.5n

.measure tran state000_cout
+ FIND V(cout) AT=37.5n

* =========================================================
* Propagation delay
*
* At 15ns:
* before transition: a=1,b=0,cin=1 -> cout=1
* after transition : a=1,b=0,cin=0 -> cout=0
*
* cin has its second falling edge at 15ns.
* cout has its first falling edge at this point.
* =========================================================

.measure tran delay_cin_cout_hl
+ TRIG V(cin)  VAL=0.5 FALL=2
+ TARG V(cout) VAL=0.5 FALL=1

* Optional delay from cin to sum at the first falling edge

.measure tran delay_cin_sum_hl
+ TRIG V(cin) VAL=0.5 FALL=1
+ TARG V(s)   VAL=0.5 FALL=1

* =========================================================
* Average current and average power
* =========================================================

.measure tran average_supply_current
+ AVG I(VDD) FROM=0n TO=40n

.measure tran average_power
+ PARAM='-average_supply_current*1'

.end