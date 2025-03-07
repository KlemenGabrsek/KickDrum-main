/*
 * macros.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Klemen
 */

#ifndef INC_MACROS_H_
#define INC_MACROS_H_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * PCBA DATA
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SWITCH NUMBER
#define NUM_OF_CAP_SWITCHES_LEFT_PANEL 20
#define NUM_OF_CAP_SWITCHES_RIGHT_PANEL 19
#define NUM_OF_SWITCHES 40
//LED NUMBER
#define NUM_OF_LED_LEFT_PANEL 16
#define NUM_OF_LED_RIGHT_PANEL 17
#define NUM_OF_LED 33
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DIGITAL_GAIN	0x03	//min: 0x0 max: 0xF0
#define ADDR_DIGITAL_GAIN	0x98

#define SAMPLING_FREQUENCY		0x0
/*
SAMPLING_FREQUENCY=0x00 : Sampling frequency=1563kHz Detection duration per one sensor=0.2054ms
SAMPLING_FREQUENCY=0x0 : Sampling frequency=1024kHz Detection duration per one sensor=0.3082ms
SAMPLING_FREQUENCY=0x20 : Sampling frequency=781kHz Detection duration per one sensor=0.4109ms
SAMPLING_FREQUENCY=0x30 : Sampling frequency=391kHz Detection duration per one sensor=0.8218ms
SAMPLING_FREQUENCY=0x40 : Sampling frequency=298kHz Detection duration per one sensor=1.0786ms
SAMPLING_FREQUENCY=0x50 : Sampling frequency=195kHz Detection duration per one sensor=1.6435ms
SAMPLING_FREQUENCY=0x60 : Sampling frequency=156kHz Detection duration per one sensor=2.0544ms
SAMPLING_FREQUENCY=0x70 : Sampling frequency=130kHz Detection duration per one sensor=2.4653ms
 */
#define ADDR_SAMPLING_FREQUENCY		0x99

#define FILTER_TAP		0x03
/*
 * FIL_CFG[2:0]=0x00 : 1 kind (base frequency) of sampling frequency is used.
Median filter tap length=1
FIL_CFG[2:0]=0x01 : 3 kinds(+6%, ±0%, -6%) of sampling frequency is used.
Median filter tap length=3
FIL_CFG[2:0]=0x02 : 5 kinds(+6%, +3%, ±0%, -3%, -6%) of sampling frequency is used.
Median filter tap length=5
FIL_CFG[2:0]=0x03 : 7 kinds(+6%, +4%, +2%, ±0%, -2%, -4%, -6%) of sampling frequency is used.
Median filter tap length=7
FIL_CFG[2:0]=0x04 : 7 kinds(+6%, +4%, +2%, ±0%, -2%, -4%, -6%) of sampling frequency is used.
Median filter tap length=9
FIL_CFG[2:0]=0x05 : 7 kinds(+6%, +4%, +2%, ±0%, -2%, -4%, -6%) of sampling frequency is used.
Median filter tap length=11
FIL_CFG[2:0]=0x06 : 7 kinds(+6%, +4%, +2%, ±0%, -2%, -4%, -6%) of sampling frequency is used.
Median filter tap length=13
FIL_CFG[2:0]=0x07 : 7 kinds(+6%, +4%, +2%, ±0%, -2%, -4%,, -6%) of sampling frequency is used.
Median filter tap length=15
 */

#define ADDR_FILTER_TAP	0x9A

#define CONTROL_MODE 	(SENSOR_HIGH_IMPEDANCE|OFFSET_CALIBRATION|UNEXPECTED_LONG_PRESS_CALIBRATION|LOWER_CALIBRATION|SAMPLING_FREQENCY_MODULATION|MULTIPLE_SWITCHES_CONTROLL )
#define SENSOR_HIGH_IMPEDANCE 0x00								//0x01 sensor becomes high impedance, 0x00 sensor outputs low
#define OFFSET_CALIBRATION 0x00											//0x02 offset calibration is disabled, 0x00 offset calibration is enabled
#define UNEXPECTED_LONG_PRESS_CALIBRATION 0x00		//0x04unexpedcted long press calibration is enabled, 0x00 unexpected long press calibration disabled
#define LOWER_CALIBRATION 0x00											//0x08lower calibration is enabled, 0x00 lower calibration is disabled
#define SAMPLING_FREQENCY_MODULATION 0x00				//0x10 enabled, 0x00 disabled
#define MULTIPLE_SWITCHES_CONTROLL 0x80						//0x80 multiple switches usable, 0x00 multiple switchesunusable
#define ADDR_CONTROL_MODE		0x9B
#define SIZE_CONTROL_MODE		1


