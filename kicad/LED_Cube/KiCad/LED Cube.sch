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
$Descr B 17000 11000
encoding utf-8
Sheet 1 24
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 12675 10225 0    60   ~ 0
E-Club LED Cube
Text Notes 13450 10375 0    60   ~ 0
11/4/17
$Comp
L +3.3V #PWR01
U 1 1 59FDD792
P 1900 1300
F 0 "#PWR01" H 1900 1150 50  0001 C CNN
F 1 "+3.3V" H 1900 1440 50  0000 C CNN
F 2 "" H 1900 1300 50  0000 C CNN
F 3 "" H 1900 1300 50  0000 C CNN
	1    1900 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 59FDD7BD
P 1900 2800
F 0 "#PWR02" H 1900 2550 50  0001 C CNN
F 1 "GND" H 1900 2650 50  0000 C CNN
F 2 "" H 1900 2800 50  0000 C CNN
F 3 "" H 1900 2800 50  0000 C CNN
	1    1900 2800
	1    0    0    -1  
$EndComp
$Sheet
S 3350 650  850  1650
U 5A1B2FBE
F0 "TLC_0" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 4200 700 60 
F3 "OUT_1" I R 4200 800 60 
F4 "OUT_2" I R 4200 900 60 
F5 "OUT_3" I R 4200 1000 60 
F6 "OUT_4" I R 4200 1100 60 
F7 "OUT_5" I R 4200 1200 60 
F8 "OUT_6" I R 4200 1300 60 
F9 "OUT_7" I R 4200 1400 60 
F10 "OUT_8" I R 4200 1500 60 
F11 "OUT_9" I R 4200 1600 60 
F12 "OUT_10" I R 4200 1700 60 
F13 "OUT_11" I R 4200 1800 60 
F14 "OUT_12" I R 4200 1900 60 
F15 "OUT_13" I R 4200 2000 60 
F16 "OUT_14" I R 4200 2100 60 
F17 "OUT_15" I R 4200 2200 60 
F18 "SIN" I L 3350 800 60 
F19 "SCLK" I L 3350 900 60 
F20 "VPRG" I L 3350 1100 60 
F21 "XLAT" I L 3350 1200 60 
F22 "BLANK" I L 3350 1300 60 
F23 "GSCLK" I L 3350 1500 60 
F24 "SOUT" I L 3350 2100 60 
F25 "DCPRG" I L 3350 1400 60 
F26 "XERR" I L 3350 1600 60 
$EndSheet
Text Label 4350 750  0    60   ~ 0
P_00_00
Text Label 4350 850  0    60   ~ 0
P_01_00
Text Label 4350 950  0    60   ~ 0
P_02_00
Text Label 4350 1050 0    60   ~ 0
P_03_00
Text Label 4350 1150 0    60   ~ 0
P_04_00
Text Label 4350 1250 0    60   ~ 0
P_05_00
Text Label 4350 1350 0    60   ~ 0
P_06_00
Text Label 4350 1450 0    60   ~ 0
P_07_00
Text Label 4350 1550 0    60   ~ 0
P_08_00
Text Label 4350 1650 0    60   ~ 0
P_09_00
Text Label 4350 1750 0    60   ~ 0
P_10_00
Text Label 4350 1850 0    60   ~ 0
P_11_00
Text Label 4350 1950 0    60   ~ 0
P_00_01
Text Label 4350 2050 0    60   ~ 0
P_01_01
Text Label 4350 2150 0    60   ~ 0
P_02_01
Text Label 4350 2250 0    60   ~ 0
P_03_01
$Sheet
S 3350 2550 850  1650
U 5A24A7AE
F0 "TLC_1" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 4200 2600 60 
F3 "OUT_1" I R 4200 2700 60 
F4 "OUT_2" I R 4200 2800 60 
F5 "OUT_3" I R 4200 2900 60 
F6 "OUT_4" I R 4200 3000 60 
F7 "OUT_5" I R 4200 3100 60 
F8 "OUT_6" I R 4200 3200 60 
F9 "OUT_7" I R 4200 3300 60 
F10 "OUT_8" I R 4200 3400 60 
F11 "OUT_9" I R 4200 3500 60 
F12 "OUT_10" I R 4200 3600 60 
F13 "OUT_11" I R 4200 3700 60 
F14 "OUT_12" I R 4200 3800 60 
F15 "OUT_13" I R 4200 3900 60 
F16 "OUT_14" I R 4200 4000 60 
F17 "OUT_15" I R 4200 4100 60 
F18 "SIN" I L 3350 2700 60 
F19 "SCLK" I L 3350 2800 60 
F20 "VPRG" I L 3350 3000 60 
F21 "XLAT" I L 3350 3100 60 
F22 "BLANK" I L 3350 3200 60 
F23 "GSCLK" I L 3350 3400 60 
F24 "SOUT" I L 3350 4000 60 
F25 "DCPRG" I L 3350 3300 60 
F26 "XERR" I L 3350 3500 60 
$EndSheet
Text Label 4350 2650 0    60   ~ 0
P_04_01
Text Label 4350 2750 0    60   ~ 0
P_05_01
Text Label 4350 2850 0    60   ~ 0
P_06_01
Text Label 4350 2950 0    60   ~ 0
P_07_01
Text Label 4350 3050 0    60   ~ 0
P_08_01
Text Label 4350 3150 0    60   ~ 0
P_09_01
Text Label 4350 3250 0    60   ~ 0
P_10_01
Text Label 4350 3350 0    60   ~ 0
P_11_01
Text Label 4350 3450 0    60   ~ 0
P_00_02
Text Label 4350 3550 0    60   ~ 0
P_01_02
Text Label 4350 3650 0    60   ~ 0
P_02_02
Text Label 4350 3750 0    60   ~ 0
P_03_02
Text Label 4350 3850 0    60   ~ 0
P_04_02
Text Label 4350 3950 0    60   ~ 0
P_05_02
Text Label 4350 4050 0    60   ~ 0
P_06_02
Text Label 4350 4150 0    60   ~ 0
P_07_02
$Sheet
S 3350 4450 850  1650
U 5A24BC1E
F0 "TLC_2" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 4200 4500 60 
F3 "OUT_1" I R 4200 4600 60 
F4 "OUT_2" I R 4200 4700 60 
F5 "OUT_3" I R 4200 4800 60 
F6 "OUT_4" I R 4200 4900 60 
F7 "OUT_5" I R 4200 5000 60 
F8 "OUT_6" I R 4200 5100 60 
F9 "OUT_7" I R 4200 5200 60 
F10 "OUT_8" I R 4200 5300 60 
F11 "OUT_9" I R 4200 5400 60 
F12 "OUT_10" I R 4200 5500 60 
F13 "OUT_11" I R 4200 5600 60 
F14 "OUT_12" I R 4200 5700 60 
F15 "OUT_13" I R 4200 5800 60 
F16 "OUT_14" I R 4200 5900 60 
F17 "OUT_15" I R 4200 6000 60 
F18 "SIN" I L 3350 4600 60 
F19 "SCLK" I L 3350 4700 60 
F20 "VPRG" I L 3350 4900 60 
F21 "XLAT" I L 3350 5000 60 
F22 "BLANK" I L 3350 5100 60 
F23 "GSCLK" I L 3350 5300 60 
F24 "SOUT" I L 3350 5900 60 
F25 "DCPRG" I L 3350 5200 60 
F26 "XERR" I L 3350 5400 60 
$EndSheet
Text Label 4350 4550 0    60   ~ 0
P_08_02
Text Label 4350 4650 0    60   ~ 0
P_09_02
Text Label 4350 4750 0    60   ~ 0
P_10_02
Text Label 4350 4850 0    60   ~ 0
P_11_02
Text Label 4350 4950 0    60   ~ 0
P_00_03
Text Label 4350 5050 0    60   ~ 0
P_01_03
Text Label 4350 5150 0    60   ~ 0
P_02_03
Text Label 4350 5250 0    60   ~ 0
P_03_03
Text Label 4350 5350 0    60   ~ 0
P_04_03
Text Label 4350 5450 0    60   ~ 0
P_05_03
Text Label 4350 5550 0    60   ~ 0
P_06_03
Text Label 4350 5650 0    60   ~ 0
P_07_03
Text Label 4350 5750 0    60   ~ 0
P_08_03
Text Label 4350 5850 0    60   ~ 0
P_09_03
Text Label 4350 5950 0    60   ~ 0
P_10_03
Text Label 4350 6050 0    60   ~ 0
P_11_03
$Sheet
S 5650 650  850  1650
U 5A25427B
F0 "TLC_3" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 6500 700 60 
F3 "OUT_1" I R 6500 800 60 
F4 "OUT_2" I R 6500 900 60 
F5 "OUT_3" I R 6500 1000 60 
F6 "OUT_4" I R 6500 1100 60 
F7 "OUT_5" I R 6500 1200 60 
F8 "OUT_6" I R 6500 1300 60 
F9 "OUT_7" I R 6500 1400 60 
F10 "OUT_8" I R 6500 1500 60 
F11 "OUT_9" I R 6500 1600 60 
F12 "OUT_10" I R 6500 1700 60 
F13 "OUT_11" I R 6500 1800 60 
F14 "OUT_12" I R 6500 1900 60 
F15 "OUT_13" I R 6500 2000 60 
F16 "OUT_14" I R 6500 2100 60 
F17 "OUT_15" I R 6500 2200 60 
F18 "SIN" I L 5650 800 60 
F19 "SCLK" I L 5650 900 60 
F20 "VPRG" I L 5650 1100 60 
F21 "XLAT" I L 5650 1200 60 
F22 "BLANK" I L 5650 1300 60 
F23 "GSCLK" I L 5650 1500 60 
F24 "SOUT" I L 5650 2100 60 
F25 "DCPRG" I L 5650 1400 60 
F26 "XERR" I L 5650 1600 60 
$EndSheet
$Sheet
S 5650 2550 850  1650
U 5A254309
F0 "TLC_4" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 6500 2600 60 
F3 "OUT_1" I R 6500 2700 60 
F4 "OUT_2" I R 6500 2800 60 
F5 "OUT_3" I R 6500 2900 60 
F6 "OUT_4" I R 6500 3000 60 
F7 "OUT_5" I R 6500 3100 60 
F8 "OUT_6" I R 6500 3200 60 
F9 "OUT_7" I R 6500 3300 60 
F10 "OUT_8" I R 6500 3400 60 
F11 "OUT_9" I R 6500 3500 60 
F12 "OUT_10" I R 6500 3600 60 
F13 "OUT_11" I R 6500 3700 60 
F14 "OUT_12" I R 6500 3800 60 
F15 "OUT_13" I R 6500 3900 60 
F16 "OUT_14" I R 6500 4000 60 
F17 "OUT_15" I R 6500 4100 60 
F18 "SIN" I L 5650 2700 60 
F19 "SCLK" I L 5650 2800 60 
F20 "VPRG" I L 5650 3000 60 
F21 "XLAT" I L 5650 3100 60 
F22 "BLANK" I L 5650 3200 60 
F23 "GSCLK" I L 5650 3400 60 
F24 "SOUT" I L 5650 4000 60 
F25 "DCPRG" I L 5650 3300 60 
F26 "XERR" I L 5650 3500 60 
$EndSheet
$Sheet
S 5650 4450 850  1650
U 5A254397
F0 "TLC_5" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 6500 4500 60 
F3 "OUT_1" I R 6500 4600 60 
F4 "OUT_2" I R 6500 4700 60 
F5 "OUT_3" I R 6500 4800 60 
F6 "OUT_4" I R 6500 4900 60 
F7 "OUT_5" I R 6500 5000 60 
F8 "OUT_6" I R 6500 5100 60 
F9 "OUT_7" I R 6500 5200 60 
F10 "OUT_8" I R 6500 5300 60 
F11 "OUT_9" I R 6500 5400 60 
F12 "OUT_10" I R 6500 5500 60 
F13 "OUT_11" I R 6500 5600 60 
F14 "OUT_12" I R 6500 5700 60 
F15 "OUT_13" I R 6500 5800 60 
F16 "OUT_14" I R 6500 5900 60 
F17 "OUT_15" I R 6500 6000 60 
F18 "SIN" I L 5650 4600 60 
F19 "SCLK" I L 5650 4700 60 
F20 "VPRG" I L 5650 4900 60 
F21 "XLAT" I L 5650 5000 60 
F22 "BLANK" I L 5650 5100 60 
F23 "GSCLK" I L 5650 5300 60 
F24 "SOUT" I L 5650 5900 60 
F25 "DCPRG" I L 5650 5200 60 
F26 "XERR" I L 5650 5400 60 
$EndSheet
$Sheet
S 7950 650  850  1650
U 5A25862B
F0 "TLC_6" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 8800 700 60 
F3 "OUT_1" I R 8800 800 60 
F4 "OUT_2" I R 8800 900 60 
F5 "OUT_3" I R 8800 1000 60 
F6 "OUT_4" I R 8800 1100 60 
F7 "OUT_5" I R 8800 1200 60 
F8 "OUT_6" I R 8800 1300 60 
F9 "OUT_7" I R 8800 1400 60 
F10 "OUT_8" I R 8800 1500 60 
F11 "OUT_9" I R 8800 1600 60 
F12 "OUT_10" I R 8800 1700 60 
F13 "OUT_11" I R 8800 1800 60 
F14 "OUT_12" I R 8800 1900 60 
F15 "OUT_13" I R 8800 2000 60 
F16 "OUT_14" I R 8800 2100 60 
F17 "OUT_15" I R 8800 2200 60 
F18 "SIN" I L 7950 800 60 
F19 "SCLK" I L 7950 900 60 
F20 "VPRG" I L 7950 1100 60 
F21 "XLAT" I L 7950 1200 60 
F22 "BLANK" I L 7950 1300 60 
F23 "GSCLK" I L 7950 1500 60 
F24 "SOUT" I L 7950 2100 60 
F25 "DCPRG" I L 7950 1400 60 
F26 "XERR" I L 7950 1600 60 
$EndSheet
$Sheet
S 7950 2550 850  1650
U 5A2586B9
F0 "TLC_7" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 8800 2600 60 
F3 "OUT_1" I R 8800 2700 60 
F4 "OUT_2" I R 8800 2800 60 
F5 "OUT_3" I R 8800 2900 60 
F6 "OUT_4" I R 8800 3000 60 
F7 "OUT_5" I R 8800 3100 60 
F8 "OUT_6" I R 8800 3200 60 
F9 "OUT_7" I R 8800 3300 60 
F10 "OUT_8" I R 8800 3400 60 
F11 "OUT_9" I R 8800 3500 60 
F12 "OUT_10" I R 8800 3600 60 
F13 "OUT_11" I R 8800 3700 60 
F14 "OUT_12" I R 8800 3800 60 
F15 "OUT_13" I R 8800 3900 60 
F16 "OUT_14" I R 8800 4000 60 
F17 "OUT_15" I R 8800 4100 60 
F18 "SIN" I L 7950 2700 60 
F19 "SCLK" I L 7950 2800 60 
F20 "VPRG" I L 7950 3000 60 
F21 "XLAT" I L 7950 3100 60 
F22 "BLANK" I L 7950 3200 60 
F23 "GSCLK" I L 7950 3400 60 
F24 "SOUT" I L 7950 4000 60 
F25 "DCPRG" I L 7950 3300 60 
F26 "XERR" I L 7950 3500 60 
$EndSheet
$Sheet
S 7950 4450 850  1650
U 5A258747
F0 "TLC_8" 60
F1 "tlc_circuit.sch" 60
F2 "OUT_0" I R 8800 4500 60 
F3 "OUT_1" I R 8800 4600 60 
F4 "OUT_2" I R 8800 4700 60 
F5 "OUT_3" I R 8800 4800 60 
F6 "OUT_4" I R 8800 4900 60 
F7 "OUT_5" I R 8800 5000 60 
F8 "OUT_6" I R 8800 5100 60 
F9 "OUT_7" I R 8800 5200 60 
F10 "OUT_8" I R 8800 5300 60 
F11 "OUT_9" I R 8800 5400 60 
F12 "OUT_10" I R 8800 5500 60 
F13 "OUT_11" I R 8800 5600 60 
F14 "OUT_12" I R 8800 5700 60 
F15 "OUT_13" I R 8800 5800 60 
F16 "OUT_14" I R 8800 5900 60 
F17 "OUT_15" I R 8800 6000 60 
F18 "SIN" I L 7950 4600 60 
F19 "SCLK" I L 7950 4700 60 
F20 "VPRG" I L 7950 4900 60 
F21 "XLAT" I L 7950 5000 60 
F22 "BLANK" I L 7950 5100 60 
F23 "GSCLK" I L 7950 5300 60 
F24 "SOUT" I L 7950 5900 60 
F25 "DCPRG" I L 7950 5200 60 
F26 "XERR" I L 7950 5400 60 
$EndSheet
Text Label 6650 750  0    60   ~ 0
P_00_04
Text Label 6650 850  0    60   ~ 0
P_01_04
Text Label 6650 950  0    60   ~ 0
P_02_04
Text Label 6650 1050 0    60   ~ 0
P_03_04
Text Label 6650 1150 0    60   ~ 0
P_04_04
Text Label 6650 1250 0    60   ~ 0
P_05_04
Text Label 6650 1350 0    60   ~ 0
P_06_04
Text Label 6650 1450 0    60   ~ 0
P_07_04
Text Label 6650 1550 0    60   ~ 0
P_08_04
Text Label 6650 1650 0    60   ~ 0
P_09_04
Text Label 6650 1750 0    60   ~ 0
P_10_04
Text Label 6650 1850 0    60   ~ 0
P_11_04
Text Label 6650 1950 0    60   ~ 0
P_00_05
Text Label 6650 2050 0    60   ~ 0
P_01_05
Text Label 6650 2150 0    60   ~ 0
P_02_05
Text Label 6650 2250 0    60   ~ 0
P_03_05
Text Label 6650 2650 0    60   ~ 0
P_04_05
Text Label 6650 2750 0    60   ~ 0
P_05_05
Text Label 6650 2850 0    60   ~ 0
P_06_05
Text Label 6650 2950 0    60   ~ 0
P_07_05
Text Label 6650 3050 0    60   ~ 0
P_08_05
Text Label 6650 3150 0    60   ~ 0
P_09_05
Text Label 6650 3250 0    60   ~ 0
P_10_05
Text Label 6650 3350 0    60   ~ 0
P_11_05
Text Label 6650 3450 0    60   ~ 0
P_00_06
Text Label 6650 3550 0    60   ~ 0
P_01_06
Text Label 6650 3650 0    60   ~ 0
P_02_06
Text Label 6650 3750 0    60   ~ 0
P_03_06
Text Label 6650 3850 0    60   ~ 0
P_04_06
Text Label 6650 3950 0    60   ~ 0
P_05_06
Text Label 6650 4050 0    60   ~ 0
P_06_06
Text Label 6650 4150 0    60   ~ 0
P_07_06
Text Label 6650 4550 0    60   ~ 0
P_08_06
Text Label 6650 4650 0    60   ~ 0
P_09_06
Text Label 6650 4750 0    60   ~ 0
P_10_06
Text Label 6650 4850 0    60   ~ 0
P_11_06
Text Label 6650 4950 0    60   ~ 0
P_00_07
Text Label 6650 5050 0    60   ~ 0
P_01_07
Text Label 6650 5150 0    60   ~ 0
P_02_07
Text Label 6650 5250 0    60   ~ 0
P_03_07
Text Label 6650 5350 0    60   ~ 0
P_04_07
Text Label 6650 5450 0    60   ~ 0
P_05_07
Text Label 6650 5550 0    60   ~ 0
P_06_07
Text Label 6650 5650 0    60   ~ 0
P_07_07
Text Label 6650 5750 0    60   ~ 0
P_08_07
Text Label 6650 5850 0    60   ~ 0
P_09_07
Text Label 6650 5950 0    60   ~ 0
P_10_07
Text Label 6650 6050 0    60   ~ 0
P_11_07
Text Label 8950 750  0    60   ~ 0
P_00_08
Text Label 8950 850  0    60   ~ 0
P_01_08
Text Label 8950 950  0    60   ~ 0
P_02_08
Text Label 8950 1050 0    60   ~ 0
P_03_08
Text Label 8950 1150 0    60   ~ 0
P_04_08
Text Label 8950 1250 0    60   ~ 0
P_05_08
Text Label 8950 1350 0    60   ~ 0
P_06_08
Text Label 8950 1450 0    60   ~ 0
P_07_08
Text Label 8950 1550 0    60   ~ 0
P_08_08
Text Label 8950 1650 0    60   ~ 0
P_09_08
Text Label 8950 1750 0    60   ~ 0
P_10_08
Text Label 8950 1850 0    60   ~ 0
P_11_08
Text Label 8950 1950 0    60   ~ 0
P_00_09
Text Label 8950 2050 0    60   ~ 0
P_01_09
Text Label 8950 2150 0    60   ~ 0
P_02_09
Text Label 8950 2250 0    60   ~ 0
P_03_09
Text Label 8950 2650 0    60   ~ 0
P_04_09
Text Label 8950 2750 0    60   ~ 0
P_05_09
Text Label 8950 2850 0    60   ~ 0
P_06_09
Text Label 8950 2950 0    60   ~ 0
P_07_09
Text Label 8950 3050 0    60   ~ 0
P_08_09
Text Label 8950 3150 0    60   ~ 0
P_09_09
Text Label 8950 3250 0    60   ~ 0
P_10_09
Text Label 8950 3350 0    60   ~ 0
P_11_09
Text Label 8950 3450 0    60   ~ 0
P_00_10
Text Label 8950 3550 0    60   ~ 0
P_01_10
Text Label 8950 3650 0    60   ~ 0
P_02_10
Text Label 8950 3750 0    60   ~ 0
P_03_10
Text Label 8950 3850 0    60   ~ 0
P_04_10
Text Label 8950 3950 0    60   ~ 0
P_05_10
Text Label 8950 4050 0    60   ~ 0
P_06_10
Text Label 8950 4150 0    60   ~ 0
P_07_10
Text Label 8950 4550 0    60   ~ 0
P_08_10
Text Label 8950 4650 0    60   ~ 0
P_09_10
Text Label 8950 4750 0    60   ~ 0
P_10_10
Text Label 8950 4850 0    60   ~ 0
P_11_10
Text Label 8950 4950 0    60   ~ 0
P_00_11
Text Label 8950 5050 0    60   ~ 0
P_01_11
Text Label 8950 5150 0    60   ~ 0
P_02_11
Text Label 8950 5250 0    60   ~ 0
P_03_11
Text Label 8950 5350 0    60   ~ 0
P_04_11
Text Label 8950 5450 0    60   ~ 0
P_05_11
Text Label 8950 5550 0    60   ~ 0
P_06_11
Text Label 8950 5650 0    60   ~ 0
P_07_11
Text Label 8950 5750 0    60   ~ 0
P_08_11
Text Label 8950 5850 0    60   ~ 0
P_09_11
Text Label 8950 5950 0    60   ~ 0
P_10_11
Text Label 8950 6050 0    60   ~ 0
P_11_11
Text Label 1300 1500 0    60   ~ 0
SIN
Text Label 1300 1700 0    60   ~ 0
XLAT
Text Label 1300 1800 0    60   ~ 0
GSCLK
Text Label 1300 1900 0    60   ~ 0
BLANK
Text Label 1300 2000 0    60   ~ 0
VPRG
Text Label 1300 2100 0    60   ~ 0
DCPRG
$Comp
L CONN_01X10 P2
U 1 1 5A57AC95
P 950 7200
F 0 "P2" H 950 7750 50  0000 C CNN
F 1 "CONN_01X10" V 1050 7200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 950 7200 60  0001 C CNN
F 3 "" H 950 7200 60  0000 C CNN
	1    950  7200
	-1   0    0    1   
