EESchema Schematic File Version 5
EELAYER 33 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 3450 2000
Connection ~ 3150 2400
Connection ~ 6100 3000
Wire Wire Line
	1500 2500 1500 2400
Wire Wire Line
	1500 2500 2650 2500
Wire Wire Line
	3050 2400 3150 2400
Wire Wire Line
	3150 1850 3150 2400
Wire Wire Line
	3150 2400 3300 2400
Wire Wire Line
	3300 2000 3300 2400
Wire Wire Line
	3300 2000 3450 2000
Wire Wire Line
	3400 2800 3400 4300
Wire Wire Line
	3400 4300 6350 4300
Wire Wire Line
	3450 1550 3550 1550
Wire Wire Line
	3450 1900 3450 1550
Wire Wire Line
	3450 1900 3600 1900
Wire Wire Line
	3450 2000 3600 2000
Wire Wire Line
	3450 2100 3450 2000
Wire Wire Line
	3450 2600 3450 4250
Wire Wire Line
	3450 4250 6300 4250
Wire Wire Line
	3500 2700 3600 2700
Wire Wire Line
	3500 4200 3500 2700
Wire Wire Line
	3500 4200 6250 4200
Wire Wire Line
	3550 1550 3550 1600
Wire Wire Line
	3600 2100 3450 2100
Wire Wire Line
	3600 2600 3450 2600
Wire Wire Line
	3600 2800 3400 2800
Wire Wire Line
	4500 4050 4500 4000
Wire Wire Line
	5250 5300 6100 5300
Wire Wire Line
	5250 5400 6150 5400
Wire Wire Line
	5300 4600 5500 4600
Wire Wire Line
	5300 5500 5650 5500
Wire Wire Line
	5400 900  5600 900 
Wire Wire Line
	5400 1100 5400 900 
Wire Wire Line
	5500 4600 5500 4700
Wire Wire Line
	5600 900  5600 1000
Wire Wire Line
	5650 5500 5650 5700
Wire Wire Line
	5650 6200 5650 6000
Wire Wire Line
	6000 2300 6100 2300
Wire Wire Line
	6000 3000 6100 3000
Wire Wire Line
	6000 3200 6600 3200
Wire Wire Line
	6100 2300 6100 3000
Wire Wire Line
	6100 3000 6100 5300
Wire Wire Line
	6150 2200 6000 2200
Wire Wire Line
	6150 2200 6150 5400
Wire Wire Line
	6250 2350 6250 4200
Wire Wire Line
	6250 2350 6450 2350
Wire Wire Line
	6300 2150 6450 2150
Wire Wire Line
	6300 4250 6300 2150
Wire Wire Line
	6350 4300 6350 1950
Wire Wire Line
	6450 1950 6350 1950
Wire Wire Line
	6750 2150 6800 2150
Wire Wire Line
	6750 2350 6800 2350
Wire Wire Line
	6800 1950 6750 1950
Wire Wire Line
	7200 2150 7900 2150
Wire Wire Line
	7350 3200 7200 3200
Wire Wire Line
	7350 3750 7350 3200
Wire Wire Line
	7900 2150 7900 1950