#define OVERSAMPLING 0x03 // min:0x01 max 0x0F
#define ADDR_OVERSAMPLING 0x9C

#define UNEXPECTED_LONG_PRESS_DETECTION_TIME 	{0x00,0x00}    // in case register set to 0, unexpected long press not detected.....0xFF
#define ADDR_UNEXPECTED_LONG_PRESS_DETECTION_TIME 0xA2
#define SIZE_UNEXPECTED_LONG_PRESS_DETECTION_TIME	2
/*
 * The time until detecting unexpected long press = TIME_UNKNOWN_*[7:0] x Approximately 1s
In the case TIME_ UNKNOWN_*[7:0] is set to 0, unexpected long press is not detected.
 */

#define LONG_PRESS_DETECTION_TIME  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#define ADDR_LONG_PRESS_DETECTION_TIME 0xA4
#define SIZE_LONG_PRESS_DETECTION_TIME 14

/*
 * The time until detecting long press = TIME_HLD_*[7:0] x Approximately 0.1s
In the case TIME_HLD_*[7:0] is set to 0, long press is not detected.
The time until detecting repeated long press = TIME_HLD_RPT_*[7:0] x Approximately 0.1s
In the case TIME_HLD_RPT_*[7:0] is set to 0, repeated long press is not detected.
 */

#define SWITCH_DETECTION_TIME 0x01 		//min 0x00, max 0xFF
#define ADDR_SWITCH_DETECTION_TIME 0xBC
#define SIZE_SWITCH_DETECTION_TIME 1
/*
 * The time until detecting the ON state of switch = TIME_DET[7:0] x Approximately 10ms
 * 0x1E *10 ms=30* 10 ms = 300ms -> multi pattern ne dela
 * * 0x32 *10 ms=50* 10 ms = 500ms -> multi pattern ne dela
 * * * 0xFF *10 ms=256* 10 ms = 2,5 s -> multi pattern ne dela
 *
 */

#define MULTIPLE_PATTERN_SWITCH_ASSIGNMENT_L {MULT_A_L, MULT_B_L, MULT_C_L, MULT_D_L, MULT_E_L, MULT_F_L, MULT_G_L, MULT_H_L}

#define MULT_A_L    CS0|CS1,0x00,0x00
#define MULT_B_L    CS0|CS2,0x00,0x00
#define MULT_C_L    CS2|CS1,0x00,0x00
#define MULT_D_L    0x00,0x00,CS17|CS18
#define MULT_E_L    0x00,0x00,CS18|CS19
#define MULT_F_L    0x00,0x00,CS17|CS19
#define MULT_G_L    0x00,0x00,0x00
#define MULT_H_L    0x00,0x00,0x00


#define MULTIPLE_PATTERN_SWITCH_ASSIGNMENT_R {MULT_A_R, MULT_B_R, MULT_C_R, MULT_D_R, MULT_E_R, MULT_F_R, MULT_G_R, MULT_H_R}

#define MULT_A_R    0x00,0x00,0x00
#define MULT_B_R    0x00,0x00,0x00
#define MULT_C_R    0x00,0x00,0x00
#define MULT_D_R    0x00,0x00,0x00
#define MULT_E_R    0x00,0x00,0x00
#define MULT_F_R    0x00,0x00,0x00
#define MULT_G_R    0x00,0x00,0x00
#define MULT_H_R    0x00,0x00,0x00


#define CS0 0x01
#define CS1 0x02
#define CS2 0x04
#define CS3 0x08
#define CS4 0x10
#define CS5 0x20
#define CS6 0x40
#define CS7 0x80
#define CS8 0x01
#define CS9 0x02
#define CS10 0x04
#define CS11 0x08
#define CS12 0x10
#define CS13 0x20
#define CS14 0x40
#define CS15 0x80
#define CS16 0x01
#define CS17 0x02
#define CS18 0x04
#define CS19 0x08
#define CS20 0x10

