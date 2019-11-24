EESchema Schematic File Version 4
LIBS:Bi-directional_Controller-cache
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "RC Bi-directional DC Motor Speed Controller"
Date "2019-03-30"
Rev ""
Comp "obbo.pl"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega8-16AU U2
U 1 1 5C9FC14B
P 3700 6850
F 0 "U2" H 3150 5450 50  0000 C CNN
F 1 "ATmega8-16AU" H 3350 5350 50  0000 C CNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 3700 6850 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2486-8-bit-avr-microcontroller-atmega8_l_datasheet.pdf" H 3700 6850 50  0001 C CNN
	1    3700 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5C9FC1C0
P 5250 4250
F 0 "R11" H 5320 4296 50  0000 L CNN
F 1 "10k" H 5320 4205 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 5180 4250 50  0001 C CNN
F 3 "~" H 5250 4250 50  0001 C CNN
	1    5250 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5C9FC2A7
P 5450 4750
F 0 "C4" H 5565 4796 50  0000 L CNN
F 1 "100n" H 5565 4705 50  0000 L CNN
F 2 "obbo_footprints:C_Disc_D5.0mm_W2.5mm_P5.00mm_PAD" H 5488 4600 50  0001 C CNN
F 3 "~" H 5450 4750 50  0001 C CNN
	1    5450 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 5C9FC360
P 5250 4050
F 0 "#PWR020" H 5250 3900 50  0001 C CNN
F 1 "+5V" H 5265 4223 50  0000 C CNN
F 2 "" H 5250 4050 50  0001 C CNN
F 3 "" H 5250 4050 50  0001 C CNN
	1    5250 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR044
U 1 1 5C9FC3B2
P 3800 8600
F 0 "#PWR044" H 3800 8350 50  0001 C CNN
F 1 "GND" H 3805 8427 50  0000 C CNN
F 2 "" H 3800 8600 50  0001 C CNN
F 3 "" H 3800 8600 50  0001 C CNN
	1    3800 8600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5C9FC446
P 5400 8600
F 0 "D2" V 5438 8483 50  0000 R CNN
F 1 "LED" V 5347 8483 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5400 8600 50  0001 C CNN
F 3 "~" H 5400 8600 50  0001 C CNN
	1    5400 8600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR043
U 1 1 5C9FC4E2
P 5400 8850
F 0 "#PWR043" H 5400 8600 50  0001 C CNN
F 1 "GND" H 5405 8677 50  0000 C CNN
F 2 "" H 5400 8850 50  0001 C CNN
F 3 "" H 5400 8850 50  0001 C CNN
	1    5400 8850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5C9FC4F7
P 5400 8100
F 0 "R18" H 5200 8150 50  0000 L CNN
F 1 "330" H 5150 8050 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 5330 8100 50  0001 C CNN
F 3 "~" H 5400 8100 50  0001 C CNN
	1    5400 8100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5C9FC54B
P 6800 3300
F 0 "C1" H 6915 3346 50  0000 L CNN
F 1 "100n" H 6915 3255 50  0000 L CNN
F 2 "obbo_footprints:C_0805K" H 6838 3150 50  0001 C CNN
F 3 "~" H 6800 3300 50  0001 C CNN
	1    6800 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5C9FC5BD
P 7200 3300
F 0 "R12" H 7270 3346 50  0000 L CNN
F 1 "4k7" H 7270 3255 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 7130 3300 50  0001 C CNN
F 3 "~" H 7200 3300 50  0001 C CNN
	1    7200 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5C9FC603
P 7550 3050
F 0 "R10" V 7343 3050 50  0000 C CNN
F 1 "22k*" V 7434 3050 50  0000 C CNN
F 2 "obbo_footprints:R_0805K" V 7480 3050 50  0001 C CNN
F 3 "~" H 7550 3050 50  0001 C CNN
	1    7550 3050
	0    1    1    0   
$EndComp
$Comp
L Regulator_Switching:LM2576HVS-5 U1
U 1 1 5C9FC775
P 9550 3150
F 0 "U1" H 9550 3517 50  0000 C CNN
F 1 "LM2576HVS-5" H 9550 3426 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-263-5_TabPin6" H 9550 2900 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2576.pdf" H 9550 3150 50  0001 C CNN
	1    9550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 8600 3800 8400
Wire Wire Line
	3700 8250 3700 8400
Wire Wire Line
	3700 8400 3800 8400
Connection ~ 3800 8400
Wire Wire Line
	3800 8400 3800 8250
Wire Wire Line
	5250 4050 5250 4100
$Comp
L power:+5V #PWR035
U 1 1 5CA79609
P 3800 4100
F 0 "#PWR035" H 3800 3950 50  0001 C CNN
F 1 "+5V" H 3815 4273 50  0000 C CNN
F 2 "" H 3800 4100 50  0001 C CNN
F 3 "" H 3800 4100 50  0001 C CNN
	1    3800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5450 3700 4900
$Comp
L power:GND #PWR037
U 1 1 5CA7A567
P 4050 5300
F 0 "#PWR037" H 4050 5050 50  0001 C CNN
F 1 "GND" H 4055 5127 50  0000 C CNN
F 2 "" H 4050 5300 50  0001 C CNN
F 3 "" H 4050 5300 50  0001 C CNN
	1    4050 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5CA7B35D
P 4350 3100
F 0 "R1" H 4420 3146 50  0000 L CNN
F 1 "330" H 4420 3055 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 4280 3100 50  0001 C CNN
F 3 "~" H 4350 3100 50  0001 C CNN
	1    4350 3100
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J8
U 1 1 5CA7B4CA
P 3700 3200
F 0 "J8" H 3620 2875 50  0000 C CNN
F 1 "CH1" H 3620 2966 50  0000 C CNN
F 2 "obbo_footprints:PinHeader_1x03_P2.54mm_Vertical_PAD" H 3700 3200 50  0001 C CNN
F 3 "~" H 3700 3200 50  0001 C CNN
	1    3700 3200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5CA7CDE8
P 4100 3500
F 0 "#PWR019" H 4100 3250 50  0001 C CNN
F 1 "GND" H 4105 3327 50  0000 C CNN
F 2 "" H 4100 3500 50  0001 C CNN
F 3 "" H 4100 3500 50  0001 C CNN
	1    4100 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3300 3900 3300