$EndComp
Text Label 1300 2200 0    60   ~ 0
SOUT
Text Label 7800 5950 2    60   ~ 0
SOUT
Text Label 5600 6750 0    60   ~ 0
L_00_R
Text Label 5600 6850 0    60   ~ 0
L_00_G
Text Label 5600 6950 0    60   ~ 0
L_00_B
$Sheet
S 3750 6600 1700 3700
U 5A576665
F0 "MOSFET_TREE" 60
F1 "child_sheets/layer_select.sch" 60
F2 "Q_0" I L 3750 6700 60 
F3 "Q_1" I L 3750 6800 60 
F4 "Q_2" I L 3750 6900 60 
F5 "Q_3" I L 3750 7000 60 
F6 "L_0" I L 3750 7150 60 
F7 "L_1" I L 3750 7250 60 
F8 "L_2" I L 3750 7350 60 
F9 "C_R" I L 3750 7500 60 
F10 "C_G" I L 3750 7600 60 
F11 "C_B" I L 3750 7700 60 
F12 "L_00_R" I R 5450 6700 60 
F13 "L_00_G" I R 5450 6800 60 
F14 "L_00_B" I R 5450 6900 60 
F15 "L_01_R" I R 5450 7000 60 
F16 "L_01_G" I R 5450 7100 60 
F17 "L_01_B" I R 5450 7200 60 
F18 "L_02_R" I R 5450 7300 60 
F19 "L_02_G" I R 5450 7400 60 
F20 "L_02_B" I R 5450 7500 60 
F21 "L_03_R" I R 5450 7600 60 
F22 "L_03_G" I R 5450 7700 60 
F23 "L_03_B" I R 5450 7800 60 
F24 "L_04_R" I R 5450 7900 60 
F25 "L_04_G" I R 5450 8000 60 
F26 "L_04_B" I R 5450 8100 60 
F27 "L_05_R" I R 5450 8200 60 
F28 "L_05_G" I R 5450 8300 60 
F29 "L_05_B" I R 5450 8400 60 
F30 "L_06_R" I R 5450 8500 60 
F31 "L_06_G" I R 5450 8600 60 
F32 "L_06_B" I R 5450 8700 60 
F33 "L_07_R" I R 5450 8800 60 
F34 "L_07_G" I R 5450 8900 60 
F35 "L_07_B" I R 5450 9000 60 
F36 "L_08_R" I R 5450 9100 60 
F37 "L_08_G" I R 5450 9200 60 
F38 "L_08_B" I R 5450 9300 60 
F39 "L_09_R" I R 5450 9400 60 
F40 "L_09_G" I R 5450 9500 60 
F41 "L_09_B" I R 5450 9600 60 
F42 "L_10_R" I R 5450 9700 60 
F43 "L_10_G" I R 5450 9800 60 
F44 "L_10_B" I R 5450 9900 60 
F45 "L_11_R" I R 5450 10000 60 
F46 "L_11_G" I R 5450 10100 60 
F47 "L_11_B" I R 5450 10200 60 
$EndSheet
Text Label 5600 7050 0    60   ~ 0
L_01_R
Text Label 5600 7150 0    60   ~ 0
L_01_G
Text Label 5600 7250 0    60   ~ 0
L_01_B
Text Label 5600 7350 0    60   ~ 0
L_02_R
Text Label 5600 7450 0    60   ~ 0
L_02_G
Text Label 5600 7550 0    60   ~ 0
L_02_B
Text Label 5600 7650 0    60   ~ 0
L_03_R
Text Label 5600 7750 0    60   ~ 0
L_03_G
Text Label 5600 7850 0    60   ~ 0
L_03_B
Text Label 5600 7950 0    60   ~ 0
L_04_R
Text Label 5600 8050 0    60   ~ 0
L_04_G
Text Label 5600 8150 0    60   ~ 0
L_04_B
Text Label 5600 8250 0    60   ~ 0
L_05_R
Text Label 5600 8350 0    60   ~ 0
L_05_G
Text Label 5600 8450 0    60   ~ 0
L_05_B
Text Label 5600 8550 0    60   ~ 0
L_06_R
Text Label 5600 8650 0    60   ~ 0
L_06_G
Text Label 5600 8750 0    60   ~ 0
L_06_B
Text Label 5600 8850 0    60   ~ 0
L_07_R
Text Label 5600 8950 0    60   ~ 0
L_07_G
Text Label 5600 9050 0    60   ~ 0
L_07_B
Text Label 5600 9150 0    60   ~ 0
L_08_R
Text Label 5600 9250 0    60   ~ 0
L_08_G
Text Label 5600 9350 0    60   ~ 0
L_08_B
Text Label 5600 9450 0    60   ~ 0
L_09_R
Text Label 5600 9550 0    60   ~ 0
L_09_G
Text Label 5600 9650 0    60   ~ 0
L_09_B
Text Label 5600 9750 0    60   ~ 0
L_10_R
Text Label 5600 9850 0    60   ~ 0
L_10_G
Text Label 5600 9950 0    60   ~ 0
L_10_B
Text Label 5600 10050 0    60   ~ 0
L_11_R
Text Label 5600 10150 0    60   ~ 0
L_11_G
Text Label 5600 10250 0    60   ~ 0
L_11_B
Text Label 1300 2300 0    60   ~ 0
XERR
Text Label 3200 850  2    60   ~ 0
SIN
Text Label 1300 1600 0    60   ~ 0
SCLK
$Comp
L CONN_01X12 P1
U 1 1 5A6048A5
P 900 2050
F 0 "P1" H 900 2700 50  0000 C CNN
F 1 "CONN_01X12" V 1000 2050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 900 2050 60  0001 C CNN
F 3 "" H 900 2050 60  0000 C CNN
	1    900  2050
	-1   0    0    1   
