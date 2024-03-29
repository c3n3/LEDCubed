EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:IHE
LIBS:Custom
LIBS:LED Cube-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 24
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR012
U 1 1 5A1B31C4
P 6850 5050
AR Path="/5A1B2FBE/5A1B31C4" Ref="#PWR012"  Part="1" 
AR Path="/5A24A7AE/5A1B31C4" Ref="#PWR016"  Part="1" 
AR Path="/5A24BC1E/5A1B31C4" Ref="#PWR020"  Part="1" 
AR Path="/5A25427B/5A1B31C4" Ref="#PWR024"  Part="1" 
AR Path="/5A254309/5A1B31C4" Ref="#PWR028"  Part="1" 
AR Path="/5A254397/5A1B31C4" Ref="#PWR032"  Part="1" 
AR Path="/5A25862B/5A1B31C4" Ref="#PWR036"  Part="1" 
AR Path="/5A2586B9/5A1B31C4" Ref="#PWR040"  Part="1" 
AR Path="/5A258747/5A1B31C4" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 6850 4800 50  0001 C CNN
F 1 "GND" H 6850 4900 50  0000 C CNN
F 2 "" H 6850 5050 60  0000 C CNN
F 3 "" H 6850 5050 60  0000 C CNN
	1    6850 5050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR013
U 1 1 5A1B31DB
P 6350 3150
AR Path="/5A1B2FBE/5A1B31DB" Ref="#PWR013"  Part="1" 
AR Path="/5A24A7AE/5A1B31DB" Ref="#PWR017"  Part="1" 
AR Path="/5A24BC1E/5A1B31DB" Ref="#PWR021"  Part="1" 
AR Path="/5A25427B/5A1B31DB" Ref="#PWR025"  Part="1" 
AR Path="/5A254309/5A1B31DB" Ref="#PWR029"  Part="1" 
AR Path="/5A254397/5A1B31DB" Ref="#PWR033"  Part="1" 
AR Path="/5A25862B/5A1B31DB" Ref="#PWR037"  Part="1" 
AR Path="/5A2586B9/5A1B31DB" Ref="#PWR041"  Part="1" 
AR Path="/5A258747/5A1B31DB" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 6350 3000 50  0001 C CNN
F 1 "+3.3V" H 6350 3290 50  0000 C CNN
F 2 "" H 6350 3150 60  0000 C CNN
F 3 "" H 6350 3150 60  0000 C CNN
	1    6350 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3900 6850 5050
Wire Wire Line
	6200 4000 6350 4000
Wire Wire Line
	6350 4000 6350 3150
$Comp
L R R1
U 1 1 5A1B3217
P 6600 4200
AR Path="/5A1B2FBE/5A1B3217" Ref="R1"  Part="1" 
AR Path="/5A24A7AE/5A1B3217" Ref="R2"  Part="1" 
AR Path="/5A24BC1E/5A1B3217" Ref="R3"  Part="1" 
AR Path="/5A25427B/5A1B3217" Ref="R4"  Part="1" 
AR Path="/5A254309/5A1B3217" Ref="R5"  Part="1" 
AR Path="/5A254397/5A1B3217" Ref="R6"  Part="1" 
AR Path="/5A25862B/5A1B3217" Ref="R7"  Part="1" 
AR Path="/5A2586B9/5A1B3217" Ref="R8"  Part="1" 
AR Path="/5A258747/5A1B3217" Ref="R9"  Part="1" 
F 0 "R8" V 6680 4200 50  0000 C CNN
F 1 "2K" V 6600 4200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6530 4200 30  0001 C CNN
F 3 "" H 6600 4200 30  0000 C CNN
	1    6600 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	6200 4200 6450 4200
Wire Wire Line
	6750 4200 6850 4200