$Comp
L power:+5V #PWR03
U 1 1 5CA7DC39
P 4100 2950
F 0 "#PWR03" H 4100 2800 50  0001 C CNN
F 1 "+5V" H 4115 3123 50  0000 C CNN
F 2 "" H 4100 2950 50  0001 C CNN
F 3 "" H 4100 2950 50  0001 C CNN
	1    4100 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4550 5250 4550
$Comp
L Device:C C5
U 1 1 5CA88F73
P 3350 5100
F 0 "C5" H 3465 5146 50  0000 L CNN
F 1 "100n" H 3465 5055 50  0000 L CNN
F 2 "obbo_footprints:C_Disc_D5.0mm_W2.5mm_P5.00mm_PAD" H 3388 4950 50  0001 C CNN
F 3 "~" H 3350 5100 50  0001 C CNN
	1    3350 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR036
U 1 1 5CA9F42D
P 5400 5800
F 0 "#PWR036" H 5400 5650 50  0001 C CNN
F 1 "+5V" H 5415 5973 50  0000 C CNN
F 2 "" H 5400 5800 50  0001 C CNN
F 3 "" H 5400 5800 50  0001 C CNN
	1    5400 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 6350 5400 5800
Text GLabel 5950 3050 0    50   Output ~ 0
V_TEST
Wire Wire Line
	7200 3150 7200 3050
Connection ~ 7200 3050
Wire Wire Line
	7200 3050 7400 3050
Wire Wire Line
	6800 3150 6800 3050
Connection ~ 6800 3050
Wire Wire Line
	6800 3050 7200 3050
$Comp
L power:GND #PWR021
U 1 1 5CAA547D
P 6800 3550
F 0 "#PWR021" H 6800 3300 50  0001 C CNN
F 1 "GND" H 6805 3377 50  0000 C CNN
F 2 "" H 6800 3550 50  0001 C CNN
F 3 "" H 6800 3550 50  0001 C CNN
	1    6800 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5CAA5500
P 7200 3550
F 0 "#PWR022" H 7200 3300 50  0001 C CNN
F 1 "GND" H 7205 3377 50  0000 C CNN
F 2 "" H 7200 3550 50  0001 C CNN
F 3 "" H 7200 3550 50  0001 C CNN
	1    7200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3550 7200 3450
Wire Wire Line
	6800 3550 6800 3450
Text GLabel 4450 6750 2    50   Input ~ 0
V_TEST
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 5CAE8879
P 14300 2800
F 0 "J7" V 14266 2612 50  0000 R CNN
F 1 "BAT 12V" V 14175 2612 50  0000 R CNN
F 2 "obbo_footprints:TerminalBlock_Degson_DG128-5.0-02P" H 14300 2800 50  0001 C CNN
F 3 "~" H 14300 2800 50  0001 C CNN
	1    14300 2800
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR02
U 1 1 5CAE8A23
P 12900 2650
F 0 "#PWR02" H 12900 2500 50  0001 C CNN
F 1 "+12V" H 12915 2823 50  0000 C CNN
F 2 "" H 12900 2650 50  0001 C CNN
F 3 "" H 12900 2650 50  0001 C CNN
	1    12900 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5CAE8A7C
P 14400 3200
F 0 "#PWR04" H 14400 2950 50  0001 C CNN
F 1 "GND" H 14405 3027 50  0000 C CNN
F 2 "" H 14400 3200 50  0001 C CNN
F 3 "" H 14400 3200 50  0001 C CNN
	1    14400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	14400 3200 14400 3000
Wire Wire Line
	14300 3000 14300 3050
$Comp
L power:GND #PWR025
U 1 1 5CAF7C68
P 9550 3750
F 0 "#PWR025" H 9550 3500 50  0001 C CNN
F 1 "GND" H 9555 3577 50  0000 C CNN
F 2 "" H 9550 3750 50  0001 C CNN
F 3 "" H 9550 3750 50  0001 C CNN
	1    9550 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5CAF7CC1
P 8950 4100
F 0 "#PWR024" H 8950 3850 50  0001 C CNN
F 1 "GND" H 8955 3927 50  0000 C CNN
F 2 "" H 8950 4100 50  0001 C CNN
F 3 "" H 8950 4100 50  0001 C CNN
	1    8950 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 4100 8950 3750
Wire Wire Line
	8950 3250 9050 3250
Wire Wire Line
	9550 3450 9550 3750
$Comp
L power:GND #PWR027
U 1 1 5CB3B78C
P 10100 3750
F 0 "#PWR027" H 10100 3500 50  0001 C CNN
F 1 "GND" H 10105 3577 50  0000 C CNN
F 2 "" H 10100 3750 50  0001 C CNN
F 3 "" H 10100 3750 50  0001 C CNN
	1    10100 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5CB3B7ED
P 10750 3750
F 0 "#PWR028" H 10750 3500 50  0001 C CNN
F 1 "GND" H 10755 3577 50  0000 C CNN
F 2 "" H 10750 3750 50  0001 C CNN
F 3 "" H 10750 3750 50  0001 C CNN
	1    10750 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 5CB3BA7D
P 11550 2900
F 0 "#PWR018" H 11550 2750 50  0001 C CNN
F 1 "+5V" H 11565 3073 50  0000 C CNN
F 2 "" H 11550 2900 50  0001 C CNN
F 3 "" H 11550 2900 50  0001 C CNN
	1    11550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 3400 10750 3250
Wire Wire Line
	10050 3250 10100 3250
Connection ~ 10100 3250
Wire Wire Line
	10750 3700 10750 3750
Wire Wire Line
	5400 8250 5400 8450
Wire Wire Line
	5400 8750 5400 8850
$Comp
L power:GND #PWR041
U 1 1 5CBB5CC9
P 10750 7850
F 0 "#PWR041" H 10750 7600 50  0001 C CNN
F 1 "GND" H 10755 7677 50  0000 C CNN
F 2 "" H 10750 7850 50  0001 C CNN
F 3 "" H 10750 7850 50  0001 C CNN
	1    10750 7850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J13
U 1 1 5CBB5F5B
P 10700 6800
F 0 "J13" V 10666 6612 50  0000 R CNN
F 1 "MOTOR" V 10575 6612 50  0000 R CNN
F 2 "obbo_footprints:TerminalBlock_Degson_DG128-5.0-02P" H 10700 6800 50  0001 C CNN
F 3 "~" H 10700 6800 50  0001 C CNN
	1    10700 6800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R14