$EndComp
Text Label 3200 950  2    60   ~ 0
SCLK
Text Label 3200 1150 2    60   ~ 0
VPRG
Text Label 3200 1250 2    60   ~ 0
XLAT
Text Label 3200 1350 2    60   ~ 0
BLANK
Text Label 3200 1450 2    60   ~ 0
DCPRG
Text Label 3200 1550 2    60   ~ 0
GSCLK
Text Label 3200 1650 2    60   ~ 0
XERR
Text Label 3200 2850 2    60   ~ 0
SCLK
Text Label 3200 3050 2    60   ~ 0
VPRG
Text Label 3200 3150 2    60   ~ 0
XLAT
Text Label 3200 3250 2    60   ~ 0
BLANK
Text Label 3200 3350 2    60   ~ 0
DCPRG
Text Label 3200 3450 2    60   ~ 0
GSCLK
Text Label 3200 3550 2    60   ~ 0
XERR
Text Label 3200 4750 2    60   ~ 0
SCLK
Text Label 3200 4950 2    60   ~ 0
VPRG
Text Label 3200 5050 2    60   ~ 0
XLAT
Text Label 3200 5150 2    60   ~ 0
BLANK
Text Label 3200 5250 2    60   ~ 0
DCPRG
Text Label 3200 5350 2    60   ~ 0
GSCLK
Text Label 3200 5450 2    60   ~ 0
XERR
Text Label 5500 950  2    60   ~ 0
SCLK
Text Label 5500 1150 2    60   ~ 0
VPRG
Text Label 5500 1250 2    60   ~ 0
XLAT
Text Label 5500 1350 2    60   ~ 0
BLANK
Text Label 5500 1450 2    60   ~ 0
DCPRG
Text Label 5500 1550 2    60   ~ 0
GSCLK
Text Label 5500 1650 2    60   ~ 0
XERR
Text Label 7800 950  2    60   ~ 0
SCLK
Text Label 7800 1150 2    60   ~ 0
VPRG
Text Label 7800 1250 2    60   ~ 0
XLAT
Text Label 7800 1350 2    60   ~ 0
BLANK
Text Label 7800 1450 2    60   ~ 0
DCPRG
Text Label 7800 1550 2    60   ~ 0
GSCLK
Text Label 7800 1650 2    60   ~ 0
XERR
Text Label 5500 2850 2    60   ~ 0
SCLK
Text Label 5500 3050 2    60   ~ 0
VPRG
Text Label 5500 3150 2    60   ~ 0
XLAT
Text Label 5500 3250 2    60   ~ 0
BLANK
Text Label 5500 3350 2    60   ~ 0
DCPRG
Text Label 5500 3450 2    60   ~ 0
GSCLK
Text Label 5500 3550 2    60   ~ 0
XERR
Text Label 5500 4750 2    60   ~ 0
SCLK
Text Label 5500 4950 2    60   ~ 0
VPRG
Text Label 5500 5050 2    60   ~ 0
XLAT
Text Label 5500 5150 2    60   ~ 0
BLANK
Text Label 5500 5250 2    60   ~ 0
DCPRG
Text Label 5500 5350 2    60   ~ 0
GSCLK
Text Label 5500 5450 2    60   ~ 0
XERR
Text Label 7800 2850 2    60   ~ 0
SCLK
Text Label 7800 3050 2    60   ~ 0
VPRG
Text Label 7800 3150 2    60   ~ 0
XLAT
Text Label 7800 3250 2    60   ~ 0
BLANK
Text Label 7800 3350 2    60   ~ 0
DCPRG
Text Label 7800 3450 2    60   ~ 0
GSCLK
Text Label 7800 3550 2    60   ~ 0
XERR
Text Label 7800 4750 2    60   ~ 0
SCLK
Text Label 7800 4950 2    60   ~ 0
VPRG
Text Label 7800 5050 2    60   ~ 0
XLAT
Text Label 7800 5150 2    60   ~ 0
BLANK
Text Label 7800 5250 2    60   ~ 0
DCPRG
Text Label 7800 5350 2    60   ~ 0
GSCLK
Text Label 7800 5450 2    60   ~ 0
XERR
Text Label 11300 2250 2    60   ~ 0
P_00_00
Text Label 11300 2350 2    60   ~ 0
P_01_00
Text Label 11300 2450 2    60   ~ 0
P_02_00
Text Label 11300 2550 2    60   ~ 0
P_03_00
Text Label 11300 2650 2    60   ~ 0
P_04_00
Text Label 11300 2750 2    60   ~ 0
P_05_00
Text Label 11800 2250 0    60   ~ 0
P_00_01
Text Label 11800 2350 0    60   ~ 0
P_01_01
Text Label 11800 2450 0    60   ~ 0
P_02_01
Text Label 11800 2550 0    60   ~ 0
P_03_01
Text Label 11800 2650 0    60   ~ 0
P_04_01
Text Label 11800 2750 0    60   ~ 0
P_05_01
Text Label 11300 2850 2    60   ~ 0
P_00_02
Text Label 11300 2950 2    60   ~ 0
P_01_02
Text Label 11300 3050 2    60   ~ 0
P_02_02
Text Label 11300 3150 2    60   ~ 0
P_03_02
Text Label 11300 3250 2    60   ~ 0
P_04_02
Text Label 11300 3350 2    60   ~ 0
P_05_02
Text Label 11800 2850 0    60   ~ 0
P_00_03
Text Label 11800 2950 0    60   ~ 0
P_01_03
Text Label 11800 3050 0    60   ~ 0
P_02_03
Text Label 11800 3150 0    60   ~ 0
P_03_03
Text Label 11800 3250 0    60   ~ 0
P_04_03
Text Label 11800 3350 0    60   ~ 0
P_05_03
Text Label 11300 3450 2    60   ~ 0
P_00_04
Text Label 11300 3550 2    60   ~ 0
P_01_04
Text Label 11300 3650 2    60   ~ 0
P_02_04
Text Label 11300 3750 2    60   ~ 0
P_03_04
Text Label 11300 3850 2    60   ~ 0
P_04_04
Text Label 11300 3950 2    60   ~ 0
P_05_04
Text Label 11800 3450 0    60   ~ 0
P_00_05
Text Label 11800 3550 0    60   ~ 0
P_01_05
Text Label 11800 3650 0    60   ~ 0
P_02_05
Text Label 11800 3750 0    60   ~ 0
P_03_05
Text Label 11800 3850 0    60   ~ 0
P_04_05
Text Label 11800 3950 0    60   ~ 0
P_05_05
Text Label 11300 4350 2    60   ~ 0
L_00_R
Text Label 11300 4450 2    60   ~ 0
L_00_G
Text Label 11300 4550 2    60   ~ 0
L_00_B
Text Label 11300 4950 2    60   ~ 0
L_01_R
Text Label 11300 5050 2    60   ~ 0
L_01_G
Text Label 11300 5150 2    60   ~ 0
L_01_B
Text Label 11300 4650 2    60   ~ 0
L_02_R
Text Label 11300 4750 2    60   ~ 0
L_02_G
Text Label 11300 4850 2    60   ~ 0
L_02_B
Text Notes 11300 2050 0    60   ~ 0
(0,0) , (5,0)\n(0,5) , (5,5)
Text Notes 13800 2050 0    60   ~ 0
(6,0) , (11,0)\n(6,5) , (11,5)
Text Notes 11300 5950 0    60   ~ 0
(0,6)  , (5,6)\n(0,11) , (5,11)
Text Notes 13750 5950 0    60   ~ 0
(6,6)  , (11,6)\n(6,11) , (11,11)
Text Label 13800 2250 2    60   ~ 0
P_06_00
Text Label 13800 2350 2    60   ~ 0
P_07_00
Text Label 13800 2450 2    60   ~ 0
P_08_00
Text Label 13800 2550 2    60   ~ 0
P_09_00
Text Label 13800 2650 2    60   ~ 0
P_10_00
Text Label 13800 2750 2    60   ~ 0
P_11_00
Text Label 14300 2250 0    60   ~ 0
P_06_01
Text Label 14300 2350 0    60   ~ 0
P_07_01
Text Label 14300 2450 0    60   ~ 0
P_08_01
Text Label 14300 2550 0    60   ~ 0
P_09_01
Text Label 14300 2650 0    60   ~ 0
P_10_01
Text Label 14300 2750 0    60   ~ 0
P_11_01
Text Label 13800 2850 2    60   ~ 0
P_06_02
Text Label 13800 2950 2    60   ~ 0
P_07_02
Text Label 13800 3050 2    60   ~ 0
P_08_02
Text Label 13800 3150 2    60   ~ 0
P_09_02
Text Label 13800 3250 2    60   ~ 0
P_10_02
Text Label 13800 3350 2    60   ~ 0
P_11_02
Text Label 14300 2850 0    60   ~ 0
P_06_03
Text Label 14300 2950 0    60   ~ 0
P_07_03
Text Label 14300 3050 0    60   ~ 0
P_08_03
Text Label 14300 3150 0    60   ~ 0
P_09_03
Text Label 14300 3250 0    60   ~ 0
P_10_03
Text Label 14300 3350 0    60   ~ 0
P_11_03
Text Label 13800 3450 2    60   ~ 0
P_06_04
Text Label 13800 3550 2    60   ~ 0
P_07_04
Text Label 13800 3650 2    60   ~ 0
P_08_04
Text Label 13800 3750 2    60   ~ 0
P_09_04
Text Label 13800 3850 2    60   ~ 0
P_10_04
Text Label 13800 3950 2    60   ~ 0
P_11_04
Text Label 14300 3450 0    60   ~ 0
P_06_05
Text Label 14300 3550 0    60   ~ 0
P_07_05
Text Label 14300 3650 0    60   ~ 0
P_08_05
Text Label 14300 3750 0    60   ~ 0
P_09_05
Text Label 14300 3850 0    60   ~ 0
P_10_05
Text Label 14300 3950 0    60   ~ 0
P_11_05
Text Label 13800 4350 2    60   ~ 0
L_03_R
Text Label 13800 4450 2    60   ~ 0
L_03_G
Text Label 13800 4550 2    60   ~ 0
L_03_B
Text Label 13800 4950 2    60   ~ 0
L_04_R
Text Label 13800 5050 2    60   ~ 0
L_04_G
Text Label 13800 5150 2    60   ~ 0
L_04_B
Text Label 13800 4650 2    60   ~ 0
L_05_R
Text Label 13800 4750 2    60   ~ 0
L_05_G
Text Label 13800 4850 2    60   ~ 0
L_05_B
Text Label 11300 6150 2    60   ~ 0
P_00_06
Text Label 11300 6250 2    60   ~ 0
P_01_06
Text Label 11300 6350 2    60   ~ 0
P_02_06
Text Label 11300 6450 2    60   ~ 0
P_03_06
Text Label 11300 6550 2    60   ~ 0
P_04_06
Text Label 11300 6650 2    60   ~ 0
P_05_06
Text Label 11800 6150 0    60   ~ 0
P_00_07
Text Label 11800 6250 0    60   ~ 0
P_01_07
Text Label 11800 6350 0    60   ~ 0
P_02_07
Text Label 11800 6450 0    60   ~ 0
P_03_07
Text Label 11800 6550 0    60   ~ 0
P_04_07
Text Label 11800 6650 0    60   ~ 0
P_05_07
Text Label 11300 6750 2    60   ~ 0
P_00_08
Text Label 11300 6850 2    60   ~ 0
P_01_08
Text Label 11300 6950 2    60   ~ 0
P_02_08
Text Label 11300 7050 2    60   ~ 0
P_03_08
Text Label 11300 7150 2    60   ~ 0
P_04_08
Text Label 11300 7250 2    60   ~ 0
P_05_08
Text Label 11800 6750 0    60   ~ 0
P_00_09
Text Label 11800 6850 0    60   ~ 0
P_01_09
Text Label 11800 6950 0    60   ~ 0
P_02_09
Text Label 11800 7050 0    60   ~ 0
P_03_09
Text Label 11800 7150 0    60   ~ 0
P_04_09
Text Label 11800 7250 0    60   ~ 0
P_05_09
Text Label 11300 7350 2    60   ~ 0
P_00_10
Text Label 11300 7450 2    60   ~ 0
P_01_10
Text Label 11300 7550 2    60   ~ 0
P_02_10
Text Label 11300 7650 2    60   ~ 0
P_03_10
Text Label 11300 7750 2    60   ~ 0
P_04_10
Text Label 11300 7850 2    60   ~ 0
P_05_10
Text Label 11800 7350 0    60   ~ 0
P_00_11
Text Label 11800 7450 0    60   ~ 0
P_01_11
Text Label 11800 7550 0    60   ~ 0
P_02_11
Text Label 11800 7650 0    60   ~ 0
P_03_11
Text Label 11800 7750 0    60   ~ 0
P_04_11
Text Label 11800 7850 0    60   ~ 0
P_05_11
Text Label 11300 8250 2    60   ~ 0
L_06_R
Text Label 11300 8350 2    60   ~ 0
L_06_G
Text Label 11300 8450 2    60   ~ 0
L_06_B
Text Label 11300 8850 2    60   ~ 0
L_07_R
Text Label 11300 8950 2    60   ~ 0
L_07_G
Text Label 11300 9050 2    60   ~ 0
L_07_B
Text Label 11300 8550 2    60   ~ 0
L_08_R
Text Label 11300 8650 2    60   ~ 0
L_08_G
Text Label 11300 8750 2    60   ~ 0
L_08_B
Text Label 13800 6150 2    60   ~ 0
P_06_06
Text Label 13800 6250 2    60   ~ 0
P_07_06
Text Label 13800 6350 2    60   ~ 0
P_08_06
Text Label 13800 6450 2    60   ~ 0
P_09_06
Text Label 13800 6550 2    60   ~ 0
P_10_06
Text Label 13800 6650 2    60   ~ 0
P_11_06
Text Label 14300 6150 0    60   ~ 0
P_06_07
Text Label 14300 6250 0    60   ~ 0
P_07_07
Text Label 14300 6350 0    60   ~ 0
P_08_07
Text Label 14300 6450 0    60   ~ 0
P_09_07
Text Label 14300 6550 0    60   ~ 0
P_10_07
Text Label 14300 6650 0    60   ~ 0
P_11_07
Text Label 13800 6750 2    60   ~ 0
P_06_08
Text Label 13800 6850 2    60   ~ 0
P_07_08
Text Label 13800 6950 2    60   ~ 0
P_08_08
Text Label 13800 7050 2    60   ~ 0
P_09_08
Text Label 13800 7150 2    60   ~ 0
P_10_08
Text Label 13800 7250 2    60   ~ 0
P_11_08
Text Label 14300 6750 0    60   ~ 0
P_06_09
Text Label 14300 6850 0    60   ~ 0
P_07_09
Text Label 14300 6950 0    60   ~ 0
P_08_09
Text Label 14300 7050 0    60   ~ 0
P_09_09
Text Label 14300 7150 0    60   ~ 0
P_10_09
Text Label 14300 7250 0    60   ~ 0
P_11_09
Text Label 13800 7350 2    60   ~ 0
P_06_10
Text Label 13800 7450 2    60   ~ 0
P_07_10
Text Label 13800 7550 2    60   ~ 0
P_08_10
Text Label 13800 7650 2    60   ~ 0
P_09_10
Text Label 13800 7750 2    60   ~ 0
P_10_10
Text Label 13800 7850 2    60   ~ 0
P_11_10
Text Label 14300 7350 0    60   ~ 0
P_06_11
Text Label 14300 7450 0    60   ~ 0
P_07_11
Text Label 14300 7550 0    60   ~ 0
P_08_11
Text Label 14300 7650 0    60   ~ 0
P_09_11
Text Label 14300 7750 0    60   ~ 0
P_10_11
Text Label 14300 7850 0    60   ~ 0
P_11_11
Text Label 13800 8250 2    60   ~ 0
L_09_R
Text Label 13800 8350 2    60   ~ 0
L_09_G
Text Label 13800 8450 2    60   ~ 0
L_09_B
Text Label 13800 8850 2    60   ~ 0
L_10_R
Text Label 13800 8950 2    60   ~ 0
L_10_G
Text Label 13800 9050 2    60   ~ 0
L_10_B
Text Label 13800 8550 2    60   ~ 0
L_11_R
Text Label 13800 8650 2    60   ~ 0
L_11_G
Text Label 13800 8750 2    60   ~ 0
L_11_B
$Comp
L CONN_01X02 P6
U 1 1 5A6A7B80
P 7600 9250
F 0 "P6" H 7600 9400 50  0000 C CNN
F 1 "CONN_01X02" V 7700 9250 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 7600 9250 60  0001 C CNN
F 3 "" H 7600 9250 60  0000 C CNN
	1    7600 9250
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5A6A92CE
P 7900 9600
F 0 "#PWR03" H 7900 9350 50  0001 C CNN
F 1 "GND" H 7900 9450 50  0000 C CNN
F 2 "" H 7900 9600 50  0000 C CNN
F 3 "" H 7900 9600 50  0000 C CNN
	1    7900 9600
	1    0    0    -1  
