EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "LPT CAPTURE  BOARD"
Date "2022-05-24"
Rev "1"
Comp "MILLSTREAM COMPUTING"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_Every A1
U 1 1 5FE48B53
P 6150 4100
F 0 "A1" H 5778 3011 50  0000 L BNN
F 1 "Arduino_Nano_Every" H 5778 2920 50  0000 L TNN
F 2 "Module:Arduino_Nano" H 6150 4100 50  0001 C CIN
F 3 "https://content.arduino.cc/assets/NANOEveryV3.0_sch.pdf" H 6150 4100 50  0001 C CNN
	1    6150 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:DB25_Male_MountingHoles J1
U 1 1 5FE4DA10
P 6000 1650
F 0 "J1" V 6317 1606 50  0000 C CNN
F 1 "DB25_Male_MountingHoles" V 6226 1606 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-25_Male_Horizontal_P2.77x2.84mm_EdgePinOffset4.94mm_Housed_MountingHolesOffset7.48mm" H 6000 1650 50  0001 C CNN
F 3 " ~" H 6000 1650 50  0001 C CNN
	1    6000 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7200 1950 7200 2000
Wire Wire Line
	7200 2700 5150 2700
Wire Wire Line
	5150 2700 5150 3600
Wire Wire Line
	5150 3600 5650 3600
Wire Wire Line
	7000 1950 7000 2000
Wire Wire Line
	7000 2650 5100 2650
Wire Wire Line
	5100 2650 5100 3700
Wire Wire Line
	5100 3700 5650 3700
Wire Wire Line
	6800 1950 6800 2000
Wire Wire Line
	6800 2600 5050 2600
Wire Wire Line
	5050 2600 5050 3800
Wire Wire Line
	5050 3800 5650 3800
Wire Wire Line
	6600 1950 6600 2000
Wire Wire Line
	6600 2550 5000 2550
Wire Wire Line
	5000 2550 5000 3900
Wire Wire Line
	5000 3900 5650 3900
Wire Wire Line
	6400 2500 4950 2500
Wire Wire Line
	4950 2500 4950 4000
Wire Wire Line
	4950 4000 5650 4000
Wire Wire Line
	6400 1950 6400 2000
Wire Wire Line
	6200 1950 6200 2000
Wire Wire Line
	6200 2450 4900 2450
Wire Wire Line
	4900 2450 4900 4100
Wire Wire Line
	4900 4100 5650 4100
Wire Wire Line
	6000 1950 6000 2000
Wire Wire Line
	6000 2400 4850 2400
Wire Wire Line
	4850 2400 4850 4200
Wire Wire Line
	4850 4200 5650 4200
Wire Wire Line
	5800 1950 5800 2000
Wire Wire Line
	5800 2350 4800 2350
Wire Wire Line
	4800 2350 4800 4300
Wire Wire Line
	4800 4300 5650 4300
Wire Wire Line
	5600 1950 5600 2000
Wire Wire Line
	5600 2300 4750 2300
Wire Wire Line
	4750 2300 4750 4400
Wire Wire Line
	4750 4400 5650 4400
Wire Wire Line
	5400 1950 5400 2950
Wire Wire Line
	5400 2950 7000 2950
Wire Wire Line
	7000 2950 7000 4100
Wire Wire Line
	7000 4100 6650 4100
Wire Wire Line
	5200 1950 5200 3000
Wire Wire Line
	5200 3000 7100 3000
Wire Wire Line
	7100 3000 7100 4200
Wire Wire Line
	7100 4200 6650 4200
Wire Wire Line
	6300 1950 6300 2100
Wire Wire Line
	6300 2100 6100 2100
Wire Wire Line
	6100 2100 6100 1950
Wire Wire Line
	5900 1950 5900 2100
Wire Wire Line
	5900 2100 6100 2100
Connection ~ 6100 2100
Wire Wire Line
	5700 1950 5700 2100
Wire Wire Line
	5700 2100 5900 2100
Connection ~ 5900 2100
Wire Wire Line
	5500 1950 5500 2100
Wire Wire Line
	5500 2100 5700 2100
Connection ~ 5700 2100
Wire Wire Line
	5300 1950 5300 2100
Wire Wire Line
	5300 2100 5500 2100
Connection ~ 5500 2100
Wire Wire Line
	5100 1950 5100 2100
Wire Wire Line
	5100 2100 5300 2100
Connection ~ 5300 2100
Wire Wire Line
	4900 1950 4900 2100
Wire Wire Line
	4900 2100 5000 2100
Connection ~ 5100 2100
$Comp
L power:GND #PWR0101
U 1 1 5FE52B83
P 4900 2100
F 0 "#PWR0101" H 4900 1850 50  0001 C CNN
F 1 "GND" H 4905 1927 50  0000 C CNN
F 2 "" H 4900 2100 50  0001 C CNN
F 3 "" H 4900 2100 50  0001 C CNN
	1    4900 2100
	1    0    0    -1  
$EndComp
Connection ~ 4900 2100
$Comp
L power:GND #PWR0102
U 1 1 5FE531C1
P 6150 5200
F 0 "#PWR0102" H 6150 4950 50  0001 C CNN
F 1 "GND" H 6155 5027 50  0000 C CNN
F 2 "" H 6150 5200 50  0001 C CNN
F 3 "" H 6150 5200 50  0001 C CNN
	1    6150 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5200 6150 5100