U 1 1 5CBDA7AE
P 13350 6550
F 0 "R14" H 13420 6596 50  0000 L CNN
F 1 "22k" H 13420 6505 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 13280 6550 50  0001 C CNN
F 3 "~" H 13350 6550 50  0001 C CNN
	1    13350 6550
	-1   0    0    1   
$EndComp
Wire Wire Line
	13350 6700 13350 6750
Connection ~ 13350 6750
Wire Wire Line
	12000 6750 12950 6750
Connection ~ 12950 6750
Wire Wire Line
	12950 6750 13350 6750
Wire Wire Line
	13350 6400 13350 6150
Wire Wire Line
	12600 7050 11650 7050
Wire Wire Line
	10800 7050 10800 7000
Wire Wire Line
	12600 7050 12600 7250
Connection ~ 11650 7050
Wire Wire Line
	11650 7050 10800 7050
Wire Wire Line
	11650 7250 11650 7050
Wire Wire Line
	12600 7650 12600 7750
Wire Wire Line
	12600 7750 11650 7750
Wire Wire Line
	11650 7750 11650 7650
Connection ~ 11650 7750
$Comp
L power:GND #PWR038
U 1 1 5CC5E214
P 13350 7650
F 0 "#PWR038" H 13350 7400 50  0001 C CNN
F 1 "GND" H 13355 7477 50  0000 C CNN
F 2 "" H 13350 7650 50  0001 C CNN
F 3 "" H 13350 7650 50  0001 C CNN
	1    13350 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	13350 7650 13350 7250
Wire Wire Line
	8950 7050 9900 7050
Wire Wire Line
	10700 7050 10700 7000
Connection ~ 9900 7050
Wire Wire Line
	9900 7050 10700 7050
Wire Wire Line
	9900 7250 9900 7050
Wire Wire Line
	8950 7250 8950 7050
Connection ~ 9900 6150
Wire Wire Line
	8950 7650 8950 7750
Wire Wire Line
	8950 7750 9900 7750
Wire Wire Line
	9900 7650 9900 7750
Connection ~ 9900 7750
Wire Wire Line
	9900 7750 10750 7750
$Comp
L Device:R R13
U 1 1 5CCDBACE
P 8200 6550
F 0 "R13" H 8270 6596 50  0000 L CNN
F 1 "22k" H 8270 6505 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 8130 6550 50  0001 C CNN
F 3 "~" H 8200 6550 50  0001 C CNN
	1    8200 6550
	-1   0    0    1   
$EndComp
Wire Wire Line
	8200 6400 8200 6150
Wire Wire Line
	8600 6750 8200 6750
Connection ~ 8200 6750
Wire Wire Line
	8200 6750 8200 6700
Wire Wire Line
	9550 6750 8600 6750
Connection ~ 8600 6750
$Comp
L power:GND #PWR040
U 1 1 5CD1FD7C
P 8200 7650
F 0 "#PWR040" H 8200 7400 50  0001 C CNN
F 1 "GND" H 8205 7477 50  0000 C CNN
F 2 "" H 8200 7650 50  0001 C CNN
F 3 "" H 8200 7650 50  0001 C CNN
	1    8200 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 7650 8200 7250
$Comp
L Device:R R22
U 1 1 5CD49E1F
P 7950 8150
F 0 "R22" H 8020 8196 50  0000 L CNN
F 1 "220" H 8020 8105 50  0000 L CNN
F 2 "obbo_footprints:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_PAD" V 7880 8150 50  0001 C CNN
F 3 "~" H 7950 8150 50  0001 C CNN
	1    7950 8150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R20
U 1 1 5CD49F23
P 13800 6550
F 0 "R20" H 13870 6596 50  0000 L CNN
F 1 "220" H 13870 6505 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 13730 6550 50  0001 C CNN
F 3 "~" H 13800 6550 50  0001 C CNN
	1    13800 6550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R23
U 1 1 5CD49FB5
P 11700 8150
F 0 "R23" H 11770 8196 50  0000 L CNN
F 1 "220" H 11770 8105 50  0000 L CNN
F 2 "obbo_footprints:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_PAD" V 11630 8150 50  0001 C CNN
F 3 "~" H 11700 8150 50  0001 C CNN
	1    11700 8150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8600 8150 8100 8150
Wire Wire Line
	9550 8150 8600 8150
Connection ~ 8600 8150
Wire Wire Line
	12950 8150 12000 8150
Connection ~ 12000 8150
Wire Wire Line
	12000 8150 11850 8150
$Comp
L power:GND #PWR045
U 1 1 5CF093DF
P 4450 8850
F 0 "#PWR045" H 4450 8600 50  0001 C CNN
F 1 "GND" H 4455 8677 50  0000 C CNN
F 2 "" H 4450 8850 50  0001 C CNN
F 3 "" H 4450 8850 50  0001 C CNN
	1    4450 8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 8850 4450 8800
$Comp
L power:GND #PWR039
U 1 1 5CF9BBEF
P 7600 7650
F 0 "#PWR039" H 7600 7400 50  0001 C CNN
F 1 "GND" H 7605 7477 50  0000 C CNN
F 2 "" H 7600 7650 50  0001 C CNN
F 3 "" H 7600 7650 50  0001 C CNN
	1    7600 7650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R24
U 1 1 5CFBA67F
P 8600 8500
F 0 "R24" H 8670 8546 50  0000 L CNN
F 1 "22k" H 8670 8455 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 8530 8500 50  0001 C CNN
F 3 "~" H 8600 8500 50  0001 C CNN
	1    8600 8500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR046
U 1 1 5CFBA77D
P 8600 8700
F 0 "#PWR046" H 8600 8450 50  0001 C CNN
F 1 "GND" H 8605 8527 50  0000 C CNN
F 2 "" H 8600 8700 50  0001 C CNN
F 3 "" H 8600 8700 50  0001 C CNN
	1    8600 8700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 8350 8600 8150
Wire Wire Line
	8600 8700 8600 8650
$Comp
L Device:R R25
U 1 1 5CFDA102
P 12000 8500
F 0 "R25" H 12070 8546 50  0000 L CNN
F 1 "22k" H 12070 8455 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 11930 8500 50  0001 C CNN
F 3 "~" H 12000 8500 50  0001 C CNN
	1    12000 8500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR047