#define ADDR_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT 0xBD
#define SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT 24
/*
 * These registers configure the combinations of multiple pattern switches detection. The multiple pattern
switch combinations are able to be set up to 8 types from A to H. In the case the same combinations are set
in 8 types, the combination settings are invalid.
MULT_A_CS*=0: CS* is not assigned to multiple pattern switches A.
MULT_A_CS*=1: CS* is assigned to multiple pattern switches A.
MULT_B_CS*=0: CS* is not assigned to multiple pattern switches B.
MULT_B_CS*=1: CS* is assigned to multiple pattern switches B.
MULT_C_CS*=0: CS* is not assigned to multiple pattern switches C.
MULT_C_CS*=1: CS* is assigned to multiple pattern switches C.
MULT_D_CS*=0: CS* is not assigned to multiple pattern switches D.
MULT_D_CS*=1: CS* is assigned to multiple pattern switches D.
MULT_E_CS*=0: CS* is not assigned to multiple pattern switches E.
MULT_E_CS*=1: CS* is assigned to multiple pattern switches E.
MULT_F_CS*=0: CS* is not assigned to multiple pattern switches F.
MULT_F_CS*=1: CS* is assigned to multiple pattern switches F.
MULT_G_CS*=0: CS* is not assigned to multiple pattern switches G.
MULT_G_CS*=1: CS* is assigned to multiple pattern switches G.
MULT_H_CS*=0: CS* is not assigned to multiple pattern switches H.
MULT_H_CS*=1: CS* is assigned to multiple pattern switches H.
 */

#define MASK_INTERRUPT_FACTOR {MASK_SOFTWARE_CALIBRATION_COMPLETION_INTERRUPT|\
																MASK_SOFTWARE_CALIBRATION_FAILURE_INTERRUPT|\
																MASK_NOISE_DETECTION_INTERRUPT,MASK_AVDD_ON_DETECTION |MASK_AVDD_OFF_DETECTION}
#define MASK_SOFTWARE_CALIBRATION_COMPLETION_INTERRUPT 0x04 //clear interrupt0x04
#define MASK_SOFTWARE_CALIBRATION_FAILURE_INTERRUPT 0x08	//0x08
#define MASK_NOISE_DETECTION_INTERRUPT 0x80		//0x80
#define MASK_AVDD_ON_DETECTION 0x01		//0x01
#define MASK_AVDD_OFF_DETECTION 0x02		//0x02
#define ADDR_MASK_INTERRUPT_FACTOR 0xd5
#define SIZE_MASK_INTERRUPT_FACTOR 2
/*
 * These registers are for masking the interrupt of the register “Interrupt Factor”. In the case mask is set to 1,
Interrupt is not reflected to the register “Interrupt Factor”.
 */

#define CLEAR_INTERRUPT_FACTOR {CLR_INT_FININI |\
																	CLR_INT_FINCAL |\
																	CLR_INT_FALCAL |\
																	CLR_INT_NOISE,\
																	CLR_INT_AVDDON |\
																	CLR_INT_AVDDOFF}


#define CLR_INT_FININI 0x00
#define CLR_INT_FINCAL 0x00
#define CLR_INT_FALCAL 0x00
#define CLR_INT_NOISE 0x00
#define CLR_INT_AVDDON 0x00
#define CLR_INT_AVDDOFF 0x00




#define ADDR_CLEAR_INTERRUPT_FACTOR 0xE0
#define SIZE_CLEAR_INTERRUPT_FACTOR 2

/*
 * These are for clearing the interrupt of the register “Interrupt Factor”.
	0: Interrupt is cleared 1: Interrupt is not cleared
 */

#define CLEAR_SWITCH_ON_DETECTION {0x00,0x00,0x00}
#define ADDR_CLEAR_SWITCH_ON_DETECTION 0xE2
#define SIZE_CLEAR_SWITCH_ON_DETECTION 3
/*
 * These registers are for clearing the interrupt of the register “Switch ON Detection”.
0: Interrupt is cleared 1: Interrupt is not cleared
 */

#define CLEAR_SWITCH_OFF_DETECTION {0x00,0x00,0x00}
#define ADDR_CLEAR_SWITCH_OFF_DETECTION 0xE5
#define SIZE_CLEAR_SWITCH_OFF_DETECTION 3
/*
 * These registers are for clearing the interrupt of the register “Switch OFF Detection”.
0: Interrupt is cleared 1: Interrupt is not cleared
 */

#define CLEAR_SWITCH_LONG_PRESS_DETECTION {0x00,0x00,0x00}
#define ADDR_CLEAR_SWITCH_LONG_PRESS_DETECTION 0xE8
#define SIZE_CLEAR_SWITCH_LONG_PRESS_DETECTION 3
/*
 * These registers are for clearing the interrupt of the register “Switch LONG_PRESS Detection”.
0: Interrupt is cleared 1: Interrupt is not cleared
 */

#define CLEAR_SWITCH_REPEATED_LONG_PRESS_DETECTION {0x00,0x00,0x00}
#define ADDR_CLEAR_SWITCH_REPEATED_LONG_PRESS_DETECTION 0xEB
#define SIZE_CLEAR_SWITCH_REPEATED_LONG_PRESS_DETECTION 3
/*
 * These registers are for clearing the interrupt of the register “Switch REPEATED LONG_PRESS Detection”.
0: Interrupt is cleared 1: Interrupt is not cleared
 */