Connection ~ 6850 4200
Text HLabel 4750 3300 0    60   Input ~ 0
OUT_0
Text HLabel 4750 3400 0    60   Input ~ 0
OUT_1
Text HLabel 4750 3500 0    60   Input ~ 0
OUT_2
Text HLabel 4750 3600 0    60   Input ~ 0
OUT_3
Text HLabel 4750 3700 0    60   Input ~ 0
OUT_4
Text HLabel 4750 3800 0    60   Input ~ 0
OUT_5
Text HLabel 4750 3900 0    60   Input ~ 0
OUT_6
Text HLabel 4750 4000 0    60   Input ~ 0
OUT_7
Text HLabel 4750 4100 0    60   Input ~ 0
OUT_8
Text HLabel 4750 4200 0    60   Input ~ 0
OUT_9
Text HLabel 4800 4300 0    60   Input ~ 0
OUT_10
Text HLabel 4800 4400 0    60   Input ~ 0
OUT_11
Text HLabel 4800 4500 0    60   Input ~ 0
OUT_12
Text HLabel 4800 4600 0    60   Input ~ 0
OUT_13
Text HLabel 4800 4700 0    60   Input ~ 0
OUT_14
Text HLabel 4800 4800 0    60   Input ~ 0
OUT_15
Wire Wire Line
	5000 3300 4750 3300
Wire Wire Line
	5000 3400 4750 3400
Wire Wire Line
	5000 3500 4750 3500
Wire Wire Line
	5000 3600 4750 3600
Wire Wire Line
	5000 3700 4750 3700
Wire Wire Line
	5000 3800 4750 3800
Wire Wire Line
	5000 3900 4750 3900
Wire Wire Line
	5000 4000 4750 4000
Wire Wire Line
	5000 4100 4750 4100
Wire Wire Line
	5000 4200 4750 4200
Wire Wire Line
	5000 4300 4800 4300
Wire Wire Line
	5000 4400 4800 4400
Wire Wire Line
	5000 4500 4800 4500
Wire Wire Line
	5000 4600 4800 4600
Wire Wire Line
	5000 4700 4800 4700
Wire Wire Line
	5000 4800 4800 4800
Text HLabel 7100 3400 2    60   Input ~ 0
SIN
Text HLabel 7100 3500 2    60   Input ~ 0
SCLK
Text HLabel 7100 3300 2    60   Input ~ 0
VPRG
Text HLabel 7100 3600 2    60   Input ~ 0
XLAT
Text HLabel 7100 3700 2    60   Input ~ 0
BLANK
Connection ~ 6350 4000
Wire Wire Line
	6850 3900 6200 3900
Text HLabel 7100 4400 2    60   Input ~ 0
GSCLK
Text HLabel 7100 4500 2    60   Input ~ 0
SOUT
Wire Wire Line
	6200 3300 7100 3300
Wire Wire Line
	6200 3400 7100 3400
Wire Wire Line
	6200 3500 7100 3500
Wire Wire Line
	6200 3600 7100 3600
Wire Wire Line
	6200 3700 7100 3700
Wire Wire Line
	6200 4400 7100 4400
Wire Wire Line
	6200 4500 7100 4500
$Comp
L +3.3V #PWR014
U 1 1 5A1B5138
P 8000 3150
AR Path="/5A1B2FBE/5A1B5138" Ref="#PWR014"  Part="1" 
AR Path="/5A24A7AE/5A1B5138" Ref="#PWR018"  Part="1" 
AR Path="/5A24BC1E/5A1B5138" Ref="#PWR022"  Part="1" 
AR Path="/5A25427B/5A1B5138" Ref="#PWR026"  Part="1" 
AR Path="/5A254309/5A1B5138" Ref="#PWR030"  Part="1" 
AR Path="/5A254397/5A1B5138" Ref="#PWR034"  Part="1" 
AR Path="/5A25862B/5A1B5138" Ref="#PWR038"  Part="1" 
AR Path="/5A2586B9/5A1B5138" Ref="#PWR042"  Part="1" 
AR Path="/5A258747/5A1B5138" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 8000 3000 50  0001 C CNN
F 1 "+3.3V" H 8000 3290 50  0000 C CNN
F 2 "" H 8000 3150 60  0000 C CNN
F 3 "" H 8000 3150 60  0000 C CNN
	1    8000 3150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5A1B5167