U 1 1 5CFDA1BC
P 12000 8700
F 0 "#PWR047" H 12000 8450 50  0001 C CNN
F 1 "GND" H 12005 8527 50  0000 C CNN
F 2 "" H 12000 8700 50  0001 C CNN
F 3 "" H 12000 8700 50  0001 C CNN
	1    12000 8700
	1    0    0    -1  
$EndComp
Wire Wire Line
	12000 8700 12000 8650
Wire Wire Line
	12000 8350 12000 8150
$Comp
L Device:R R21
U 1 1 5CFFA521
P 13800 7350
F 0 "R21" H 13870 7396 50  0000 L CNN
F 1 "22k" H 13870 7305 50  0000 L CNN
F 2 "obbo_footprints:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_PAD" V 13730 7350 50  0001 C CNN
F 3 "~" H 13800 7350 50  0001 C CNN
	1    13800 7350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 5D01AABA
P 13800 7650
F 0 "#PWR042" H 13800 7400 50  0001 C CNN
F 1 "GND" H 13805 7477 50  0000 C CNN
F 2 "" H 13800 7650 50  0001 C CNN
F 3 "" H 13800 7650 50  0001 C CNN
	1    13800 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	13800 7650 13800 7500
$Comp
L power:+5V #PWR026
U 1 1 5D134EE5
P 3700 4800
F 0 "#PWR026" H 3700 4650 50  0001 C CNN
F 1 "+5V" H 3715 4973 50  0000 C CNN
F 2 "" H 3700 4800 50  0001 C CNN
F 3 "" H 3700 4800 50  0001 C CNN
	1    3700 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5D1CF533
P 3350 5300
F 0 "#PWR030" H 3350 5050 50  0001 C CNN
F 1 "GND" H 3355 5127 50  0000 C CNN
F 2 "" H 3350 5300 50  0001 C CNN
F 3 "" H 3350 5300 50  0001 C CNN
	1    3350 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5300 3350 5250
$Comp
L Device:Crystal Y1
U 1 1 5D2142CF
P 2600 6000
F 0 "Y1" V 2554 6131 50  0000 L CNN
F 1 "16MHz" V 2645 6131 50  0000 L CNN
F 2 "obbo_footprints:Crystal_SMD_HC49-SD_HandSoldering" H 2600 6000 50  0001 C CNN
F 3 "~" H 2600 6000 50  0001 C CNN
	1    2600 6000
	0    1    1    0   
$EndComp
Wire Wire Line
	3100 6150 2600 6150
Wire Wire Line
	3100 5950 3000 5950
Wire Wire Line
	3000 5950 3000 5850
Wire Wire Line
	3000 5850 2600 5850
$Comp
L power:GND #PWR029
U 1 1 5D24B0FF
P 5450 5100
F 0 "#PWR029" H 5450 4850 50  0001 C CNN
F 1 "GND" H 5455 4927 50  0000 C CNN
F 2 "" H 5450 5100 50  0001 C CNN
F 3 "" H 5450 5100 50  0001 C CNN
	1    5450 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5C9FC303
P 4050 5100
F 0 "C8" H 4165 5146 50  0000 L CNN
F 1 "100n" H 4165 5055 50  0000 L CNN
F 2 "obbo_footprints:C_Disc_D5.0mm_W2.5mm_P5.00mm_PAD" H 4088 4950 50  0001 C CNN
F 3 "~" H 4050 5100 50  0001 C CNN
	1    4050 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5D24B264
P 2300 6150
F 0 "C7" H 2415 6196 50  0000 L CNN
F 1 "15p" H 2415 6105 50  0000 L CNN
F 2 "obbo_footprints:C_0805K" H 2338 6000 50  0001 C CNN
F 3 "~" H 2300 6150 50  0001 C CNN
	1    2300 6150
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 5D24B316
P 2100 5850
F 0 "C6" H 2215 5896 50  0000 L CNN
F 1 "15p" H 2215 5805 50  0000 L CNN
F 2 "obbo_footprints:C_0805K" H 2138 5700 50  0001 C CNN
F 3 "~" H 2100 5850 50  0001 C CNN
	1    2100 5850
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR032
U 1 1 5D24B3C2
P 1800 5900
F 0 "#PWR032" H 1800 5650 50  0001 C CNN
F 1 "GND" H 1805 5727 50  0000 C CNN
F 2 "" H 1800 5900 50  0001 C CNN
F 3 "" H 1800 5900 50  0001 C CNN
	1    1800 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR034
U 1 1 5D24B45B
P 2000 6200
F 0 "#PWR034" H 2000 5950 50  0001 C CNN
F 1 "GND" H 2005 6027 50  0000 C CNN
F 2 "" H 2000 6200 50  0001 C CNN
F 3 "" H 2000 6200 50  0001 C CNN
	1    2000 6200
	1    0    0    -1  
$EndComp
Connection ~ 2600 5850
Wire Wire Line
	4500 3100 4700 3100
Wire Wire Line
	5250 4400 5250 4550
Connection ~ 5250 4550
Wire Wire Line
	5450 5100 5450 4900
Wire Wire Line
	5450 4600 5450 4550
Wire Wire Line
	5450 4550 5250 4550
Wire Wire Line
	3000 5750 3100 5750
Wire Wire Line
	3000 4550 3000 5750
Wire Wire Line
	3350 4950 3350 4900
Wire Wire Line
	3350 4900 3700 4900
Wire Wire Line
	2450 6150 2600 6150
Connection ~ 2600 6150
Wire Wire Line
	2150 6150 2000 6150
Wire Wire Line
	2000 6150 2000 6200
Wire Wire Line
	2250 5850 2600 5850
Wire Wire Line
	1950 5850 1800 5850
Wire Wire Line
	1800 5850 1800 5900
$Comp
L Connector_Generic:Conn_01x03 J14
U 1 1 5CB6DDD7
P 5700 7050
F 0 "J14" H 5620 6725 50  0000 C CNN
F 1 "Serial" H 5620 6816 50  0000 C CNN
F 2 "obbo_footprints:PinHeader_1x03_P2.54mm_Vertical_PAD" H 5700 7050 50  0001 C CNN
F 3 "~" H 5700 7050 50  0001 C CNN
	1    5700 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 7150 5050 7150