#define SIZE_CLEAR_MULTIPLE_PATTERN_SWITCHES_ON_DETECTION 1
#define CLEAR_MULTIPLE_PATTERN_SWITCHES_ON_DETECTION 0x00
#define ADDR_CLEAR_MULTIPLE_PATTERN_SWITCHES_ON_DETECTION 0xEE

/*
 * These registers are for clearing the interrupt of the register “Switch REPEATED LONG_PRESS Detection”.
0: Interrupt is cleared 1: Interrupt is not cleared
 */
#define SIZE_CLEAR_MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION 1
#define CLEAR_MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION 0x00
#define ADDR_CLEAR_MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION 0xEF

#define CLEAR_UNEXPECTED_LONG_PRESS_DETECTION {0x00,0x00,0x00}
#define ADDR_CLEAR_UNEXPECTED_LONG_PRESS_DETECTION 0xF0
#define SIZE_CLEAR_UNEXPECTED_LONG_PRESS_DETECTION 3



/*
 * These registers are for clearing the interrupt of the register “Switch REPEATED LONG_PRESS Detection”.
0: Interrupt is cleared 1: Interrupt is not cleared
 */

#define AVDD_LDO_CONTROL {AVDD_LDO_CONTROLL_ON|\
															AVDD_LDO_OUTPUT_VOLTAGE_2_7V	}

#define AVDD_LDO_CONTROLL_ON 0x01
#define AVDD_LDO_CONTROLL_OFF 0x00
#define AVDD_LDO_OUTPUT_VOLTAGE_2_8V 0x00
#define AVDD_LDO_OUTPUT_VOLTAGE_2_7V 0x10
#define AVDD_LDO_OUTPUT_VOLTAGE_2_6V 0x20
#define AVDD_LDO_OUTPUT_VOLTAGE_2_5V 0x30
#define ADDR_AVDD_LDO_CONTROL 0xFE
#define SIZE_AVDD_LDO_CONTROL 1



#define SENSOR_CONTROL      {CONTROLL_SENSOR_DETECTION_START | SOFTWARE_CALIBRATION_CONTROL_CALIBRATION_ON | UPDATE_CONFIGURATION_REGISTERS}
#define CONTROLL_SENSOR_DETECTION_START 0x01
#define CONTROLL_SENSOR_DETECTION_STOP 0x00
#define SOFTWARE_CALIBRATION_CONTROL_CALIBRATION_ON 0x02
#define SOFTWARE_CALIBRATION_CONTROL_CALIBRATION_OFF 0x00
#define UPDATE_CONFIGURATION_REGISTERS 0x04
#define ADDR_SENSOR_CONTROL 0xFF
#define SIZE_SENSOR_CONTROL 1

//vsak register  8 bitov je en senzor
#define	ADDR_SENSOR_DATA 0x00
#define	SIZE_SENSOR_DATA 20

#define ADDR_FILTER_SENSOR_DATA 0x15
#define SIZE_FILTER_SENSOR_DATA 40

#define ADDR_INTERRUPT_FACTOR 0x40
#define SIZE_INTERRUPT_FACTOR 3
#define  INITIALIZATION_COMPLETION_INTERRUPT 0x01
#define  SOFTWARE_CALIBRATION_COMPLETION_INTERRUPT 0x04
#define  CALIBRATION_FAILURE_INTERRUPT 0x08
#define  UNEXPECTED_LONG_PRESS_DETECTION_INTERRUPT 0x40
#define  NOISE_DETECTION_INTERRUPT 0x80
#define  SWITCH_ON_DETECTION_INTERRUPT 0x01
#define  SWITCH_OFF_DETECTION_INTERRUPT 0x02
#define  SWITCH_LONG_PRESS_DETECTION_INTERRUPT 0x04
#define  SWITCH_REPEATED_LONG_PRESS_DETECTION_INTERRUPT 0x08
#define  MULTIPLE_PATTERN_SWITCHES_ON_DETECTION_INTERRUPT 0x10
#define  MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION_INTERRUPT 0x20
#define  AVDD_ON_DETECTION_INTERRUPT 0x01
#define  AVDD_OFF_DETECTION_INTERRUPT 0x02


#define INTERRUPT_FACTOR_REG1_FLAGS  INITIALIZATION_COMPLETION_INTERRUPT | SOFTWARE_CALIBRATION_COMPLETION_INTERRUPT |\
																		CALIBRATION_FAILURE_INTERRUPT|UNEXPECTED_LONG_PRESS_DETECTION_INTERRUPT |\
																			NOISE_DETECTION_INTERRUPT