$EndComp
Text Notes 6050 7300 0    60   ~ 0
MOSFET TREE\nPositive power is applied to one color layer via these MOSFETS.\nBecause they are P-FETs, HIGH level is inactive and LOW level is active. \nTo activate a layer, set one line in each group (Q, L, C) LOW.\n\nQuarter (Q):  There are 4 "slices" placed like books on a bookshelf.\nLayer (L):    There are 3 layers in each quarter.\nColor(C):	    There are 3 colors (RGB) within a layer.
Text Notes 9550 1100 0    60   ~ 0
TLC DAISY CHAIN\nThe active layer is displayed via 144 TLC outputs.\nEach LED on a layer corresponds to one output.\nOnly one color layer is active at any given time.\nThe active layer is selected via the MOSFET TREE.
Text Notes 11900 1850 0    60   ~ 0
All signals are routed to these connectors \nto be distributed to daughter boards.
Text Notes 7850 8800 0    60   ~ 0
POWER INLET & REGULATOR
Text Notes 850  1350 0    60   ~ 0
TLC INPUT
Text Notes 550  6600 0    60   ~ 0
MOSFET TREE INPUT
Text Notes 9650 3200 0    60   ~ 0
1 Division = 1 Half Row
$Comp
L CONN_01X14 P3
U 1 1 5A6EEA00
P 1200 4800
F 0 "P3" H 1200 5550 50  0000 C CNN
F 1 "CONN_01X14" V 1300 4800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x14_Pitch2.54mm" H 1200 4800 60  0001 C CNN
F 3 "" H 1200 4800 60  0000 C CNN
	1    1200 4800
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X14 P4
U 1 1 5A6EF71B
P 1550 4800
F 0 "P4" H 1550 5550 50  0000 C CNN
F 1 "CONN_01X14" V 1650 4800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x14_Pitch2.54mm" H 1550 4800 60  0001 C CNN
F 3 "" H 1550 4800 60  0000 C CNN
	1    1550 4800
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5A6F4DFF
P 600 4150
F 0 "#PWR04" H 600 3900 50  0001 C CNN
F 1 "GND" H 600 4000 50  0000 C CNN
F 2 "" H 600 4150 50  0000 C CNN
F 3 "" H 600 4150 50  0000 C CNN
	1    600  4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5A6F547F