Wire Wire Line
	5050 7150 5050 6950
Wire Wire Line
	4300 7250 5150 7250
Wire Wire Line
	5150 7250 5150 7050
$Comp
L power:GND #PWR048
U 1 1 5CB98F2F
P 5300 7200
F 0 "#PWR048" H 5300 6950 50  0001 C CNN
F 1 "GND" H 5305 7027 50  0000 C CNN
F 2 "" H 5300 7200 50  0001 C CNN
F 3 "" H 5300 7200 50  0001 C CNN
	1    5300 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 7200 5300 7150
Text Label 5800 6950 0    50   ~ 0
Rx
Text Label 5800 7050 0    50   ~ 0
Tx
Text Label 5800 7150 0    50   ~ 0
GND
Text GLabel 10600 5850 0    50   Input ~ 0
V_BAT
Text GLabel 13700 2600 0    50   Input ~ 0
V_BAT
Wire Wire Line
	13700 2600 13900 2600
Wire Wire Line
	13900 2600 13900 3050
Wire Wire Line
	10600 5850 10750 5850
$Comp
L Device:R R15
U 1 1 5D7F9A1B
P 11550 3450
F 0 "R15" V 11343 3450 50  0000 C CNN
F 1 "10k" V 11434 3450 50  0000 C CNN
F 2 "obbo_footprints:R_0805K" V 11480 3450 50  0001 C CNN
F 3 "~" H 11550 3450 50  0001 C CNN
	1    11550 3450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R26
U 1 1 5D7F9B13
P 11550 3950
F 0 "R26" V 11343 3950 50  0000 C CNN
F 1 "3k3" V 11434 3950 50  0000 C CNN
F 2 "obbo_footprints:R_0805K" V 11480 3950 50  0001 C CNN
F 3 "~" H 11550 3950 50  0001 C CNN
	1    11550 3950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5D7F9C6B
P 11550 4250
F 0 "#PWR01" H 11550 4000 50  0001 C CNN
F 1 "GND" H 11555 4077 50  0000 C CNN
F 2 "" H 11550 4250 50  0001 C CNN
F 3 "" H 11550 4250 50  0001 C CNN
	1    11550 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 2900 11550 3250
Connection ~ 11550 3250
Wire Wire Line
	11550 3250 11550 3300
Wire Wire Line
	11550 3600 11550 3700
Wire Wire Line
	11550 4100 11550 4200
Wire Wire Line
	11350 3050 11350 3700
Connection ~ 11550 3700
Wire Wire Line
	11550 3700 11550 3800
Wire Wire Line
	11350 3700 11550 3700
$Comp
L Device:R R16
U 1 1 5D8E2958
P 11350 3950
F 0 "R16" V 11143 3950 50  0000 C CNN
F 1 "100k*" V 11234 3950 50  0000 C CNN
F 2 "obbo_footprints:R_0805K" V 11280 3950 50  0001 C CNN
F 3 "~" H 11350 3950 50  0001 C CNN
	1    11350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	11350 3800 11350 3700
Connection ~ 11350 3700
Wire Wire Line
	11350 4100 11350 4200
Wire Wire Line
	11350 4200 11550 4200
Connection ~ 11550 4200
Wire Wire Line
	11550 4200 11550 4250
Wire Wire Line
	8200 6150 8950 6150
Wire Wire Line
	9900 6150 10750 6150
Wire Wire Line
	11650 6250 11650 6150
Connection ~ 11650 6150
Wire Wire Line
	11650 6150 12600 6150
Wire Wire Line
	12600 6250 12600 6150
Connection ~ 12600 6150
Wire Wire Line
	12600 6150 13350 6150
Wire Wire Line
	12600 6650 12600 7050
Connection ~ 12600 7050
Wire Wire Line
	11650 6650 11650 7050
Wire Wire Line
	9900 6250 9900 6150
Wire Wire Line
	9900 6650 9900 7050
Wire Wire Line
	8950 6250 8950 6150
Connection ~ 8950 6150
Wire Wire Line
	8950 6150 9900 6150
Wire Wire Line
	8950 6650 8950 7050
Connection ~ 8950 7050
Wire Wire Line
	8200 6750 8200 6850
Wire Wire Line
	13350 6750 13350 6850
Wire Wire Line
	10750 7850 10750 7750
Connection ~ 10750 7750
Wire Wire Line
	10750 7750 11650 7750
Wire Wire Line
	10750 6150 10750 5850
Connection ~ 10750 6150
Wire Wire Line
	10750 6150 11650 6150
Wire Wire Line
	4300 6050 5500 6050
Wire Wire Line
	4300 6150 5500 6150
Wire Wire Line
	4300 6250 5500 6250
Wire Wire Line
	5250 6550 5500 6550
Wire Wire Line
	5250 4550 5250 6550
Wire Wire Line
	5400 6350 5500 6350
Wire Wire Line
	8600 6450 8600 6750
Wire Wire Line
	12950 6450 12950 6750
Wire Wire Line
	12000 6450 12000 6750
Wire Wire Line
	9550 6450 9550 6750
Wire Wire Line
	8600 7450 8600 8150
Wire Wire Line
	9550 7450 9550 8150
Wire Wire Line
	12000 7450 12000 8150
Wire Wire Line
	12950 7450 12950 8150
Wire Wire Line
	10100 3250 10100 3400
Wire Wire Line
	10050 3050 11350 3050
Wire Wire Line
	10750 3250 11550 3250
Connection ~ 10750 3250
Wire Wire Line
	4650 7850 4650 8250
Wire Wire Line
	5150 6450 5500 6450
Wire Wire Line
	5400 7950 5400 7450
Wire Wire Line
	5400 7450 4300 7450
Wire Wire Line
	3700 4800 3700 4900
Connection ~ 3700 4900
Wire Wire Line
	3800 4100 3800 4150
Wire Wire Line
	3800 4450 3800 4900
Wire Wire Line
	4050 5250 4050 5300
Wire Wire Line
	4050 4950 4050 4900
Wire Wire Line
	4050 4900 3800 4900
Connection ~ 3800 4900
Wire Wire Line
	3800 4900 3800 5450