#define INTERRUPT_FACTOR_REG2_FLAGS      SWITCH_ON_DETECTION_INTERRUPT | SWITCH_OFF_DETECTION_INTERRUPT|SWITCH_LONG_PRESS_DETECTION_INTERRUPT|\
																	SWITCH_REPEATED_LONG_PRESS_DETECTION_INTERRUPT|MULTIPLE_PATTERN_SWITCHES_ON_DETECTION_INTERRUPT|\
																	MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION_INTERRUPT


#define INTERRUPT_FACTOR_REG3_FLAGS    AVDD_ON_DETECTION_INTERRUPT| AVDD_OFF_DETECTION_INTERRUPT

#define INTERRUPT_FACTOR_FLAGS       {INTERRUPT_FACTOR_REG1_FLAGS  ,INTERRUPT_FACTOR_REG2_FLAGS , INTERRUPT_FACTOR_REG3_FLAGS}

#define ADDR_SWITCH_ON_DETECTION 0x43
#define SIZE_SWITCH_ON_DETECTION 3

#define ADDR_SWITCH_OFF_DETECTION 0x46
#define SIZE_SWITCH_OFF_DETECTION 3

#define ADDR_SWITCH_LONG_PRESS_DETECTION 0x49
#define SIZE_SWITCH_LONG_PRESS_DETECTION 3

#define ADDR_SWITCH_REPEATED_LONG_PRESS_DETECTION 0x4C
#define SIZE_SWITCH_REPEATED_LONG_PRESS_DETECTION 3

#define ADDR_MULTIPLE_PATTERN_SWITCH_ON_DETECTION 0X4F
#define SIZE_MULTIPLE_PATTERN_SWITCH_ON_DETECTION 1

#define ADDR_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION 0X50
#define SIZE_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION 1

#define ADDR_UNEXPECTED_LONG_PRESS_DETECTION 0x51
#define SIZE_UNEXPECTED_LONG_PRESS_DETECTION 3

#define ADDR_SWITCH_ON_OFF_STATE 0x54
#define SIZE_SWITCH_ON_OFF_STATE 3

#define ADDR_STATE_OF_IC 0x57
#define SIZE_STATE_OF_IC 1

#define STATE_OFF_SENSOR 0x02
#define STATE_OFF_CALIBRATION 0x04

#define ADDR_CALIBRATION_FAILURE_NUMBER_OF_TIMES 0x58

#define ADDR_SENSOR_FUNCTION 0x60
#define SIZE_SENSOR_FUNCTION 5

#define ADDR_SENSITIVITY 0x66
#define SIZE_SENSITIVITY 10

#define ADDR_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD  0X70
#define SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD  40


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * SLIDER DEFINITION AREA
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUMBER_OF_SLIDERS 3

#define SWITCH_NUMBER { SLIDER_0_SWITCH_NUM, SLIDER_1_SWITCH_NUM,SLIDER_2_SWITCH_NUM}

#define SLIDER_0_SWITCH_NUM {0,1,2}
#define SLIDER_1_SWITCH_NUM {17,18,19}
#define SLIDER_2_SWITCH_NUM {28,31,34}

#define SLIDER_CROSSSECTION_NUMBERS {SLIDER_0_CROSSSECTION_NUMBERS, SLIDER_1_CROSSSECTIONS_NUMBERS, SLIDER_2_CROSSSECTIONS_NUMBERS}

#define SLIDER_0_CROSSSECTION_NUMBERS {0,2,1}

#define SLIDER_1_CROSSSECTIONS_NUMBERS {3,4,5}
#define SLIDER_2_CROSSSECTIONS_NUMBERS {0,2,1}


#define SLIDER_0_NAME "OUT LEVEL"
#define SLIDER_1_NAME "DECAY"
#define SLIDER_2_NAME "TEMPO"

#define SLIDER_NAMES {SLIDER_0_NAME,SLIDER_1_NAME,SLIDER_2_NAME}

#define SLIDER_SWITCHES {SLIDER_0_SWITCHES,SLIDER_1_SWITCHES,SLIDER_2_SWITCHES}
#define SLIDER_0_SWITCHES {"CS0","CS1","CS2"}
#define SLIDER_1_SWITCHES {"CS17","CS18","CS19"}
#define SLIDER_2_SWITCHES {"CS8","CS11","CS14"}