P 2500 4250
F 0 "#PWR05" H 2500 4000 50  0001 C CNN
F 1 "GND" H 2500 4100 50  0000 C CNN
F 2 "" H 2500 4250 50  0000 C CNN
F 3 "" H 2500 4250 50  0000 C CNN
	1    2500 4250
	1    0    0    -1  
$EndComp
NoConn ~ 1750 4150
$Comp
L +3.3V #PWR06
U 1 1 5A6F730C
P 2300 4050
F 0 "#PWR06" H 2300 3900 50  0001 C CNN
F 1 "+3.3V" H 2300 4190 50  0000 C CNN
F 2 "" H 2300 4050 50  0000 C CNN
F 3 "" H 2300 4050 50  0000 C CNN
	1    2300 4050
	1    0    0    -1  
$EndComp
Text Label 1000 5350 2    60   ~ 0
SIN
Text Label 1000 5250 2    60   ~ 0
XLAT
Text Label 1000 5150 2    60   ~ 0
GSCLK
Text Label 1000 4450 2    60   ~ 0
BLANK
Text Label 1000 4650 2    60   ~ 0
VPRG
Text Label 1000 4550 2    60   ~ 0
DCPRG
Text Label 1750 5450 0    60   ~ 0
SCLK
Text Label 1150 6750 0    60   ~ 0
P_Q_0
Text Label 1150 6850 0    60   ~ 0
P_Q_1
Text Label 1150 6950 0    60   ~ 0
P_Q_2
Text Label 1150 7050 0    60   ~ 0
P_Q_3
Text Label 1150 7150 0    60   ~ 0
P_L_0
Text Label 1150 7250 0    60   ~ 0
P_L_1
Text Label 1150 7350 0    60   ~ 0
P_L_2
Text Label 1150 7450 0    60   ~ 0
P_C_R
Text Label 1150 7550 0    60   ~ 0
P_C_G
Text Label 1150 7650 0    60   ~ 0
P_C_B
Text Label 2050 6750 2    60   ~ 0
P_Q_0
Text Label 2050 6850 2    60   ~ 0
P_Q_1
Text Label 2050 6950 2    60   ~ 0
P_Q_2
Text Label 2050 7050 2    60   ~ 0
P_Q_3
Text Label 2050 7200 2    60   ~ 0
P_L_0
Text Label 2050 7300 2    60   ~ 0
P_L_1
Text Label 2050 7400 2    60   ~ 0
P_L_2
Text Label 2050 7550 2    60   ~ 0
P_C_R
Text Label 2050 7650 2    60   ~ 0
P_C_G
Text Label 2050 7750 2    60   ~ 0
P_C_B
Text Label 1000 4750 2    60   ~ 0
P_Q_0
Text Label 1000 4850 2    60   ~ 0
P_Q_1
Text Label 1000 4950 2    60   ~ 0
P_Q_2
Text Label 1000 5050 2    60   ~ 0
P_Q_3
Text Label 1750 4850 0    60   ~ 0
P_L_0
Text Label 1000 4250 2    60   ~ 0
P_L_1
Text Label 1000 4350 2    60   ~ 0
P_L_2
Text Label 1750 5150 0    60   ~ 0
P_C_R
Text Label 1750 5050 0    60   ~ 0
P_C_G
Text Label 1750 4950 0    60   ~ 0
P_C_B
$Comp
L CONN_01X07 P5
U 1 1 5A719E7A
P 2500 5150
F 0 "P5" H 2500 5550 50  0000 C CNN
F 1 "CONN_01X07" V 2600 5150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 2500 5150 60  0001 C CNN
F 3 "" H 2500 5150 60  0000 C CNN
	1    2500 5150
	1    0    0    -1  
$EndComp
Text Notes 950  3950 0    60   ~ 0
Teensy LC "Socket"
$Comp
L CONN_02X30 P7
U 1 1 5A75D3CC
P 11550 3700
F 0 "P7" H 11550 5250 50  0000 C CNN
F 1 "CONN_02X30" V 11550 3700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x30_Pitch2.54mm" H 11550 3200 60  0001 C CNN
F 3 "" H 11550 3200 60  0000 C CNN
	1    11550 3700
	1    0    0    -1  
$EndComp
Text Notes 11900 4650 0    60   ~ 0
These pins are paired \nfor high current (3A)
$Comp
L CONN_02X30 P9
U 1 1 5A773C43
P 14050 3700
F 0 "P9" H 14050 5250 50  0000 C CNN
F 1 "CONN_02X30" V 14050 3700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x30_Pitch2.54mm" H 14050 3200 60  0001 C CNN
F 3 "" H 14050 3200 60  0000 C CNN
	1    14050 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X30 P8
U 1 1 5A787DF0
P 11550 7600
F 0 "P8" H 11550 9150 50  0000 C CNN
F 1 "CONN_02X30" V 11550 7600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x30_Pitch2.54mm" H 11550 7100 60  0001 C CNN
F 3 "" H 11550 7100 60  0000 C CNN
	1    11550 7600
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X30 P10
U 1 1 5A78815B
P 14050 7600
F 0 "P10" H 14050 9150 50  0000 C CNN
F 1 "CONN_02X30" V 14050 7600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x30_Pitch2.54mm" H 14050 7100 60  0001 C CNN
F 3 "" H 14050 7100 60  0000 C CNN
	1    14050 7600
	1    0    0    -1  
$EndComp
$Comp
L SPX2920U-3.3 U1
U 1 1 5A6EEAF3
P 8550 9200
F 0 "U1" H 8550 9450 40  0000 C CNN
F 1 "SPX2920U-3.3" H 8550 9400 40  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 8550 9300 35  0000 C CIN
F 3 "" H 8550 9200 60  0000 C CNN
	1    8550 9200
	1    0    0    -1  
$EndComp
$Comp
L CP1 C11
U 1 1 5A6F98B9
P 8950 9300
F 0 "C11" H 8975 9400 50  0000 L CNN
F 1 "10uF" H 8975 9200 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 8950 9300 60  0001 C CNN
F 3 "" H 8950 9300 60  0000 C CNN
	1    8950 9300
	1    0    0    -1  
$EndComp
$Comp
L CP1 C10
U 1 1 5A6FA5C7
P 8150 9300
F 0 "C10" H 8175 9400 50  0000 L CNN
F 1 "10uF" H 8175 9200 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 8150 9300 60  0001 C CNN
F 3 "" H 8150 9300 60  0000 C CNN
	1    8150 9300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5A6FAC6E
P 8550 9600
F 0 "#PWR07" H 8550 9350 50  0001 C CNN
F 1 "GND" H 8550 9450 50  0000 C CNN
F 2 "" H 8550 9600 50  0000 C CNN
F 3 "" H 8550 9600 50  0000 C CNN
	1    8550 9600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR08
U 1 1 5A6FD4BF
P 7900 9050
F 0 "#PWR08" H 7900 8900 50  0001 C CNN
F 1 "+5V" H 7900 9190 50  0000 C CNN
F 2 "" H 7900 9050 60  0000 C CNN
F 3 "" H 7900 9050 60  0000 C CNN
	1    7900 9050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR09
U 1 1 5A700E96
P 9200 9050
F 0 "#PWR09" H 9200 8900 50  0001 C CNN
F 1 "+3.3V" H 9200 9190 50  0000 C CNN
F 2 "" H 9200 9050 50  0000 C CNN
F 3 "" H 9200 9050 50  0000 C CNN
	1    9200 9050
	1    0    0    -1  
$EndComp
$Comp
L CP1 C12
U 1 1 5A71C1DD
P 9650 9250
F 0 "C12" H 9675 9350 50  0000 L CNN
F 1 "100uF" H 9675 9150 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 9650 9250 60  0001 C CNN
F 3 "" H 9650 9250 60  0000 C CNN
	1    9650 9250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5A71C1E4
P 9650 9600
F 0 "#PWR010" H 9650 9350 50  0001 C CNN
F 1 "GND" H 9650 9450 50  0000 C CNN
F 2 "" H 9650 9600 60  0000 C CNN
F 3 "" H 9650 9600 60  0000 C CNN
	1    9650 9600
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR011
U 1 1 5A71C1EA
P 9650 9050
F 0 "#PWR011" H 9650 8900 50  0001 C CNN
F 1 "+5V" H 9650 9190 50  0000 C CNN
F 2 "" H 9650 9050 60  0000 C CNN
F 3 "" H 9650 9050 60  0000 C CNN
	1    9650 9050
	1    0    0    -1  
$EndComp
$Sheet
S 2200 6600 850  1200
U 5A730FC5
F0 "Level Shift" 60
F1 "child_sheets/level_shift.sch" 60
F2 "IN_0" I L 2200 6700 60 
F3 "OUT_0" I R 3050 6700 60 
F4 "IN_1" I L 2200 6800 60 
F5 "OUT_1" I R 3050 6800 60 
F6 "IN_2" I L 2200 6900 60 
F7 "OUT_2" I R 3050 6900 60 
F8 "IN_3" I L 2200 7000 60 
F9 "OUT_3" I R 3050 7000 60 
F10 "IN_4" I L 2200 7150 60 
F11 "OUT_4" I R 3050 7150 60 
F12 "IN_5" I L 2200 7250 60 
F13 "OUT_5" I R 3050 7250 60 
F14 "IN_6" I L 2200 7350 60 
F15 "OUT_6" I R 3050 7350 60 
F16 "IN_7" I L 2200 7500 60 
F17 "OUT_7" I R 3050 7500 60 
F18 "IN_8" I L 2200 7600 60 
F19 "OUT_8" I R 3050 7600 60 
F20 "IN_9" I L 2200 7700 60 
F21 "OUT_9" I R 3050 7700 60 
$EndSheet
Wire Wire Line
	4350 750  4250 750 
Wire Wire Line
	4250 750  4200 700 
Wire Wire Line
	4350 850  4250 850 
Wire Wire Line
	4250 850  4200 800 
Wire Wire Line
	4350 950  4250 950 
Wire Wire Line
	4250 950  4200 900 
Wire Wire Line
	4350 1050 4250 1050
Wire Wire Line
	4250 1050 4200 1000
Wire Wire Line
	4350 1150 4250 1150
Wire Wire Line
	4250 1150 4200 1100
Wire Wire Line
	4350 1250 4250 1250
Wire Wire Line
	4250 1250 4200 1200
Wire Wire Line
	4350 1350 4250 1350
Wire Wire Line
	4250 1350 4200 1300