$Comp
L Device:C C9
U 1 1 5D9522B3
P 2500 6750
F 0 "C9" H 2615 6796 50  0000 L CNN
F 1 "100n" H 2615 6705 50  0000 L CNN
F 2 "obbo_footprints:C_0805K" H 2538 6600 50  0001 C CNN
F 3 "~" H 2500 6750 50  0001 C CNN
	1    2500 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D952713
P 2500 7100
F 0 "#PWR0102" H 2500 6850 50  0001 C CNN
F 1 "GND" H 2505 6927 50  0000 C CNN
F 2 "" H 2500 7100 50  0001 C CNN
F 3 "" H 2500 7100 50  0001 C CNN
	1    2500 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 6900 2500 7100
Wire Wire Line
	2500 6350 3100 6350
Wire Wire Line
	2500 6350 2500 6600
Wire Wire Line
	7700 3050 7800 3050
$Comp
L Device:C C10
U 1 1 5D3D1E2D
P 7800 3300
F 0 "C10" H 7915 3346 50  0000 L CNN
F 1 "100n" H 7915 3255 50  0000 L CNN
F 2 "obbo_footprints:C_Disc_D5.0mm_W2.5mm_P5.00mm_PAD" H 7838 3150 50  0001 C CNN
F 3 "~" H 7800 3300 50  0001 C CNN
	1    7800 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5D3D224A
P 7800 3550
F 0 "#PWR0103" H 7800 3300 50  0001 C CNN
F 1 "GND" H 7805 3377 50  0000 C CNN
F 2 "" H 7800 3550 50  0001 C CNN
F 3 "" H 7800 3550 50  0001 C CNN
	1    7800 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3550 7800 3450
Wire Wire Line
	7800 3150 7800 3050
Connection ~ 7800 3050
Wire Wire Line
	5150 6450 5150 6550
$Comp
L power:GND #PWR031
U 1 1 5CA9F3FA
P 5150 6550
F 0 "#PWR031" H 5150 6300 50  0001 C CNN
F 1 "GND" H 5155 6377 50  0000 C CNN
F 2 "" H 5150 6550 50  0001 C CNN
F 3 "" H 5150 6550 50  0001 C CNN
	1    5150 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3300 4100 3500
Wire Wire Line
	7600 6150 7450 6150
Wire Wire Line
	4450 5950 4300 5950
Wire Wire Line
	7600 6700 7600 7050
$Comp
L Device:R R17
U 1 1 5CD4A33E
P 7600 6550
F 0 "R17" H 7670 6596 50  0000 L CNN
F 1 "220" H 7670 6505 50  0000 L CNN
F 2 "obbo_footprints:R_0805K" V 7530 6550 50  0001 C CNN
F 3 "~" H 7600 6550 50  0001 C CNN
	1    7600 6550
	-1   0    0    1   
$EndComp
Wire Wire Line
	7600 6400 7600 6150
Wire Wire Line
	7600 7200 7600 7050
Wire Wire Line
	7600 7650 7600 7500
$Comp
L Device:R R19
U 1 1 5CF9BB0C
P 7600 7350
F 0 "R19" H 7670 7396 50  0000 L CNN
F 1 "22k" H 7670 7305 50  0000 L CNN
F 2 "obbo_footprints:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_PAD" V 7530 7350 50  0001 C CNN
F 3 "~" H 7600 7350 50  0001 C CNN
	1    7600 7350
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 5850 4300 5850
Wire Wire Line
	13800 6700 13800 7050
$Comp
L power:GND #PWR0101
U 1 1 5D73C52A
P 6300 3550
F 0 "#PWR0101" H 6300 3300 50  0001 C CNN
F 1 "GND" H 6305 3377 50  0000 C CNN
F 2 "" H 6300 3550 50  0001 C CNN
F 3 "" H 6300 3550 50  0001 C CNN
	1    6300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 3050 14300 3050
Wire Wire Line
	4300 6650 4450 6650
Wire Wire Line
	4300 6550 4450 6550
Wire Wire Line
	4450 6750 4300 6750
Connection ~ 13900 3050
$Comp
L power:GND #PWR0104
U 1 1 5D5F10A1
P 6100 5100
F 0 "#PWR0104" H 6100 4850 50  0001 C CNN
F 1 "GND" H 6105 4927 50  0000 C CNN
F 2 "" H 6100 5100 50  0001 C CNN
F 3 "" H 6100 5100 50  0001 C CNN
	1    6100 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4600 6100 4550
Wire Wire Line
	6100 4550 5450 4550
Connection ~ 5450 4550
Wire Wire Line
	6100 5100 6100 5000
$Comp
L Diode:B340 D1
U 1 1 5D65965B
P 10100 3550
F 0 "D1" V 10054 3629 50  0000 L CNN
F 1 "B340" V 10145 3629 50  0000 L CNN
F 2 "Diode_SMD:D_SMB" H 10100 3375 50  0001 C CNN
F 3 "http://www.jameco.com/Jameco/Products/ProdDS/1538777.pdf" H 10100 3550 50  0001 C CNN
	1    10100 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	10100 3750 10100 3700
$Comp
L Device:CP C12
U 1 1 5D6D5427
P 10750 3550
F 0 "C12" H 10868 3596 50  0000 L CNN
F 1 "1000u/10V" H 10868 3505 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_10x10" H 10788 3400 50  0001 C CNN
F 3 "~" H 10750 3550 50  0001 C CNN
	1    10750 3550
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS138 Q1
U 1 1 5D6F3C15
P 8100 7050
F 0 "Q1" H 8306 7096 50  0000 L CNN
F 1 "BSS138" H 8306 7005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8300 6975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 8100 7050 50  0001 L CNN
	1    8100 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 7050 7600 7050
Connection ~ 7600 7050
$Comp
L Transistor_FET:BSS138 Q2
U 1 1 5D7088B2
P 13450 7050
F 0 "Q2" H 13656 7096 50  0000 L CNN
F 1 "BSS138" H 13656 7005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 13650 6975 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 13450 7050 50  0001 L CNN
	1    13450 7050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	13650 7050 13800 7050
Connection ~ 13800 7050
$Comp
L obbo_Transistors:AOD403 Q3
U 1 1 5D77E093
P 8950 6450
F 0 "Q3" H 9058 6397 60  0000 L CNN
F 1 "AOD403" H 9058 6503 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 9150 6650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD403.pdf" H 9150 6750 60  0001 L CNN
	1    8950 6450
	1    0    0    1   
