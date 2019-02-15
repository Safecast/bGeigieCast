EESchema Schematic File Version 4
LIBS:xbee-cache
EELAYER 29 0
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
$EndDescr
$Comp
L xbee-eagle-import:XBEE-1B2 U$1
U 1 0 20F524AA4D826FCC
P 4600 4000
F 0 "U$1" H 4000 4530 56  0000 L BNN
F 1 "XBEE-1B2" H 4000 3300 56  0000 L BNN
F 2 "xbee:XBEE-SILK" H 4600 4000 50  0001 C CNN
F 3 "" H 4600 4000 50  0001 C CNN
	1    4600 4000
	1    0    0    -1  
$EndComp
Text GLabel 3800 3600 0    10   BiDi ~ 0
VDD
Text GLabel 3800 4500 0    10   BiDi ~ 0
GND
$Comp
L tinkerforge:RGB-LED D1
U 1 1 5C649CE7
P 5550 2550
F 0 "D1" H 5575 2937 60  0000 C CNN
F 1 "RGB-LED" H 5575 2831 60  0000 C CNN
F 2 "LEDs:LED_D5.0mm-4" H 5800 2450 60  0000 C CNN
F 3 "" H 5800 2450 60  0000 C CNN
	1    5550 2550
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:TACT-SWITCH SW1
U 1 1 5C64B43D
P 4400 2750
F 0 "SW1" H 4400 3005 50  0000 C CNN
F 1 "TACT-SWITCH" H 4400 2914 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_Tactile_SPST_Angled_PTS645Vx58-2LFS" H 4400 2750 60  0001 C CNN
F 3 "" H 4400 2750 60  0000 C CNN
	1    4400 2750
	1    0    0    -1  
$EndComp
$Comp
L espressif-xess:ESP32S U1
U 1 1 5C64BD37
P 6350 2850
F 0 "U1" H 7550 3853 60  0000 C CNN
F 1 "ESP32S" H 7550 3747 60  0000 C CNN
F 2 "ESP32-footprints-Lib:ESP3212" H 6350 2850 50  0001 C CNN
F 3 "http://www.shenzhen2u.com/ESP-32S" H 6350 2850 50  0001 C CNN
	1    6350 2850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