#define SLIDER_CROSSSECTIONS {SLIDER_0_CROSSSECTIONS,SLIDER_1_CROSSSECTIONS,SLIDER_2_CROSSSECTIONS}
#define SLIDER_0_CROSSSECTIONS {"CS0CS1","CS1CS2","CS0CS2"}
#define SLIDER_1_CROSSSECTIONS {"CS17CS18","CS18CS19","CS17CS19"}
#define SLIDER_2_CROSSSECTIONS {"CS8CS11","CS11CS14","CS8CS14"}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * LED DRIVER DEFINITION AREA
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_OF_REG_IN_LED_DRIVER 1
#define NUM_OF_IS32_STRUCT_FOR_SENDING 8


#define ADDR_SHUTDOWN_REGISTER {0x00,0x00,0x00,0x00,0x00}

// PWM Registers for 18 channels (01h to 12h)


#define ADDR_LED_CONTROL_REGISTER_1 0x13
#define ADDR_LED_CONTROL_REGISTER_2 0x14
#define ADDR_LED_CONTROL_REGISTER_3 0x15

#define ADDR_LED_CONTROL_REG {ADDR_LED_CONTROL_REGISTER_1, ADDR_LED_CONTROL_REGISTER_2, ADDR_LED_CONTROL_REGISTER_3,0x00,0x00}

#define ADDR_UPDATE_REGISTER {0x16,0x00,0x00,0x00,0x00}
#define ADDR_RESET_REGISTER {0x17,0x00,0x00,0x00,0x00}

// Define individual addresses for PWM channels
#define ADDR_PWM_CHANNEL_1 0x01
#define ADDR_PWM_CHANNEL_2 0x02
#define ADDR_PWM_CHANNEL_3 0x03
#define ADDR_PWM_CHANNEL_4 0x04
#define ADDR_PWM_CHANNEL_5 0x05
#define ADDR_PWM_CHANNEL_6 0x06
#define ADDR_PWM_CHANNEL_7 0x07
#define ADDR_PWM_CHANNEL_8 0x08
#define ADDR_PWM_CHANNEL_9 0x09
#define ADDR_PWM_CHANNEL_10 0x0A
#define ADDR_PWM_CHANNEL_11 0x0B
#define ADDR_PWM_CHANNEL_12 0x0C
#define ADDR_PWM_CHANNEL_13 0x0D
#define ADDR_PWM_CHANNEL_14 0x0E
#define ADDR_PWM_CHANNEL_15 0x0F
#define ADDR_PWM_CHANNEL_16 0x10
#define ADDR_PWM_CHANNEL_17 0x11
#define ADDR_PWM_CHANNEL_18 0x12

// Array of PWM channel addresses for channels 1 to 5
#define ADDR_PWM_CHANNELS_1_TO_5 { \
    ADDR_PWM_CHANNEL_1, \
    ADDR_PWM_CHANNEL_2, \
    ADDR_PWM_CHANNEL_3, \
    ADDR_PWM_CHANNEL_4, \
    ADDR_PWM_CHANNEL_5  \
}

// Array of PWM channel addresses for channels 6 to 10
#define ADDR_PWM_CHANNELS_6_TO_10 { \
    ADDR_PWM_CHANNEL_6, \
    ADDR_PWM_CHANNEL_7, \
    ADDR_PWM_CHANNEL_8, \
    ADDR_PWM_CHANNEL_9, \
    ADDR_PWM_CHANNEL_10  \
}

// Array of PWM channel addresses for channels 11 to 15
#define ADDR_PWM_CHANNELS_11_TO_15 { \
    ADDR_PWM_CHANNEL_11, \
    ADDR_PWM_CHANNEL_12, \
    ADDR_PWM_CHANNEL_13, \
    ADDR_PWM_CHANNEL_14, \
    ADDR_PWM_CHANNEL_15  \
}

// Array of PWM channel addresses for channels 16 to 18
#define ADDR_PWM_CHANNELS_16_TO_18 { \
    ADDR_PWM_CHANNEL_16, \
    ADDR_PWM_CHANNEL_17, \
    ADDR_PWM_CHANNEL_18,  \
	0x00,\
	0x00\
}

// Combined array of all PWM channel addresses
#define ADDR_PWM_CHANNELS_ALL { \
    ADDR_PWM_CHANNELS_1_TO_5, \
    ADDR_PWM_CHANNELS_6_TO_10, \
    ADDR_PWM_CHANNELS_11_TO_15, \
    ADDR_PWM_CHANNELS_16_TO_18  \
}
//////////////////////ALL ADDRS
#define ADDR_OF_ALL_REG_FOR_IS32 {\
	ADDR_SHUTDOWN_REGISTER,\
	ADDR_UPDATE_REGISTER,\
	ADDR_RESET_REGISTER,\
	ADDR_LED_CONTROL_REG,\
	ADDR_PWM_CHANNELS_1_TO_5,\
	ADDR_PWM_CHANNELS_6_TO_10,\
	ADDR_PWM_CHANNELS_11_TO_15,\
	ADDR_PWM_CHANNELS_16_TO_18}