Wire Wire Line
	4350 1450 4250 1450
Wire Wire Line
	4250 1450 4200 1400
Wire Wire Line
	4350 1550 4250 1550
Wire Wire Line
	4250 1550 4200 1500
Wire Wire Line
	4350 1650 4250 1650
Wire Wire Line
	4250 1650 4200 1600
Wire Wire Line
	4350 1750 4250 1750
Wire Wire Line
	4250 1750 4200 1700
Wire Wire Line
	4350 1850 4250 1850
Wire Wire Line
	4250 1850 4200 1800
Wire Wire Line
	4350 1950 4250 1950
Wire Wire Line
	4250 1950 4200 1900
Wire Wire Line
	4350 2050 4250 2050
Wire Wire Line
	4250 2050 4200 2000
Wire Wire Line
	4350 2150 4250 2150
Wire Wire Line
	4250 2150 4200 2100
Wire Wire Line
	4350 2250 4250 2250
Wire Wire Line
	4250 2250 4200 2200
Wire Wire Line
	4350 2650 4250 2650
Wire Wire Line
	4250 2650 4200 2600
Wire Wire Line
	4350 2750 4250 2750
Wire Wire Line
	4250 2750 4200 2700
Wire Wire Line
	4350 2850 4250 2850
Wire Wire Line
	4250 2850 4200 2800
Wire Wire Line
	4350 2950 4250 2950
Wire Wire Line
	4250 2950 4200 2900
Wire Wire Line
	4350 3050 4250 3050
Wire Wire Line
	4250 3050 4200 3000
Wire Wire Line
	4350 3150 4250 3150
Wire Wire Line
	4250 3150 4200 3100
Wire Wire Line
	4350 3250 4250 3250
Wire Wire Line
	4250 3250 4200 3200
Wire Wire Line
	4350 3350 4250 3350
Wire Wire Line
	4250 3350 4200 3300
Wire Wire Line
	4350 3450 4250 3450
Wire Wire Line
	4250 3450 4200 3400
Wire Wire Line
	4350 3550 4250 3550
Wire Wire Line
	4250 3550 4200 3500
Wire Wire Line
	4350 3650 4250 3650
Wire Wire Line
	4250 3650 4200 3600
Wire Wire Line
	4350 3750 4250 3750
Wire Wire Line
	4250 3750 4200 3700
Wire Wire Line
	4350 3850 4250 3850
Wire Wire Line
	4250 3850 4200 3800
Wire Wire Line
	4350 3950 4250 3950
Wire Wire Line
	4250 3950 4200 3900
Wire Wire Line
	4350 4050 4250 4050
Wire Wire Line
	4250 4050 4200 4000
Wire Wire Line
	4350 4150 4250 4150
Wire Wire Line
	4250 4150 4200 4100
Wire Wire Line
	4350 4550 4250 4550
Wire Wire Line
	4250 4550 4200 4500
Wire Wire Line
	4350 4650 4250 4650
Wire Wire Line
	4250 4650 4200 4600
Wire Wire Line
	4350 4750 4250 4750
Wire Wire Line
	4250 4750 4200 4700
Wire Wire Line
	4350 4850 4250 4850
Wire Wire Line
	4250 4850 4200 4800
Wire Wire Line
	4350 4950 4250 4950
Wire Wire Line
	4250 4950 4200 4900
Wire Wire Line
	4350 5050 4250 5050
Wire Wire Line
	4250 5050 4200 5000
Wire Wire Line
	4350 5150 4250 5150
Wire Wire Line
	4250 5150 4200 5100
Wire Wire Line
	4350 5250 4250 5250
Wire Wire Line
	4250 5250 4200 5200
Wire Wire Line
	4350 5350 4250 5350
Wire Wire Line
	4250 5350 4200 5300
Wire Wire Line
	4350 5450 4250 5450
Wire Wire Line
	4250 5450 4200 5400
Wire Wire Line
	4350 5550 4250 5550
Wire Wire Line
	4250 5550 4200 5500
Wire Wire Line
	4350 5650 4250 5650
Wire Wire Line
	4250 5650 4200 5600
Wire Wire Line
	4350 5750 4250 5750
Wire Wire Line
	4250 5750 4200 5700
Wire Wire Line
	4350 5850 4250 5850
Wire Wire Line
	4250 5850 4200 5800
Wire Wire Line
	4350 5950 4250 5950
Wire Wire Line
	4250 5950 4200 5900
Wire Wire Line
	4350 6050 4250 6050
Wire Wire Line
	4250 6050 4200 6000
Wire Wire Line
	6550 750  6500 700 
Wire Wire Line
	6550 850  6500 800 
Wire Wire Line
	6550 950  6500 900 
Wire Wire Line
	6550 1050 6500 1000
Wire Wire Line
	6550 1150 6500 1100
Wire Wire Line
	6550 1250 6500 1200
Wire Wire Line
	6550 1350 6500 1300
Wire Wire Line
	6550 1450 6500 1400
Wire Wire Line
	6550 1550 6500 1500
Wire Wire Line
	6550 1650 6500 1600
Wire Wire Line
	6550 1750 6500 1700
Wire Wire Line
	6550 1850 6500 1800
Wire Wire Line
	6550 1950 6500 1900
Wire Wire Line
	6550 2050 6500 2000
Wire Wire Line
	6550 2150 6500 2100
Wire Wire Line
	6550 2250 6500 2200
Wire Wire Line
	6550 2650 6500 2600
Wire Wire Line
	6550 2750 6500 2700
Wire Wire Line
	6550 2850 6500 2800
Wire Wire Line
	6550 2950 6500 2900
Wire Wire Line
	6550 3050 6500 3000
Wire Wire Line
	6550 3150 6500 3100
Wire Wire Line
	6550 3250 6500 3200
Wire Wire Line
	6550 3350 6500 3300
Wire Wire Line
	6550 3450 6500 3400
Wire Wire Line
	6550 3550 6500 3500
Wire Wire Line
	6550 3650 6500 3600
Wire Wire Line
	6550 3750 6500 3700
Wire Wire Line
	6550 3850 6500 3800
Wire Wire Line
	6550 3950 6500 3900
Wire Wire Line
	6550 4050 6500 4000
Wire Wire Line
	6550 4150 6500 4100
Wire Wire Line
	6550 4550 6500 4500
Wire Wire Line
	6550 4650 6500 4600
Wire Wire Line
	6550 4750 6500 4700
Wire Wire Line
	6550 4850 6500 4800
Wire Wire Line
	6550 4950 6500 4900
Wire Wire Line
	6550 5050 6500 5000
Wire Wire Line
	6550 5150 6500 5100
Wire Wire Line
	6550 5250 6500 5200
Wire Wire Line
	6550 5350 6500 5300
Wire Wire Line
	6550 5450 6500 5400
Wire Wire Line
	6550 5550 6500 5500
Wire Wire Line
	6550 5650 6500 5600
Wire Wire Line
	6550 5750 6500 5700
Wire Wire Line
	6550 5850 6500 5800
Wire Wire Line
	6550 5950 6500 5900
Wire Wire Line
	6550 6050 6500 6000
Wire Wire Line
	8850 750  8800 700 
Wire Wire Line
	8850 850  8800 800 
Wire Wire Line
	8850 950  8800 900 
Wire Wire Line
	8850 1050 8800 1000
Wire Wire Line
	8850 1150 8800 1100
Wire Wire Line
	8850 1250 8800 1200
Wire Wire Line
	8850 1350 8800 1300
Wire Wire Line
	8850 1450 8800 1400
Wire Wire Line
	8850 1550 8800 1500
Wire Wire Line
	8850 1650 8800 1600
Wire Wire Line
	8850 1750 8800 1700
Wire Wire Line
	8850 1850 8800 1800
Wire Wire Line
	8850 1950 8800 1900
Wire Wire Line
	8850 2050 8800 2000
Wire Wire Line
	8850 2150 8800 2100
Wire Wire Line
	8850 2250 8800 2200
Wire Wire Line
	8850 2650 8800 2600
Wire Wire Line
	8850 2750 8800 2700
Wire Wire Line
	8850 2850 8800 2800
Wire Wire Line
	8850 2950 8800 2900
Wire Wire Line
	8850 3050 8800 3000
Wire Wire Line
	8850 3150 8800 3100
Wire Wire Line
	8850 3250 8800 3200
Wire Wire Line
	8850 3350 8800 3300
Wire Wire Line
	8850 3450 8800 3400
Wire Wire Line
	8850 3550 8800 3500
Wire Wire Line
	8850 3650 8800 3600
Wire Wire Line
	8850 3750 8800 3700
Wire Wire Line
	8850 3850 8800 3800
Wire Wire Line
	8850 3950 8800 3900
Wire Wire Line
	8850 4050 8800 4000
Wire Wire Line
	8850 4150 8800 4100
Wire Wire Line
	8850 4550 8800 4500
Wire Wire Line
	8850 4650 8800 4600
Wire Wire Line
	8850 4750 8800 4700
Wire Wire Line
	8850 4850 8800 4800
Wire Wire Line
	8850 4950 8800 4900
Wire Wire Line
	8850 5050 8800 5000
Wire Wire Line
	8850 5150 8800 5100
Wire Wire Line
	8850 5250 8800 5200
Wire Wire Line
	8850 5350 8800 5300
Wire Wire Line
	8850 5450 8800 5400
Wire Wire Line
	8850 5550 8800 5500
Wire Wire Line
	8850 5650 8800 5600
Wire Wire Line
	8850 5750 8800 5700
Wire Wire Line
	8850 5850 8800 5800
Wire Wire Line
	8850 5950 8800 5900
Wire Wire Line
	8850 6050 8800 6000
Wire Wire Line
	3350 2100 3250 2100
Wire Wire Line
	3250 2100 3250 2700
Wire Wire Line
	3250 2700 3350 2700
Wire Wire Line
	3350 4000 3250 4000
Wire Wire Line
	3250 4000 3250 4600
Wire Wire Line
	3250 4600 3350 4600
Wire Wire Line
	3350 5900 3250 5900
Wire Wire Line
	3250 5900 3250 6250
Wire Wire Line
	3250 6250 4850 6250
Wire Wire Line
	4850 6250 4850 800 
Wire Wire Line
	4850 800  5650 800 
Wire Wire Line
	5650 2100 5550 2100
Wire Wire Line
	5550 2100 5550 2700
Wire Wire Line
	5550 2700 5650 2700
Wire Wire Line
	5650 4000 5550 4000
Wire Wire Line
	5550 4000 5550 4600
Wire Wire Line
	5550 4600 5650 4600
Wire Wire Line
	5650 5900 5550 5900
Wire Wire Line
	5550 5900 5550 6250
Wire Wire Line
	5550 6250 7150 6250
Wire Wire Line
	7150 6250 7150 800 
Wire Wire Line
	7150 800  7950 800 
Wire Wire Line
	7950 2100 7850 2100
Wire Wire Line
	7850 2100 7850 2700
Wire Wire Line
	7850 2700 7950 2700
Wire Wire Line
	7950 4000 7850 4000
Wire Wire Line
	7850 4000 7850 4600
Wire Wire Line
	7850 4600 7950 4600
Wire Wire Line
	6650 750  6550 750 
Wire Wire Line
	6650 850  6550 850 
Wire Wire Line
	6650 950  6550 950 
Wire Wire Line
	6650 1050 6550 1050
Wire Wire Line
	6650 1150 6550 1150
Wire Wire Line
	6650 1250 6550 1250
Wire Wire Line
	6650 1350 6550 1350
Wire Wire Line
	6650 1450 6550 1450
Wire Wire Line
	6650 1550 6550 1550
Wire Wire Line
	6650 1650 6550 1650
Wire Wire Line
	6650 1750 6550 1750
Wire Wire Line
	6650 1850 6550 1850
Wire Wire Line
	6650 1950 6550 1950
Wire Wire Line
	6650 2050 6550 2050
Wire Wire Line
	6650 2150 6550 2150