Text Notes 7150 6300 0    50   ~ 0
bGeigieNano ESP32 Xbee version for BLE and WiFi.\nCopyrigth 2019 Safecast\n\n2019-03-20\n- For data from bGeigieNano the Xbee  pin 3 goes to pin 28\n- For programing through serial  0\n2019-03-28\n- for final check the RGB led cathode or anode.\n- check the wireing/pads for RGB led.\n- check the wires for serial 0 and serial 1\n\n2019-04-04 V1.1.0 \n- fixed the IO16 (RX) to Din (3) on xbee socket\n\n2019-06-24\n - Final fixes.\n\n
Text Notes 7350 7500 0    50   ~ 0
bGeigieNano ESP32 Xbee V1.4.0
Text Notes 8200 7650 0    50   ~ 0
2019-06-24
Text Notes 10600 7650 0    50   ~ 0
V1.1
Text GLabel 5250 4600 2    10   BiDi ~ 0
GND
Text GLabel 5250 5500 2    10   BiDi ~ 0
VDD
$Comp
L power:VDD #PWR0101
U 1 1 5C9DCF8F
P 1500 2400
F 0 "#PWR0101" H 1500 2250 50  0001 C CNN
F 1 "VDD" H 1518 2573 50  0000 C CNN
F 2 "" H 1500 2400 50  0001 C CNN
F 3 "" H 1500 2400 50  0001 C CNN
	1    1500 2400
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0105
U 1 1 5C707B62
P 5300 5500
F 0 "#PWR0105" H 5300 5350 50  0001 C CNN
F 1 "VDD" H 5318 5673 50  0000 C CNN
F 2 "" H 5300 5500 50  0001 C CNN
F 3 "" H 5300 5500 50  0001 C CNN
	1    5300 5500
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 5C9DDC35
P 3150 1850
F 0 "#PWR0102" H 3150 1700 50  0001 C CNN
F 1 "+3.3V" H 3165 2023 50  0000 C CNN
F 2 "" H 3150 1850 50  0001 C CNN
F 3 "" H 3150 1850 50  0001 C CNN
	1    3150 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR02
U 1 1 5C6662D2
P 7900 1950
F 0 "#PWR02" H 7900 1800 50  0001 C CNN
F 1 "+3.3V" H 7915 2123 50  0000 C CNN
F 2 "" H 7900 1950 50  0001 C CNN
F 3 "" H 7900 1950 50  0001 C CNN
	1    7900 1950
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:GND-kicad_project_geiger-cache #PWR03
U 1 1 5C66AD4C
P 3550 1600
F 0 "#PWR03" H 3550 1350 50  0001 C CNN
F 1 "GND" H 3555 1427 50  0000 C CNN
F 2 "" H 3550 1600 50  0000 C CNN
F 3 "" H 3550 1600 50  0000 C CNN
	1    3550 1600
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:GND-kicad_project_geiger-cache #PWR0104
U 1 1 5C68B954
P 4500 4050
F 0 "#PWR0104" H 4500 3800 50  0001 C CNN
F 1 "GND" H 4400 4050 50  0000 C CNN
F 2 "" H 4500 4050 50  0000 C CNN
F 3 "" H 4500 4050 50  0000 C CNN
	1    4500 4050
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:GND-kicad_project_geiger-cache #PWR01
U 1 1 5C6694D5
P 5500 4700
F 0 "#PWR01" H 5500 4450 50  0001 C CNN
F 1 "GND" V 5505 4572 50  0000 R CNN
F 2 "" H 5500 4700 50  0000 C CNN
F 3 "" H 5500 4700 50  0000 C CNN
	1    5500 4700
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:GND-kicad_project_geiger-cache #PWR0107
U 1 1 5C765427
P 5600 1000
F 0 "#PWR0107" H 5600 750 50  0001 C CNN
F 1 "GND" V 5605 872 50  0000 R CNN
F 2 "" H 5600 1000 50  0000 C CNN
F 3 "" H 5600 1000 50  0000 C CNN
	1    5600 1000
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:GND-kicad_project_geiger-cache #PWR04
U 1 1 5CC7DCAE
P 5650 6200
F 0 "#PWR04" H 5650 5950 50  0001 C CNN
F 1 "GND" H 5655 6027 50  0000 C CNN
F 2 "" H 5650 6200 50  0000 C CNN
F 3 "" H 5650 6200 50  0000 C CNN
	1    5650 6200
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:GND-kicad_project_geiger-cache #PWR0106
U 1 1 5C728459
P 7350 3750
F 0 "#PWR0106" H 7350 3500 50  0001 C CNN
F 1 "GND" H 7355 3577 50  0000 C CNN
F 2 "" H 7350 3750 50  0000 C CNN
F 3 "" H 7350 3750 50  0000 C CNN
	1    7350 3750
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:R-device R1
U 1 1 5CE61627
P 6600 1950
F 0 "R1" V 6500 1950 50  0000 C CNN
F 1 "470" V 6600 1950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6530 1950 50  0001 C CNN
F 3 "~" H 6600 1950 50  0001 C CNN
	1    6600 1950
	0    -1   -1   0   