/////////////////////////////////////////////////////////
/*
#define PWM_CHANNEL_1_VALUE 0xFF
#define PWM_CHANNEL_2_VALUE 0xFF
#define PWM_CHANNEL_3_VALUE 0xFF
#define PWM_CHANNEL_4_VALUE 0xFF
#define PWM_CHANNEL_5_VALUE 0xFF
#define PWM_CHANNEL_6_VALUE 0xFF
#define PWM_CHANNEL_7_VALUE 0xFF
#define PWM_CHANNEL_8_VALUE 0xFF
#define PWM_CHANNEL_9_VALUE 0xFF
#define PWM_CHANNEL_10_VALUE 0xFF
#define PWM_CHANNEL_11_VALUE 0xFF
#define PWM_CHANNEL_12_VALUE 0xFF
#define PWM_CHANNEL_13_VALUE 0xFF
#define PWM_CHANNEL_14_VALUE 0xFF
#define PWM_CHANNEL_15_VALUE 0xFF
#define PWM_CHANNEL_16_VALUE 0xFF
#define PWM_CHANNEL_17_VALUE 0xFF
#define PWM_CHANNEL_18_VALUE 0xFF
*/
#define PWM_CHANNEL_1_VALUE  0
#define PWM_CHANNEL_2_VALUE  0
#define PWM_CHANNEL_3_VALUE  0
#define PWM_CHANNEL_4_VALUE  0
#define PWM_CHANNEL_5_VALUE  0
#define PWM_CHANNEL_6_VALUE  0
#define PWM_CHANNEL_7_VALUE  0
#define PWM_CHANNEL_8_VALUE  0
#define PWM_CHANNEL_9_VALUE  0
#define PWM_CHANNEL_10_VALUE 0
#define PWM_CHANNEL_11_VALUE 0
#define PWM_CHANNEL_12_VALUE 0
#define PWM_CHANNEL_13_VALUE 0
#define PWM_CHANNEL_14_VALUE 0
#define PWM_CHANNEL_15_VALUE 0
#define PWM_CHANNEL_16_VALUE 0
#define PWM_CHANNEL_17_VALUE 0
#define PWM_CHANNEL_18_VALUE 0



// Array of PWM channel values for channels 1 to 5
#define PWM_CHANNELS_1_TO_5_VALUES {\
	 PWM_CHANNEL_1_VALUE, \
    PWM_CHANNEL_2_VALUE, \
    PWM_CHANNEL_3_VALUE, \
    PWM_CHANNEL_4_VALUE, \
	 PWM_CHANNEL_5_VALUE \
}

// Array of PWM channel values for channels 6 to 10
#define PWM_CHANNELS_6_TO_10_VALUES { \
    PWM_CHANNEL_6_VALUE , \
    PWM_CHANNEL_7_VALUE , \
    PWM_CHANNEL_8_VALUE , \
    PWM_CHANNEL_9_VALUE , \
    PWM_CHANNEL_10_VALUE  \
}

// Array of PWM channel values for channels 11 to 15
#define PWM_CHANNELS_11_TO_15_VALUES { \
    PWM_CHANNEL_11_VALUE , \
    PWM_CHANNEL_12_VALUE , \
    PWM_CHANNEL_13_VALUE , \
    PWM_CHANNEL_14_VALUE , \
    PWM_CHANNEL_15_VALUE   \
}

// Array of PWM channel values for channels 16 to 18
#define PWM_CHANNELS_16_TO_18_VALUES { \
    PWM_CHANNEL_16_VALUE , \
    PWM_CHANNEL_17_VALUE , \
    PWM_CHANNEL_18_VALUE  }

// Combined array of all PWM channel values
#define PWM_CHANNELS_1_TO_18_VALUES { \
    PWM_CHANNELS_1_TO_5_VALUES, \
    PWM_CHANNELS_6_TO_10_VALUES, \
    PWM_CHANNELS_11_TO_15_VALUES, \
    PWM_CHANNELS_16_TO_18_VALUES  \
}



// Array of all PWM channel values