Wire Wire Line
	6650 2250 6550 2250
Wire Wire Line
	6650 2650 6550 2650
Wire Wire Line
	6650 2750 6550 2750
Wire Wire Line
	6650 2850 6550 2850
Wire Wire Line
	6650 2950 6550 2950
Wire Wire Line
	6650 3050 6550 3050
Wire Wire Line
	6650 3150 6550 3150
Wire Wire Line
	6650 3250 6550 3250
Wire Wire Line
	6650 3350 6550 3350
Wire Wire Line
	6650 3450 6550 3450
Wire Wire Line
	6650 3550 6550 3550
Wire Wire Line
	6650 3650 6550 3650
Wire Wire Line
	6650 3750 6550 3750
Wire Wire Line
	6650 3850 6550 3850
Wire Wire Line
	6650 3950 6550 3950
Wire Wire Line
	6650 4050 6550 4050
Wire Wire Line
	6650 4150 6550 4150
Wire Wire Line
	6650 4550 6550 4550
Wire Wire Line
	6650 4650 6550 4650
Wire Wire Line
	6650 4750 6550 4750
Wire Wire Line
	6650 4850 6550 4850
Wire Wire Line
	6650 4950 6550 4950
Wire Wire Line
	6650 5050 6550 5050
Wire Wire Line
	6650 5150 6550 5150
Wire Wire Line
	6650 5250 6550 5250
Wire Wire Line
	6650 5350 6550 5350
Wire Wire Line
	6650 5450 6550 5450
Wire Wire Line
	6650 5550 6550 5550
Wire Wire Line
	6650 5650 6550 5650
Wire Wire Line
	6650 5750 6550 5750
Wire Wire Line
	6650 5850 6550 5850
Wire Wire Line
	6650 5950 6550 5950
Wire Wire Line
	6650 6050 6550 6050
Wire Wire Line
	8950 750  8850 750 
Wire Wire Line
	8950 850  8850 850 
Wire Wire Line
	8950 950  8850 950 
Wire Wire Line
	8950 1050 8850 1050
Wire Wire Line
	8950 1150 8850 1150
Wire Wire Line
	8950 1250 8850 1250
Wire Wire Line
	8950 1350 8850 1350
Wire Wire Line
	8950 1450 8850 1450
Wire Wire Line
	8950 1550 8850 1550
Wire Wire Line
	8950 1650 8850 1650
Wire Wire Line
	8950 1750 8850 1750
Wire Wire Line
	8950 1850 8850 1850
Wire Wire Line
	8950 1950 8850 1950
Wire Wire Line
	8950 2050 8850 2050
Wire Wire Line
	8950 2150 8850 2150
Wire Wire Line
	8950 2250 8850 2250
Wire Wire Line
	8950 2650 8850 2650
Wire Wire Line
	8950 2750 8850 2750
Wire Wire Line
	8950 2850 8850 2850
Wire Wire Line
	8950 2950 8850 2950
Wire Wire Line
	8950 3050 8850 3050
Wire Wire Line
	8950 3150 8850 3150
Wire Wire Line
	8950 3250 8850 3250
Wire Wire Line
	8950 3350 8850 3350
Wire Wire Line
	8950 3450 8850 3450
Wire Wire Line
	8950 3550 8850 3550
Wire Wire Line
	8950 3650 8850 3650
Wire Wire Line
	8950 3750 8850 3750
Wire Wire Line
	8950 3850 8850 3850
Wire Wire Line
	8950 3950 8850 3950
Wire Wire Line
	8950 4050 8850 4050
Wire Wire Line
	8950 4150 8850 4150
Wire Wire Line
	8950 4550 8850 4550
Wire Wire Line
	8950 4650 8850 4650
Wire Wire Line
	8950 4750 8850 4750
Wire Wire Line
	8950 4850 8850 4850
Wire Wire Line
	8950 4950 8850 4950
Wire Wire Line
	8950 5050 8850 5050
Wire Wire Line
	8950 5150 8850 5150
Wire Wire Line
	8950 5250 8850 5250
Wire Wire Line
	8950 5350 8850 5350
Wire Wire Line
	8950 5450 8850 5450
Wire Wire Line
	8950 5550 8850 5550
Wire Wire Line
	8950 5650 8850 5650
Wire Wire Line
	8950 5750 8850 5750
Wire Wire Line
	8950 5850 8850 5850
Wire Wire Line
	8950 5950 8850 5950
Wire Wire Line
	8950 6050 8850 6050
Wire Wire Line
	1300 1500 1100 1500
Wire Wire Line
	1100 1700 1300 1700
Wire Wire Line
	1300 1800 1100 1800
Wire Wire Line
	1300 1900 1100 1900
Wire Wire Line
	1300 2000 1100 2000
Wire Wire Line
	1300 2100 1100 2100
Wire Wire Line
	1900 2500 1100 2500
Wire Wire Line
	1100 2600 1900 2600
Connection ~ 1900 2600
Wire Wire Line
	1900 2500 1900 2800
Wire Wire Line
	1100 2200 1300 2200
Wire Wire Line
	7800 5950 7900 5950
Wire Wire Line
	7900 5950 7950 5900
Wire Wire Line
	5600 6750 5500 6750
Wire Wire Line
	5600 6850 5500 6850
Wire Wire Line
	5600 6950 5500 6950
Wire Wire Line
	5500 6750 5450 6700
Wire Wire Line
	5500 6850 5450 6800
Wire Wire Line
	5500 6950 5450 6900
Wire Wire Line
	5600 7050 5500 7050
Wire Wire Line
	5600 7150 5500 7150
Wire Wire Line
	5600 7250 5500 7250
Wire Wire Line
	5500 7050 5450 7000
Wire Wire Line
	5500 7150 5450 7100
Wire Wire Line
	5500 7250 5450 7200
Wire Wire Line
	5600 7350 5500 7350
Wire Wire Line
	5600 7450 5500 7450
Wire Wire Line
	5600 7550 5500 7550
Wire Wire Line
	5500 7350 5450 7300
Wire Wire Line
	5500 7450 5450 7400
Wire Wire Line
	5500 7550 5450 7500
Wire Wire Line
	5600 7650 5500 7650
Wire Wire Line
	5600 7750 5500 7750
Wire Wire Line
	5600 7850 5500 7850
Wire Wire Line
	5500 7650 5450 7600
Wire Wire Line
	5500 7750 5450 7700
Wire Wire Line
	5500 7850 5450 7800
Wire Wire Line
	5600 7950 5500 7950
Wire Wire Line
	5600 8050 5500 8050
Wire Wire Line
	5600 8150 5500 8150
Wire Wire Line
	5500 7950 5450 7900
Wire Wire Line
	5500 8050 5450 8000
Wire Wire Line
	5500 8150 5450 8100
Wire Wire Line
	5600 8250 5500 8250
Wire Wire Line
	5600 8350 5500 8350
Wire Wire Line
	5600 8450 5500 8450
Wire Wire Line
	5500 8250 5450 8200
Wire Wire Line
	5500 8350 5450 8300
Wire Wire Line
	5500 8450 5450 8400
Wire Wire Line
	5600 8550 5500 8550
Wire Wire Line
	5600 8650 5500 8650
Wire Wire Line
	5600 8750 5500 8750
Wire Wire Line
	5500 8550 5450 8500
Wire Wire Line
	5500 8650 5450 8600
Wire Wire Line
	5500 8750 5450 8700
Wire Wire Line
	5600 8850 5500 8850
Wire Wire Line
	5600 8950 5500 8950
Wire Wire Line
	5600 9050 5500 9050
Wire Wire Line
	5500 8850 5450 8800
Wire Wire Line
	5500 8950 5450 8900
Wire Wire Line
	5500 9050 5450 9000
Wire Wire Line
	5600 9150 5500 9150
Wire Wire Line
	5600 9250 5500 9250
Wire Wire Line
	5600 9350 5500 9350
Wire Wire Line
	5500 9150 5450 9100
Wire Wire Line
	5500 9250 5450 9200
Wire Wire Line
	5500 9350 5450 9300
Wire Wire Line
	5600 9450 5500 9450
Wire Wire Line
	5600 9550 5500 9550
Wire Wire Line
	5600 9650 5500 9650
Wire Wire Line
	5500 9450 5450 9400
Wire Wire Line
	5500 9550 5450 9500
Wire Wire Line
	5500 9650 5450 9600
Wire Wire Line
	5600 9750 5500 9750
Wire Wire Line
	5600 9850 5500 9850
Wire Wire Line
	5600 9950 5500 9950
Wire Wire Line
	5500 9750 5450 9700
Wire Wire Line
	5500 9850 5450 9800
Wire Wire Line
	5500 9950 5450 9900
Wire Wire Line
	5600 10050 5500 10050
Wire Wire Line
	5600 10150 5500 10150
Wire Wire Line
	5600 10250 5500 10250
Wire Wire Line
	5500 10050 5450 10000
Wire Wire Line
	5500 10150 5450 10100
Wire Wire Line
	5500 10250 5450 10200
Wire Wire Line
	1300 2300 1100 2300
Wire Wire Line
	1100 2400 1900 2400
Wire Wire Line
	3200 850  3300 850 
Wire Wire Line
	3300 850  3350 800 
Wire Wire Line
	1300 1600 1100 1600
Wire Wire Line
	1900 2400 1900 1300
Wire Wire Line
	3200 950  3300 950 
Wire Wire Line
	3300 950  3350 900 
Wire Wire Line
	3200 1150 3300 1150
Wire Wire Line
	3300 1150 3350 1100
Wire Wire Line
	3200 1250 3300 1250
Wire Wire Line
	3300 1250 3350 1200
Wire Wire Line
	3200 1350 3300 1350
Wire Wire Line
	3300 1350 3350 1300
Wire Wire Line
	3200 1450 3300 1450
Wire Wire Line
	3300 1450 3350 1400
Wire Wire Line
	3200 1550 3300 1550
Wire Wire Line
	3300 1550 3350 1500
Wire Wire Line
	3200 1650 3300 1650
Wire Wire Line
	3300 1650 3350 1600
Wire Wire Line
	3200 2850 3300 2850
Wire Wire Line
	3300 2850 3350 2800
Wire Wire Line
	3200 3050 3300 3050
Wire Wire Line
	3300 3050 3350 3000
Wire Wire Line
	3200 3150 3300 3150
Wire Wire Line
	3300 3150 3350 3100
Wire Wire Line
	3200 3250 3300 3250
Wire Wire Line
	3300 3250 3350 3200
Wire Wire Line
	3200 3350 3300 3350
Wire Wire Line
	3300 3350 3350 3300
Wire Wire Line
	3200 3450 3300 3450
Wire Wire Line
	3300 3450 3350 3400
Wire Wire Line
	3200 3550 3300 3550
Wire Wire Line
	3300 3550 3350 3500
Wire Wire Line
	3200 4750 3300 4750
Wire Wire Line
	3300 4750 3350 4700
Wire Wire Line
	3200 4950 3300 4950
Wire Wire Line
	3300 4950 3350 4900
Wire Wire Line
	3200 5050 3300 5050
Wire Wire Line
	3300 5050 3350 5000
Wire Wire Line
	3200 5150 3300 5150
Wire Wire Line
	3300 5150 3350 5100
Wire Wire Line
	3200 5250 3300 5250
Wire Wire Line
	3300 5250 3350 5200
Wire Wire Line
	3200 5350 3300 5350
Wire Wire Line
	3300 5350 3350 5300
Wire Wire Line
	3200 5450 3300 5450
Wire Wire Line
	3300 5450 3350 5400
Wire Wire Line
	5500 950  5600 950 
Wire Wire Line
	5600 950  5650 900 
Wire Wire Line
	5500 1150 5600 1150
Wire Wire Line
	5600 1150 5650 1100
Wire Wire Line
	5500 1250 5600 1250
Wire Wire Line
	5600 1250 5650 1200