$Comp
L power:GND #PWR0103
U 1 1 5FE54AAA
P 7400 1750
F 0 "#PWR0103" H 7400 1500 50  0001 C CNN
F 1 "GND" H 7405 1577 50  0000 C CNN
F 2 "" H 7400 1750 50  0001 C CNN
F 3 "" H 7400 1750 50  0001 C CNN
	1    7400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1650 7400 1750
$Comp
L 74xx:74LS541 U2
U 1 1 5FE5F600
P 2550 4450
F 0 "U2" H 2550 5431 50  0000 C CNN
F 1 "74LS541" H 2550 5340 50  0000 C CNN
F 2 "Package_DIP:DIP-20_W7.62mm_LongPads" H 2550 4450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS541" H 2550 4450 50  0001 C CNN
	1    2550 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5FE5FFF9
P 7200 2150
F 0 "R9" H 7322 2196 50  0000 C CNN
F 1 "1K" H 7322 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7130 2150 50  0001 C CNN
F 3 "~" H 7200 2150 50  0001 C CNN
	1    7200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2300 7200 2700
$Comp
L Device:R R8
U 1 1 5FE608AE
P 7000 2150
F 0 "R8" H 7122 2196 50  0000 C CNN
F 1 "1K" H 7122 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6930 2150 50  0001 C CNN
F 3 "~" H 7000 2150 50  0001 C CNN
	1    7000 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2300 7000 2650
$Comp
L Device:R R7
U 1 1 5FE60B0A
P 6800 2150
F 0 "R7" H 6922 2196 50  0000 C CNN
F 1 "1K" H 6922 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6730 2150 50  0001 C CNN
F 3 "~" H 6800 2150 50  0001 C CNN
	1    6800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2300 6800 2600
$Comp
L Device:R R6
U 1 1 5FE60E1D
P 6600 2150
F 0 "R6" H 6722 2196 50  0000 C CNN
F 1 "1K" H 6722 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6530 2150 50  0001 C CNN
F 3 "~" H 6600 2150 50  0001 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2300 6600 2550
$Comp
L Device:R R5
U 1 1 5FE60FC6
P 6400 2150
F 0 "R5" H 6522 2196 50  0000 C CNN
F 1 "1K" H 6522 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6330 2150 50  0001 C CNN
F 3 "~" H 6400 2150 50  0001 C CNN
	1    6400 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2300 6400 2500
$Comp
L Device:R R4
U 1 1 5FE61261
P 6200 2150
F 0 "R4" H 6322 2196 50  0000 C CNN
F 1 "1K" H 6322 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6130 2150 50  0001 C CNN
F 3 "~" H 6200 2150 50  0001 C CNN
	1    6200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2300 6200 2450
$Comp
L Device:R R3
U 1 1 5FE61584
P 6000 2150
F 0 "R3" H 6122 2196 50  0000 C CNN
F 1 "1K" H 6122 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5930 2150 50  0001 C CNN
F 3 "~" H 6000 2150 50  0001 C CNN
	1    6000 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2300 6000 2400
$Comp
L Device:R R2
U 1 1 5FE617EF
P 5800 2150
F 0 "R2" H 5922 2196 50  0000 C CNN
F 1 "1K" H 5922 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5730 2150 50  0001 C CNN
F 3 "~" H 5800 2150 50  0001 C CNN
	1    5800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2300 5800 2350
$Comp
L Device:R R1
U 1 1 5FE61A16
P 5600 2150
F 0 "R1" H 5722 2196 50  0000 C CNN
F 1 "1K" H 5722 2105 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5530 2150 50  0001 C CNN
F 3 "~" H 5600 2150 50  0001 C CNN
	1    5600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 1950 5000 2100
Connection ~ 5000 2100
Wire Wire Line
	5000 2100 5100 2100
Text Notes 5250 1150 0    50   ~ 0
TODO: Change the wiring here to avoid\nall the bit shifting. Neater code or neater\nPCB?
Text Label 5300 3600 0    50   ~ 0
PD2(INT0)
Text Label 5400 3700 0    50   ~ 0
PD3
Text Label 5400 3800 0    50   ~ 0
PD4
Text Label 5400 3900 0    50   ~ 0
PD5
Text Label 5400 4000 0    50   ~ 0
PD6
Text Label 5400 4100 0    50   ~ 0
PD7
Text Label 5400 4200 0    50   ~ 0
PB0
Text Label 5400 4300 0    50   ~ 0
PB1
Text Label 5400 4400 0    50   ~ 0
PB2
Text Label 6750 4100 0    50   ~ 0
PC0
Text Label 6750 4200 0    50   ~ 0
PC1
Text Label 6650 4300 0    50   ~ 0
PC2
Text Label 6650 4400 0    50   ~ 0
PC3
Text Label 6650 4500 0    50   ~ 0
PC4
Text Label 6650 4600 0    50   ~ 0
PC5
Text Label 6650 4700 0    50   ~ 0
PC6
Text Label 6650 4800 0    50   ~ 0
PC7
Text Label 5450 4800 0    50   ~ 0
PB5
Text Label 5450 4700 0    50   ~ 0
PB4
Text Label 5450 4600 0    50   ~ 0
PB3
Wire Wire Line
	5450 4600 5650 4600
Wire Wire Line
	5450 4700 5650 4700
Wire Wire Line
	5450 4800 5650 4800
Text Notes 1050 4450 0    50   ~ 0
TODO: Maybe add buffers \nto prevent PC damage
NoConn ~ 7100 1950
NoConn ~ 6900 1950
NoConn ~ 6700 1950
NoConn ~ 6500 1950
NoConn ~ 4800 1950
NoConn ~ 6650 3500
NoConn ~ 6650 3600
NoConn ~ 6650 3900
$EndSCHEMATC