// 0 - LED OFF
//0x1.... - LED ON
/*
#define LED_1_STATE 0x1//0x1
#define LED_2_STATE 0x2//0x2
#define LED_3_STATE 0x4
#define LED_4_STATE  0x8
#define LED_5_STATE 0x10
#define LED_6_STATE 0x20
#define LED_7_STATE 0x1
#define LED_8_STATE 0x2
#define LED_9_STATE 0x4
#define LED_10_STATE 0x8
#define LED_11_STATE 0x10
#define LED_12_STATE 0x20
#define LED_13_STATE 0x1
#define LED_14_STATE 0x2
#define LED_15_STATE 0x4
#define LED_16_STATE 0x8
#define LED_17_STATE 0x10
#define LED_18_STATE 0x20
*/

#define LED_1_STATE 0x0
#define LED_2_STATE 0x0
#define LED_3_STATE 0
#define LED_4_STATE 0
#define LED_5_STATE 0
#define LED_6_STATE 0
#define LED_7_STATE 0
#define LED_8_STATE 0
#define LED_9_STATE 0
#define LED_10_STATE 0
#define LED_11_STATE 0
#define LED_12_STATE 0
#define LED_13_STATE 0
#define LED_14_STATE 0
#define LED_15_STATE 0
#define LED_16_STATE 0
#define LED_17_STATE 0
#define LED_18_STATE 0


// Array of all LED states
#define LED_CONTROL_REGISTER_1_STATES  ( \
    LED_1_STATE | \
    LED_2_STATE | \
    LED_3_STATE | \
    LED_4_STATE | \
    LED_5_STATE | \
    LED_6_STATE )

#define LED_CONTROL_REGISTER_2_STATES ( \
    LED_7_STATE | \
    LED_8_STATE | \
    LED_9_STATE | \
    LED_10_STATE | \
    LED_11_STATE | \
    LED_12_STATE  )

#define LED_CONTROL_REGISTER_3_STATES (\
    LED_13_STATE | \
    LED_14_STATE | \
    LED_15_STATE | \
    LED_16_STATE | \
    LED_17_STATE | \
    LED_18_STATE  )


#define LED_CONTROL_REGISTER_ALL {LED_CONTROL_REGISTER_1_STATES,\
	LED_CONTROL_REGISTER_2_STATES,\
	LED_CONTROL_REGISTER_3_STATES}
///////////////////////////////////////////////////////////////////
#define ALL_REGISTERS_FOR_IS32 { \
SHUTDOWN_REGISTER,\
UPDATE_REGISTER,\
RESET_REGISTER ,\
LED_CONTROL_REGISTER_ALL,\
PWM_CHANNELS_1_TO_5_VALUES,\
PWM_CHANNELS_6_TO_10_VALUES,\
PWM_CHANNELS_11_TO_15_VALUES,\
PWM_CHANNELS_16_TO_18_VALUES}
////////////////////////////////////////////////////////////////////
#define UPDATE_REGISTER 0x00
#define RESET_REGISTER  0x00
#define SHUTDOWN_REGISTER 0x01

#define I2C_ADDR_IS31FL3218 0xA8

// this array depicts how many registers will be send in each DataFor_IS32 structure
// Array of register counts for each group in DataFor_IS32
#define NUM_OF_REG_REGISTER_COUNTS { \
    NUM_OF_REG_SHUTDOWN_REGISTER_COUNT, \
    NUM_OF_REG_UPDATE_REGISTER_COUNT, \
    NUM_OF_REG_RESET_REGISTER_COUNT, \
    NUM_OF_REG_LED_CONTROL_REGISTER_COUNT, \
    NUM_OF_REG_PWM_REGISTER_1_TO_5_COUNT, \
    NUM_OF_REG_PWM_REGISTER_6_TO_10_COUNT, \
    NUM_OF_REG_PWM_REGISTER_11_TO_15_COUNT, \
    NUM_OF_REG_PWM_REGISTER_16_TO_18_COUNT  \
}



// Number of registers for each group in DataFor_IS32 array
#define NUM_OF_REG_SHUTDOWN_REGISTER_COUNT 1
#define NUM_OF_REG_UPDATE_REGISTER_COUNT 1
#define NUM_OF_REG_RESET_REGISTER_COUNT 1
#define NUM_OF_REG_LED_CONTROL_REGISTER_COUNT 3
#define NUM_OF_REG_PWM_REGISTER_1_TO_5_COUNT 5
#define NUM_OF_REG_PWM_REGISTER_6_TO_10_COUNT 5
#define NUM_OF_REG_PWM_REGISTER_11_TO_15_COUNT 5
#define NUM_OF_REG_PWM_REGISTER_16_TO_18_COUNT 3


#define LEN_LED_INDEX_ACTION_LIST 5





#define NUM_OF_INSTRUMENTS_PER_NUMBER_BUT 6






#endif /* INC_MACROS_H_ */