Wire Wire Line
	5500 1350 5600 1350
Wire Wire Line
	5600 1350 5650 1300
Wire Wire Line
	5500 1450 5600 1450
Wire Wire Line
	5600 1450 5650 1400
Wire Wire Line
	5500 1550 5600 1550
Wire Wire Line
	5600 1550 5650 1500
Wire Wire Line
	5500 1650 5600 1650
Wire Wire Line
	5600 1650 5650 1600
Wire Wire Line
	7800 950  7900 950 
Wire Wire Line
	7900 950  7950 900 
Wire Wire Line
	7800 1150 7900 1150
Wire Wire Line
	7900 1150 7950 1100
Wire Wire Line
	7800 1250 7900 1250
Wire Wire Line
	7900 1250 7950 1200
Wire Wire Line
	7800 1350 7900 1350
Wire Wire Line
	7900 1350 7950 1300
Wire Wire Line
	7800 1450 7900 1450
Wire Wire Line
	7900 1450 7950 1400
Wire Wire Line
	7800 1550 7900 1550
Wire Wire Line
	7900 1550 7950 1500
Wire Wire Line
	7800 1650 7900 1650
Wire Wire Line
	7900 1650 7950 1600
Wire Wire Line
	5500 2850 5600 2850
Wire Wire Line
	5600 2850 5650 2800
Wire Wire Line
	5500 3050 5600 3050
Wire Wire Line
	5600 3050 5650 3000
Wire Wire Line
	5500 3150 5600 3150
Wire Wire Line
	5600 3150 5650 3100
Wire Wire Line
	5500 3250 5600 3250
Wire Wire Line
	5600 3250 5650 3200
Wire Wire Line
	5500 3350 5600 3350
Wire Wire Line
	5600 3350 5650 3300
Wire Wire Line
	5500 3450 5600 3450
Wire Wire Line
	5600 3450 5650 3400
Wire Wire Line
	5500 3550 5600 3550
Wire Wire Line
	5600 3550 5650 3500
Wire Wire Line
	5500 4750 5600 4750
Wire Wire Line
	5600 4750 5650 4700
Wire Wire Line
	5500 4950 5600 4950
Wire Wire Line
	5600 4950 5650 4900
Wire Wire Line
	5500 5050 5600 5050
Wire Wire Line
	5600 5050 5650 5000
Wire Wire Line
	5500 5150 5600 5150
Wire Wire Line
	5600 5150 5650 5100
Wire Wire Line
	5500 5250 5600 5250
Wire Wire Line
	5600 5250 5650 5200
Wire Wire Line
	5500 5350 5600 5350
Wire Wire Line
	5600 5350 5650 5300
Wire Wire Line
	5500 5450 5600 5450
Wire Wire Line
	5600 5450 5650 5400
Wire Wire Line
	7800 2850 7900 2850
Wire Wire Line
	7900 2850 7950 2800
Wire Wire Line
	7800 3050 7900 3050
Wire Wire Line
	7900 3050 7950 3000
Wire Wire Line
	7800 3150 7900 3150
Wire Wire Line
	7900 3150 7950 3100
Wire Wire Line
	7800 3250 7900 3250
Wire Wire Line
	7900 3250 7950 3200
Wire Wire Line
	7800 3350 7900 3350
Wire Wire Line
	7900 3350 7950 3300
Wire Wire Line
	7800 3450 7900 3450
Wire Wire Line
	7900 3450 7950 3400
Wire Wire Line
	7800 3550 7900 3550
Wire Wire Line
	7900 3550 7950 3500
Wire Wire Line
	7800 4750 7900 4750
Wire Wire Line
	7900 4750 7950 4700
Wire Wire Line
	7800 4950 7900 4950
Wire Wire Line
	7900 4950 7950 4900
Wire Wire Line
	7800 5050 7900 5050
Wire Wire Line
	7900 5050 7950 5000
Wire Wire Line
	7800 5150 7900 5150
Wire Wire Line
	7900 5150 7950 5100
Wire Wire Line
	7800 5250 7900 5250
Wire Wire Line
	7900 5250 7950 5200
Wire Wire Line
	7800 5350 7900 5350
Wire Wire Line
	7900 5350 7950 5300
Wire Wire Line
	7800 5450 7900 5450
Wire Wire Line
	7900 5450 7950 5400
Wire Wire Line
	7900 9200 7800 9200
Wire Wire Line
	7900 9050 7900 9200
Wire Wire Line
	7800 9300 7900 9300
Wire Wire Line
	7900 9300 7900 9600
Wire Notes Line
	10900 2150 10850 2150
Wire Notes Line
	10850 2150 10850 3950
Wire Notes Line
	10850 2750 10900 2750
Wire Notes Line
	10850 3350 10900 3350
Wire Notes Line
	10850 3950 10900 3950
Wire Notes Line
	13400 2150 13350 2150
Wire Notes Line
	13350 2150 13350 3950
Wire Notes Line
	13350 2750 13400 2750
Wire Notes Line
	13350 3350 13400 3350
Wire Notes Line
	13350 3950 13400 3950
Wire Notes Line
	10900 6050 10850 6050
Wire Notes Line
	10850 6050 10850 7850
Wire Notes Line
	10850 6650 10900 6650
Wire Notes Line
	10850 7250 10900 7250
Wire Notes Line
	10850 7850 10900 7850
Wire Notes Line
	13400 6050 13350 6050
Wire Notes Line
	13350 6050 13350 7850
Wire Notes Line
	13350 6650 13400 6650
Wire Notes Line
	13350 7250 13400 7250
Wire Notes Line
	13350 7850 13400 7850
Wire Notes Line
	14700 6050 14750 6050
Wire Notes Line
	14750 6050 14750 7850
Wire Notes Line
	14750 6650 14700 6650
Wire Notes Line
	14750 7250 14700 7250
Wire Notes Line
	14750 7850 14700 7850
Wire Notes Line
	12200 6050 12250 6050
Wire Notes Line
	12250 6050 12250 7850
Wire Notes Line
	12250 6650 12200 6650
Wire Notes Line
	12250 7250 12200 7250
Wire Notes Line
	12250 7850 12200 7850
Wire Notes Line
	12200 2150 12250 2150
Wire Notes Line
	12250 2150 12250 3950
Wire Notes Line
	12250 2750 12200 2750
Wire Notes Line
	12250 3350 12200 3350
Wire Notes Line
	12250 3950 12200 3950
Wire Notes Line
	14700 2150 14750 2150
Wire Notes Line
	14750 2150 14750 3950
Wire Notes Line
	14750 2750 14700 2750
Wire Notes Line
	14750 3350 14700 3350
Wire Notes Line
	14750 3950 14700 3950
Wire Wire Line
	1000 4150 600  4150
Wire Wire Line
	1750 4250 2500 4250
Wire Wire Line
	1750 4350 2300 4350
Wire Wire Line
	2300 4350 2300 4050
Wire Wire Line
	2050 6750 2150 6750
Wire Wire Line
	2150 6750 2200 6700
Wire Wire Line
	2050 6850 2150 6850
Wire Wire Line
	2150 6850 2200 6800
Wire Wire Line
	2050 6950 2150 6950
Wire Wire Line
	2150 6950 2200 6900
Wire Wire Line
	2050 7050 2150 7050
Wire Wire Line
	2150 7050 2200 7000
Wire Wire Line
	2050 7200 2150 7200
Wire Wire Line
	2150 7200 2200 7150
Wire Wire Line
	2050 7300 2150 7300
Wire Wire Line
	2150 7300 2200 7250
Wire Wire Line
	2050 7400 2150 7400
Wire Wire Line
	2150 7400 2200 7350
Wire Wire Line
	2050 7550 2150 7550
Wire Wire Line
	2150 7550 2200 7500
Wire Wire Line
	2050 7650 2150 7650
Wire Wire Line
	2150 7650 2200 7600
Wire Wire Line
	2050 7750 2150 7750
Wire Wire Line
	2150 7750 2200 7700
Wire Wire Line
	1000 5450 1000 5550
Wire Wire Line
	1000 5550 2250 5550
Wire Wire Line
	2250 5550 2250 5450
Wire Wire Line
	2250 5450 2300 5450
Wire Wire Line
	1750 5350 2300 5350
Wire Wire Line
	1750 5250 2300 5250
Wire Wire Line
	1750 4450 2300 4450
Wire Wire Line
	2300 4450 2300 4850
Wire Wire Line
	1750 4550 2250 4550
Wire Wire Line
	2250 4550 2250 4950
Wire Wire Line
	2250 4950 2300 4950
Wire Wire Line
	1750 4650 2200 4650
Wire Wire Line
	2200 4650 2200 5050
Wire Wire Line
	2200 5050 2300 5050
Wire Wire Line
	1750 4750 2150 4750
Wire Wire Line
	2150 4750 2150 5150
Wire Wire Line
	2150 5150 2300 5150
Wire Wire Line
	11300 4350 11800 4350
Wire Wire Line
	11300 4450 11800 4450
Wire Wire Line
	11800 4550 11300 4550
Wire Wire Line
	11300 4650 11800 4650
Wire Wire Line
	11800 4750 11300 4750
Wire Wire Line
	11800 4850 11300 4850
Wire Wire Line
	11300 4950 11800 4950
Wire Wire Line
	13800 4350 14300 4350
Wire Wire Line
	13800 4450 14300 4450
Wire Wire Line
	14300 4550 13800 4550
Wire Wire Line
	13800 4650 14300 4650
Wire Wire Line
	14300 4750 13800 4750
Wire Wire Line
	14300 4850 13800 4850
Wire Wire Line
	13800 4950 14300 4950
Wire Wire Line
	11800 5050 11300 5050
Wire Wire Line
	11800 5150 11300 5150
Wire Wire Line
	14300 5050 13800 5050
Wire Wire Line
	14300 5150 13800 5150
Wire Notes Line
	11800 4300 11850 4300
Wire Notes Line
	11850 4300 11850 5200
Wire Notes Line
	11850 5200 11800 5200
Wire Wire Line
	11300 8250 11800 8250
Wire Wire Line
	11300 8350 11800 8350
Wire Wire Line
	11800 8450 11300 8450
Wire Wire Line
	11300 8550 11800 8550
Wire Wire Line
	11800 8650 11300 8650
Wire Wire Line
	11800 8750 11300 8750
Wire Wire Line
	11300 8850 11800 8850
Wire Wire Line
	11800 8950 11300 8950
Wire Wire Line
	11800 9050 11300 9050
Wire Wire Line
	13800 8250 14300 8250
Wire Wire Line
	13800 8350 14300 8350
Wire Wire Line
	14300 8450 13800 8450
Wire Wire Line
	13800 8550 14300 8550
Wire Wire Line
	14300 8650 13800 8650
Wire Wire Line
	14300 8750 13800 8750
Wire Wire Line
	13800 8850 14300 8850
Wire Wire Line
	14300 8950 13800 8950
Wire Wire Line
	14300 9050 13800 9050
Wire Wire Line
	8150 9450 8950 9450
Connection ~ 8550 9450
Wire Wire Line
	8550 9600 8550 9450
Wire Wire Line
	8150 9150 7900 9150
Connection ~ 7900 9150
Wire Wire Line
	8950 9150 9200 9150
Wire Wire Line
	9200 9150 9200 9050
Wire Wire Line
	9650 9600 9650 9400
Wire Wire Line
	9650 9100 9650 9050
Wire Wire Line
	3050 6700 3750 6700
Wire Wire Line
	3050 6800 3750 6800
Wire Wire Line
	3750 6900 3050 6900
Wire Wire Line
	3050 7000 3750 7000
Wire Wire Line
	3750 7150 3050 7150
Wire Wire Line
	3050 7250 3750 7250
Wire Wire Line
	3750 7350 3050 7350
Wire Wire Line
	3050 7500 3750 7500
Wire Wire Line
	3750 7600 3050 7600
Wire Wire Line
	3050 7700 3750 7700
$EndSCHEMATC