$EndComp
$Comp
L xbee-rescue:R-device R3
U 1 1 5CE61931
P 6600 2150
F 0 "R3" V 6500 2150 50  0000 C CNN
F 1 "470" V 6600 2150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6530 2150 50  0001 C CNN
F 3 "~" H 6600 2150 50  0001 C CNN
	1    6600 2150
	0    -1   -1   0   
$EndComp
$Comp
L xbee-rescue:R-device R4
U 1 1 5CE61B83
P 6600 2350
F 0 "R4" V 6500 2350 50  0000 C CNN
F 1 "470" V 6600 2350 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6530 2350 50  0001 C CNN
F 3 "~" H 6600 2350 50  0001 C CNN
	1    6600 2350
	0    -1   -1   0   
$EndComp
$Comp
L xbee-rescue:CP1-kicad_project_geiger-cache C1
U 1 1 5CC7C796
P 5650 5850
F 0 "C1" H 5765 5941 50  0000 L CNN
F 1 "330uF" H 5765 5850 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-6032-15_Kemet-U_Pad2.25x2.35mm_HandSolder" H 5765 5759 50  0001 L CNN
F 3 "" H 5650 5850 50  0000 C CNN
	1    5650 5850
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:TACT-SWITCH-tinkerforge SW1
U 1 1 5C64B43D
P 6900 3200
F 0 "SW1" H 6900 3455 50  0000 C CNN
F 1 "TACT-SWITCH" H 6900 3050 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPST_TL3342" H 6900 3200 60  0001 C CNN
F 3 "" H 6900 3200 60  0000 C CNN
	1    6900 3200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW2
U 1 1 5C70EACA
P 2850 2500
F 0 "SW2" H 2850 2825 50  0000 C CNN
F 1 "SWITCH_INV" H 2850 2734 50  0000 C CNN
F 2 "Buttons_Switches_SMD:SW_SPDT_PCM12" V 2941 2688 50  0001 L CNN
F 3 "" H 2850 2500 50  0000 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
$Comp
L xbee-rescue:LED_RCBG-device D1
U 1 1 5C649CE7
P 7000 2150
F 0 "D1" H 7025 2537 60  0000 C CNN
F 1 "RGB-LED" H 7000 1750 60  0000 C CNN
F 2 "digikey-footprints:DJS-BRGBC-TR8" H 7250 2050 60  0001 C CNN
F 3 "" H 7250 2050 60  0000 C CNN
	1    7000 2150
	-1   0    0    1   
$EndComp
$Comp
L xbee-eagle-import:XBEE-1B2 U2
U 1 1 4D826FCC
P 4450 5100
F 0 "U2" H 3850 4350 56  0000 L BNN
F 1 "XBEE-socket" H 4200 5650 56  0000 L BNN
F 2 "digikey-footprints:XBEE-20_THT" H 4450 5100 50  0001 C CNN
F 3 "" H 4450 5100 50  0001 C CNN
	1    4450 5100
	-1   0    0    1   
$EndComp
$Comp
L xbee-rescue:ESP32S-espressif-xess U1
U 1 1 5C64BD37
P 3600 1900
F 0 "U1" H 5750 2600 60  0000 C CNN
F 1 "ESP32S" H 4850 2600 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP-32S" H 3600 1900 50  0001 C CNN
F 3 "http://www.shenzhen2u.com/ESP-32S" H 3600 1900 50  0001 C CNN
	1    3600 1900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