$EndComp
Wire Wire Line
	8650 6450 8600 6450
$Comp
L obbo_Transistors:AOD403 Q4
U 1 1 5D7C9BD1
P 9900 6450
F 0 "Q4" H 10008 6397 60  0000 L CNN
F 1 "AOD403" H 10008 6503 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 10100 6650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD403.pdf" H 10100 6750 60  0001 L CNN
	1    9900 6450
	1    0    0    1   
$EndComp
Wire Wire Line
	9600 6450 9550 6450
$Comp
L obbo_Transistors:AOD403 Q5
U 1 1 5D7ED79D
P 11650 6450
F 0 "Q5" H 11758 6397 60  0000 L CNN
F 1 "AOD403" H 11758 6503 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 11850 6650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD403.pdf" H 11850 6750 60  0001 L CNN
	1    11650 6450
	-1   0    0    1   
$EndComp
$Comp
L obbo_Transistors:AOD403 Q6
U 1 1 5D7FD9E7
P 12600 6450
F 0 "Q6" H 12708 6397 60  0000 L CNN
F 1 "AOD403" H 12708 6503 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 12800 6650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD403.pdf" H 12800 6750 60  0001 L CNN
	1    12600 6450
	-1   0    0    1   
$EndComp
Wire Wire Line
	11950 6450 12000 6450
Wire Wire Line
	12950 6450 12900 6450
$Comp
L obbo_Transistors:AOD240 Q7
U 1 1 5D83EF91
P 8950 7450
F 0 "Q7" H 9058 7503 60  0000 L CNN
F 1 "AOD240" H 9058 7397 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 9150 7650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD240.pdf" H 9150 7750 60  0001 L CNN
	1    8950 7450
	1    0    0    -1  
$EndComp
$Comp
L obbo_Transistors:AOD240 Q8
U 1 1 5D840B77
P 9900 7450
F 0 "Q8" H 10008 7503 60  0000 L CNN
F 1 "AOD240" H 10008 7397 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 10100 7650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD240.pdf" H 10100 7750 60  0001 L CNN
	1    9900 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 7450 9550 7450
Wire Wire Line
	8650 7450 8600 7450
$Comp
L obbo_Transistors:AOD240 Q9
U 1 1 5D860B1A
P 11650 7450
F 0 "Q9" H 11758 7503 60  0000 L CNN
F 1 "AOD240" H 11758 7397 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 11850 7650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD240.pdf" H 11850 7750 60  0001 L CNN
	1    11650 7450
	-1   0    0    -1  
$EndComp
$Comp
L obbo_Transistors:AOD240 Q10
U 1 1 5D8712FA
P 12600 7450
F 0 "Q10" H 12708 7503 60  0000 L CNN
F 1 "AOD240" H 12708 7397 60  0000 L CNN
F 2 "obbo_footprints:TO-252-2-DPAK" H 12800 7650 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOD240.pdf" H 12800 7750 60  0001 L CNN
	1    12600 7450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	12900 7450 12950 7450
Wire Wire Line
	11950 7450 12000 7450
$Comp
L Device:D_Zener D3
U 1 1 5D9670F1
P 6300 3300
F 0 "D3" V 6254 3379 50  0000 L CNN
F 1 "4V7" V 6345 3379 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 6300 3300 50  0001 C CNN
F 3 "~" H 6300 3300 50  0001 C CNN
	1    6300 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 3050 6300 3050
Wire Wire Line
	6300 3150 6300 3050
Connection ~ 6300 3050
Wire Wire Line
	6300 3050 6800 3050
Wire Wire Line
	6300 3450 6300 3550
Wire Wire Line
	4100 3200 3900 3200
Wire Wire Line
	4100 2950 4100 3200
Wire Wire Line
	4200 3100 3900 3100
$Comp
L obbo_Transistors:AO6401A Q12
U 1 1 5D6D4DC2
P 13400 3050
F 0 "Q12" V 13667 3050 60  0000 C CNN
F 1 "AO6401A" V 13561 3050 60  0000 C CNN
F 2 "Package_SO:TSOP-6_1.65x3.05mm_P0.95mm" H 13600 3250 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AO4485.pdf" H 13600 3350 60  0001 L CNN
	1    13400 3050
	0    1    -1   0   
$EndComp
$Comp
L Device:D_Zener D4
U 1 1 5D6D6A63
P 12900 3300
F 0 "D4" V 12854 3379 50  0000 L CNN
F 1 "8v2" V 12945 3379 50  0000 L CNN
F 2 "Diode_SMD:D_MiniMELF" H 12900 3300 50  0001 C CNN
F 3 "~" H 12900 3300 50  0001 C CNN
	1    12900 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	12900 3150 12900 3050
Connection ~ 12900 3050
Wire Wire Line
	12900 3550 12900 3450
Wire Wire Line
	13400 3550 13400 3350
Wire Wire Line
	13600 3050 13900 3050
$Comp
L Device:R R3
U 1 1 5D747F06
P 12900 3850
F 0 "R3" V 12693 3850 50  0000 C CNN
F 1 "10k" V 12784 3850 50  0000 C CNN
F 2 "obbo_footprints:R_0805K" V 12830 3850 50  0001 C CNN
F 3 "~" H 12900 3850 50  0001 C CNN
	1    12900 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5D74802F
P 12900 4150
F 0 "#PWR0105" H 12900 3900 50  0001 C CNN
F 1 "GND" H 12905 3977 50  0000 C CNN
F 2 "" H 12900 4150 50  0001 C CNN
F 3 "" H 12900 4150 50  0001 C CNN
	1    12900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	12900 4150 12900 4000
Wire Wire Line
	12900 3050 13200 3050
Wire Wire Line
	12900 3550 13400 3550
Connection ~ 12900 3550
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5D81923B
P 8750 3750
F 0 "J1" V 8623 3830 50  0000 L CNN
F 1 "ON/OFF" V 8714 3830 50  0000 L CNN
F 2 "obbo_footprints:PinHeader_1x02_P2.54mm_Vertical_PAD" H 8750 3750 50  0001 C CNN
F 3 "~" H 8750 3750 50  0001 C CNN
	1    8750 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	8950 2900 8950 3250