P 8000 5050
AR Path="/5A1B2FBE/5A1B5167" Ref="#PWR015"  Part="1" 
AR Path="/5A24A7AE/5A1B5167" Ref="#PWR019"  Part="1" 
AR Path="/5A24BC1E/5A1B5167" Ref="#PWR023"  Part="1" 
AR Path="/5A25427B/5A1B5167" Ref="#PWR027"  Part="1" 
AR Path="/5A254309/5A1B5167" Ref="#PWR031"  Part="1" 
AR Path="/5A254397/5A1B5167" Ref="#PWR035"  Part="1" 
AR Path="/5A25862B/5A1B5167" Ref="#PWR039"  Part="1" 
AR Path="/5A2586B9/5A1B5167" Ref="#PWR043"  Part="1" 
AR Path="/5A258747/5A1B5167" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 8000 4800 50  0001 C CNN
F 1 "GND" H 8000 4900 50  0000 C CNN
F 2 "" H 8000 5050 60  0000 C CNN
F 3 "" H 8000 5050 60  0000 C CNN
	1    8000 5050
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5A1B51CD
P 8000 4150
AR Path="/5A1B2FBE/5A1B51CD" Ref="C1"  Part="1" 
AR Path="/5A24A7AE/5A1B51CD" Ref="C2"  Part="1" 
AR Path="/5A24BC1E/5A1B51CD" Ref="C3"  Part="1" 
AR Path="/5A25427B/5A1B51CD" Ref="C4"  Part="1" 
AR Path="/5A254309/5A1B51CD" Ref="C5"  Part="1" 
AR Path="/5A254397/5A1B51CD" Ref="C6"  Part="1" 
AR Path="/5A25862B/5A1B51CD" Ref="C7"  Part="1" 
AR Path="/5A2586B9/5A1B51CD" Ref="C8"  Part="1" 
AR Path="/5A258747/5A1B51CD" Ref="C9"  Part="1" 
F 0 "C8" H 8025 4250 50  0000 L CNN
F 1 ".1uF" H 8025 4050 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 8038 4000 30  0001 C CNN
F 3 "" H 8000 4150 60  0000 C CNN
	1    8000 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 4000 8000 3150
Wire Wire Line
	8000 4300 8000 5050
Text HLabel 7100 4300 2    60   Input ~ 0
DCPRG
Wire Wire Line
	6200 4300 7100 4300
Text HLabel 7100 4600 2    60   Input ~ 0
XERR
Wire Wire Line
	6200 4600 7100 4600
$Comp
L TLC5940 TLC4
U 1 1 5A6DF48C
P 5600 4000
AR Path="/5A25427B/5A6DF48C" Ref="TLC4"  Part="1" 
AR Path="/5A1B2FBE/5A6DF48C" Ref="TLC1"  Part="1" 
AR Path="/5A24A7AE/5A6DF48C" Ref="TLC2"  Part="1" 
AR Path="/5A24BC1E/5A6DF48C" Ref="TLC3"  Part="1" 
AR Path="/5A254309/5A6DF48C" Ref="TLC5"  Part="1" 
AR Path="/5A254397/5A6DF48C" Ref="TLC6"  Part="1" 
AR Path="/5A25862B/5A6DF48C" Ref="TLC7"  Part="1" 
AR Path="/5A2586B9/5A6DF48C" Ref="TLC8"  Part="1" 
AR Path="/5A258747/5A6DF48C" Ref="TLC9"  Part="1" 
F 0 "TLC8" H 5600 4125 60  0000 C CNN
F 1 "TLC5940" H 5750 3175 60  0000 C CNN
F 2 "Housings_DIP:DIP-28_W7.62mm_Socket" H 5600 4000 60  0001 C CNN
F 3 "" H 5600 4000 60  0000 C CNN
	1    5600 4000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