Connection ~ 8950 3250
$Comp
L Device:R R2
U 1 1 5D819C3E
P 8950 2750
F 0 "R2" V 8743 2750 50  0000 C CNN
F 1 "10k" V 8834 2750 50  0000 C CNN
F 2 "obbo_footprints:R_0805K" V 8880 2750 50  0001 C CNN
F 3 "~" H 8950 2750 50  0001 C CNN
	1    8950 2750
	-1   0    0    1   
$EndComp
Wire Wire Line
	8950 2600 8950 2500
Wire Wire Line
	8950 3650 8950 3250
Wire Wire Line
	12900 3550 12900 3700
Wire Wire Line
	12900 2650 12900 3050
Wire Wire Line
	4300 7750 4450 7750
Wire Wire Line
	4450 7750 4450 8250
Wire Wire Line
	4300 7850 4550 7850
Wire Wire Line
	4550 7850 4550 8250
Wire Wire Line
	4450 7650 4300 7650
Wire Wire Line
	4650 7850 4850 7850
Wire Wire Line
	4850 5750 4300 5750
$Comp
L Connector_Generic:Conn_01x06 J2
U 1 1 5D7BD426
P 5700 6250
F 0 "J2" H 5780 6242 50  0000 L CNN
F 1 "Conn_01x06" H 5780 6151 50  0000 L CNN
F 2 "obbo_footprints:PinHeader_1x06_P2.54mm_Vertical_PAD" H 5700 6250 50  0001 C CNN
F 3 "~" H 5700 6250 50  0001 C CNN
	1    5700 6250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J3
U 1 1 5D7BE5C5
P 4550 8450
F 0 "J3" H 4650 8650 50  0000 L CNN
F 1 "Conn_02x03_Odd_Even" H 4300 8750 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical_SMD" H 4550 8450 50  0001 C CNN
F 3 "~" H 4550 8450 50  0001 C CNN
	1    4550 8450
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 8800 4550 8800
Wire Wire Line
	4650 8800 4650 8750
Wire Wire Line
	4550 8750 4550 8800
Connection ~ 4550 8800
Wire Wire Line
	4550 8800 4650 8800
Wire Wire Line
	4450 8750 4450 8800
Connection ~ 4450 8800
$Comp
L Switch:SW_Push SW1
U 1 1 5D7F55E1
P 6100 4800
F 0 "SW1" V 6146 4752 50  0000 R CNN
F 1 "RESET" V 6055 4752 50  0000 R CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS645" H 6100 5000 50  0001 C CNN
F 3 "~" H 6100 5000 50  0001 C CNN
	1    6100 4800
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L1
U 1 1 5D7F7710
P 10450 3250
F 0 "L1" V 10550 3250 50  0000 C CNN
F 1 "100uH" V 10350 3250 50  0000 C CNN
F 2 "obbo_footprints:L_SMD_Ferrite_X13mm_Y10mm_H5mm_HandSoldering" H 10450 3250 50  0001 C CNN
F 3 "~" H 10450 3250 50  0001 C CNN
	1    10450 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10600 3250 10750 3250
Wire Wire Line
	10100 3250 10300 3250
$Comp
L obbo_Passive:bead B1
U 1 1 5D82F499
P 3800 4300
F 0 "B1" V 3754 4370 50  0000 L CNN
F 1 "bead" V 3845 4370 50  0000 L CNN
F 2 "obbo_footprints:L_0805K" V 3800 4300 50  0001 C CNN
F 3 "" V 3800 4300 50  0001 C CNN
	1    3800 4300
	0    1    1    0   
$EndComp
$Comp
L power:+12V #PWR017
U 1 1 5CAF0395
P 8200 2350
F 0 "#PWR017" H 8200 2200 50  0001 C CNN
F 1 "+12V" H 8215 2523 50  0000 C CNN
F 2 "" H 8200 2350 50  0001 C CNN
F 3 "" H 8200 2350 50  0001 C CNN
	1    8200 2350
	1    0    0    -1  
$EndComp
Connection ~ 8200 2500
Wire Wire Line
	8950 2500 8200 2500
Wire Wire Line
	8200 2350 8200 2500
Wire Wire Line
	8200 3050 9050 3050
Wire Wire Line
	8200 2500 8200 3050
Wire Wire Line
	7800 3050 8200 3050
Connection ~ 8200 3050
$Comp
L power:GND #PWR023
U 1 1 5CB2AD4F
P 8200 3600
F 0 "#PWR023" H 8200 3350 50  0001 C CNN
F 1 "GND" H 8205 3427 50  0000 C CNN
F 2 "" H 8200 3600 50  0001 C CNN
F 3 "" H 8200 3600 50  0001 C CNN
	1    8200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3500 8200 3600
Wire Wire Line
	8200 3200 8200 3050
$Comp
L Device:CP C11
U 1 1 5D6D5AB9
P 8200 3350
F 0 "C11" H 8318 3396 50  0000 L CNN
F 1 "100u/35V" H 8318 3305 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 8238 3200 50  0001 C CNN
F 3 "~" H 8200 3350 50  0001 C CNN
	1    8200 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 6950 5500 6950
Wire Wire Line
	5150 7050 5500 7050
Wire Wire Line
	5300 7150 5500 7150
Wire Wire Line
	4850 5750 4850 7850
Text GLabel 4700 3100 2    50   Input ~ 0
CH1
Text GLabel 4450 7650 2    50   Input ~ 0
CH1
Text GLabel 13600 5650 0    50   Input ~ 0
DIR_L
Text GLabel 4450 5850 2    50   Input ~ 0
DIR_L
Wire Wire Line
	13600 5650 13800 5650
Wire Wire Line
	13800 5650 13800 6400
Wire Wire Line
	13800 7050 13800 7200
Text GLabel 7450 6150 0    50   Input ~ 0
DIR_R
Text GLabel 4450 5950 2    50   Input ~ 0
DIR_R
Text GLabel 11450 8150 0    50   Input ~ 0
PULS_R
Wire Wire Line
	11450 8150 11550 8150
Text GLabel 4450 6550 2    50   Input ~ 0
PULS_R
Text GLabel 7600 8150 0    50   Input ~ 0
PULS_L
Wire Wire Line
	7600 8150 7800 8150
Text GLabel 4450 6650 2    50   Input ~ 0
PULS_L
$EndSCHEMATC
