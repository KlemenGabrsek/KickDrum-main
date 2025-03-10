/*
 * SwitchesInit.h
 *
 *  Created on: 21 Mar 2024
 *      Author: Klemen
 */

#ifndef INC_SWITCHESINIT_H_
#define INC_SWITCHESINIT_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * WHAT INDEX DOES FRONPANEL INSTRUMENT BUTTON HAVE
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define IndexBaseDrum 16
#define IndexSnareDrum 39
#define IndexCymal 38
#define IndexClaves 36
#define IndexConga 35
#define IndexCowbell 33
#define IndexTom 32
#define IndexRimShot 30


#define INSTRUMENTINDEX {IndexBaseDrum, IndexSnareDrum, IndexCymal, IndexClaves, IndexConga, IndexCowbell, IndexTom, IndexRimShot}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * WHAT INDEX DOES FRONPANEL NUMBER BUTTON HAVE, as we have varA/B, we actually have 32 buttons
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NumOfBut 32

#define NumBut_1  8
#define NumBut_2  9
#define NumBut_3  10
#define NumBut_4  11
#define NumBut_5  13
#define NumBut_6  12
#define NumBut_7  15
#define NumBut_8  14
#define NumBut_9  20
#define NumBut_10 22
#define NumBut_11 21
#define NumBut_12 23
#define NumBut_13 24
#define NumBut_14 25
#define NumBut_15 26
#define NumBut_16 27

#define NumBut_17 NumBut_1
#define NumBut_18 NumBut_2
#define NumBut_19 NumBut_3
#define NumBut_20 NumBut_4
#define NumBut_21 NumBut_5
#define NumBut_22 NumBut_6
#define NumBut_23 NumBut_7
#define NumBut_24 NumBut_8
#define NumBut_25 NumBut_9
#define NumBut_26 NumBut_10
#define NumBut_27 NumBut_11
#define NumBut_28 NumBut_12
#define NumBut_29 NumBut_13
#define NumBut_30 NumBut_14
#define NumBut_31 NumBut_15
#define NumBut_32 NumBut_16

#define NUMBUT_ARRAY { \
    NumBut_1, NumBut_2, NumBut_3, NumBut_4, NumBut_5, NumBut_6, NumBut_7, NumBut_8, \
    NumBut_9, NumBut_10, NumBut_11, NumBut_12, NumBut_13, NumBut_14, NumBut_15, NumBut_16, \
    NumBut_17, NumBut_18, NumBut_19, NumBut_20, NumBut_21, NumBut_22, NumBut_23, NumBut_24, \
    NumBut_25, NumBut_26, NumBut_27, NumBut_28, NumBut_29, NumBut_30, NumBut_31, NumBut_32 \
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *SENSOR FUNCTION FOR ALL  SWITCHES, LEFT AND RIGHT BUT
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 /*
* SensorFunction=0x0	0	CS pin becomes a capacitive sensor pin
		 * SensorFunction=0x1	 The CS pin outputs low level
		 * SensorFunction=0x2	The CS pin outputs high level.
		 * SensorFunction=0x3	 The CS pin becomes the high impedance.
**/



#define DATA_SENSOR_FUNCTION_L { SEN_FUN_CS0_L, SEN_FUN_CS1_L, SEN_FUN_CS2_L, SEN_FUN_CS3_L, \
                               SEN_FUN_CS4_L, SEN_FUN_CS5_L, SEN_FUN_CS6_L, SEN_FUN_CS7_L, \
                               SEN_FUN_CS8_L, SEN_FUN_CS9_L, SEN_FUN_CS10_L, SEN_FUN_CS11_L, \
                               SEN_FUN_CS12_L, SEN_FUN_CS13_L, SEN_FUN_CS14_L, SEN_FUN_CS15_L, \
                               SEN_FUN_CS16_L, SEN_FUN_CS17_L, SEN_FUN_CS18_L, SEN_FUN_CS19_L \
                             }

// Define functionality for each switch with _L added
#define SEN_FUN_CS0_L  0x00
#define SEN_FUN_CS1_L  0x00
#define SEN_FUN_CS2_L  0x00
#define SEN_FUN_CS3_L  0x00
#define SEN_FUN_CS4_L  0x00
#define SEN_FUN_CS5_L  0x00
#define SEN_FUN_CS6_L  0x00
#define SEN_FUN_CS7_L  0x00
#define SEN_FUN_CS8_L  0x00
#define SEN_FUN_CS9_L  0x00
#define SEN_FUN_CS10_L 0x00
#define SEN_FUN_CS11_L 0x00
#define SEN_FUN_CS12_L 0x00
#define SEN_FUN_CS13_L 0x00
#define SEN_FUN_CS14_L 0x00
#define SEN_FUN_CS15_L 0x00
#define SEN_FUN_CS16_L 0x00
#define SEN_FUN_CS17_L 0x00
#define SEN_FUN_CS18_L 0x00
#define SEN_FUN_CS19_L 0x00

#define DATA_SENSOR_FUNCTION_R { SEN_FUN_CS0_R, SEN_FUN_CS1_R, SEN_FUN_CS2_R, SEN_FUN_CS3_R, \
                               SEN_FUN_CS4_R, SEN_FUN_CS5_R, SEN_FUN_CS6_R, SEN_FUN_CS7_R, \
                               SEN_FUN_CS8_R, SEN_FUN_CS9_R, SEN_FUN_CS10_R, SEN_FUN_CS11_R, \
                               SEN_FUN_CS12_R, SEN_FUN_CS13_R, SEN_FUN_CS14_R, SEN_FUN_CS15_R, \
                               SEN_FUN_CS16_R, SEN_FUN_CS17_R, SEN_FUN_CS18_R, SEN_FUN_CS19_R \
                             }

// Define functionality for each switch with _R added
#define SEN_FUN_CS0_R  0x00
#define SEN_FUN_CS1_R  0x00
#define SEN_FUN_CS2_R  0x00
#define SEN_FUN_CS3_R  0x00
#define SEN_FUN_CS4_R  0x00
#define SEN_FUN_CS5_R  0x00
#define SEN_FUN_CS6_R  0x00
#define SEN_FUN_CS7_R  0x00
#define SEN_FUN_CS8_R  0x00
#define SEN_FUN_CS9_R  0x00
#define SEN_FUN_CS10_R 0x00
#define SEN_FUN_CS11_R 0x00
#define SEN_FUN_CS12_R 0x00
#define SEN_FUN_CS13_R 0x00
#define SEN_FUN_CS14_R 0x00
#define SEN_FUN_CS15_R 0x00
#define SEN_FUN_CS16_R 0x00
#define SEN_FUN_CS17_R 0x00
#define SEN_FUN_CS18_R 0x00
#define SEN_FUN_CS19_R 0x00


#define DATA_SENSOR_FUNCTION_L_R  { SEN_FUN_CS0_L, SEN_FUN_CS1_L, SEN_FUN_CS2_L, SEN_FUN_CS3_L, \
                               SEN_FUN_CS4_L, SEN_FUN_CS5_L, SEN_FUN_CS6_L, SEN_FUN_CS7_L, \
                               SEN_FUN_CS8_L, SEN_FUN_CS9_L, SEN_FUN_CS10_L, SEN_FUN_CS11_L, \
                               SEN_FUN_CS12_L, SEN_FUN_CS13_L, SEN_FUN_CS14_L, SEN_FUN_CS15_L, \
                               SEN_FUN_CS16_L, SEN_FUN_CS17_L, SEN_FUN_CS18_L, SEN_FUN_CS19_L, \
							   SEN_FUN_CS0_R, SEN_FUN_CS1_R, SEN_FUN_CS2_R, SEN_FUN_CS3_R, \
                               SEN_FUN_CS4_R, SEN_FUN_CS5_R, SEN_FUN_CS6_R, SEN_FUN_CS7_R, \
                               SEN_FUN_CS8_R, SEN_FUN_CS9_R, SEN_FUN_CS10_R, SEN_FUN_CS11_R, \
                               SEN_FUN_CS12_R, SEN_FUN_CS13_R, SEN_FUN_CS14_R, SEN_FUN_CS15_R, \
                               SEN_FUN_CS16_R, SEN_FUN_CS17_R, SEN_FUN_CS18_R, SEN_FUN_CS19_R \
                             }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * SWITCH ASSIGMENT WITH BUTTON ASSIGMEN -> CURRENTLY NOT USED !!
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DATA_TIPKA_NUM_ONPCB { NUM_ONPCB_CS0, NUM_ONPCB_CS1, NUM_ONPCB_CS2, NUM_ONPCB_CS3,\
																NUM_ONPCB_CS4, NUM_ONPCB_CS5, NUM_ONPCB_CS6, NUM_ONPCB_CS7,\
																NUM_ONPCB_CS8, NUM_ONPCB_CS9, NUM_ONPCB_CS10, NUM_ONPCB_CS11,\
																NUM_ONPCB_CS12, NUM_ONPCB_CS13, NUM_ONPCB_CS14, NUM_ONPCB_CS15,\
																NUM_ONPCB_CS16, NUM_ONPCB_CS18, NUM_ONPCB_CS19\
															}

//tu določamo kateri switch je vezan na katero zunanjo tipko
#define NUM_ONPCB_CS0 	210	//slider 2 tipka 1		//OUT LEVEL
#define NUM_ONPCB_CS1 	200//slider 2 tipka 0
#define NUM_ONPCB_CS2	 	202//slider 2 tipka 2
#define NUM_ONPCB_CS3		3
#define NUM_ONPCB_CS4 	4
#define NUM_ONPCB_CS5 	5
#define NUM_ONPCB_CS6	 	6
#define NUM_ONPCB_CS7		 7
#define NUM_ONPCB_CS8	 	8
#define NUM_ONPCB_CS9	 	9
#define NUM_ONPCB_CS10 	10
#define NUM_ONPCB_CS11	11
#define NUM_ONPCB_CS12  12
#define NUM_ONPCB_CS13 	13
#define NUM_ONPCB_CS14	0
#define NUM_ONPCB_CS15	1
#define NUM_ONPCB_CS16	2 //BD tipka
#define NUM_ONPCB_CS17	100 //slider1 tipka 0 //DECAY
#define NUM_ONPCB_CS18	110//slider1 tipka 1
#define NUM_ONPCB_CS19	120//slider1 tipka 2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * TRESHHOLD FOR ALL DATA SWITCHES, LEFT AND RIGHT BUT
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DATA_TRESHOLD_ONOFF_L { TH_ON_CS0_L, TH_OFF_CS0_L, \
															  TH_ON_CS1_L, TH_OFF_CS1_L, \
															  TH_ON_CS2_L, TH_OFF_CS2_L, \
															  TH_ON_CS3_L, TH_OFF_CS3_L, \
															  TH_ON_CS4_L, TH_OFF_CS4_L, \
															  TH_ON_CS5_L, TH_OFF_CS5_L, \
															  TH_ON_CS6_L, TH_OFF_CS6_L, \
															  TH_ON_CS7_L, TH_OFF_CS7_L, \
															  TH_ON_CS8_L, TH_OFF_CS8_L, \
															  TH_ON_CS9_L, TH_OFF_CS9_L, \
															  TH_ON_CS10_L, TH_OFF_CS10_L, \
															  TH_ON_CS11_L, TH_OFF_CS11_L, \
															  TH_ON_CS12_L, TH_OFF_CS12_L, \
															  TH_ON_CS13_L, TH_OFF_CS13_L, \
															  TH_ON_CS14_L, TH_OFF_CS14_L, \
															  TH_ON_CS15_L, TH_OFF_CS15_L, \
															  TH_ON_CS16_L, TH_OFF_CS16_L, \
															  TH_ON_CS17_L, TH_OFF_CS17_L, \
															  TH_ON_CS18_L, TH_OFF_CS18_L, \
															  TH_ON_CS19_L, TH_OFF_CS19_L \
															}

// Define ONOFF thresholds with _L added
#define TH_ON_CS0_L 0xC8
#define TH_OFF_CS0_L 0x64
#define TH_ON_CS1_L 0xC8
#define TH_OFF_CS1_L 0x64
#define TH_ON_CS2_L 0xC8
#define TH_OFF_CS2_L 0x64
#define TH_ON_CS3_L 0xC8
#define TH_OFF_CS3_L 0x64
#define TH_ON_CS4_L 0xC8
#define TH_OFF_CS4_L 0x64
#define TH_ON_CS5_L 0xC8
#define TH_OFF_CS5_L 0x64
#define TH_ON_CS6_L 0xC8
#define TH_OFF_CS6_L 0x64
#define TH_ON_CS7_L 0xC8
#define TH_OFF_CS7_L 0x64
#define TH_ON_CS8_L 0xC8
#define TH_OFF_CS8_L 0x64
#define TH_ON_CS9_L 0xC8
#define TH_OFF_CS9_L 0x64
#define TH_ON_CS10_L 0xC8
#define TH_OFF_CS10_L 0x64
#define TH_ON_CS11_L 0xC8
#define TH_OFF_CS11_L 0x64
#define TH_ON_CS12_L 0xC8
#define TH_OFF_CS12_L 0x64
#define TH_ON_CS13_L 0xC8
#define TH_OFF_CS13_L 0x64
#define TH_ON_CS14_L 0xC8
#define TH_OFF_CS14_L 0x64
#define TH_ON_CS15_L 0xC8
#define TH_OFF_CS15_L 0x64
#define TH_ON_CS16_L 0xC8
#define TH_OFF_CS16_L 0x64
#define TH_ON_CS17_L 0xC8
#define TH_OFF_CS17_L 0x64
#define TH_ON_CS18_L 0xC8
#define TH_OFF_CS18_L 0x64
#define TH_ON_CS19_L 0xC8
#define TH_OFF_CS19_L 0x64

#define DATA_TRESHOLD_ONOFF_R { TH_ON_CS0_R, TH_OFF_CS0_R, \
                                TH_ON_CS1_R, TH_OFF_CS1_R, \
                                TH_ON_CS2_R, TH_OFF_CS2_R, \
                                TH_ON_CS3_R, TH_OFF_CS3_R, \
                                TH_ON_CS4_R, TH_OFF_CS4_R, \
                                TH_ON_CS5_R, TH_OFF_CS5_R, \
                                TH_ON_CS6_R, TH_OFF_CS6_R, \
                                TH_ON_CS7_R, TH_OFF_CS7_R, \
                                TH_ON_CS8_R, TH_OFF_CS8_R, \
                                TH_ON_CS9_R, TH_OFF_CS9_R, \
                                TH_ON_CS10_R, TH_OFF_CS10_R, \
                                TH_ON_CS11_R, TH_OFF_CS11_R, \
                                TH_ON_CS12_R, TH_OFF_CS12_R, \
                                TH_ON_CS13_R, TH_OFF_CS13_R, \
                                TH_ON_CS14_R, TH_OFF_CS14_R, \
                                TH_ON_CS15_R, TH_OFF_CS15_R, \
                                TH_ON_CS16_R, TH_OFF_CS16_R, \
                                TH_ON_CS17_R, TH_OFF_CS17_R, \
                                TH_ON_CS18_R, TH_OFF_CS18_R, \
                                TH_ON_CS19_R, TH_OFF_CS19_R \
                              }

// Define ONOFF thresholds with _R added
#define TH_ON_CS0_R 0xC8
#define TH_OFF_CS0_R 0x64
#define TH_ON_CS1_R 0xC8
#define TH_OFF_CS1_R 0x64
#define TH_ON_CS2_R 0xC8
#define TH_OFF_CS2_R 0x64
#define TH_ON_CS3_R 0xC8
#define TH_OFF_CS3_R 0x64
#define TH_ON_CS4_R 0xC8
#define TH_OFF_CS4_R 0x64
#define TH_ON_CS5_R 0xC8
#define TH_OFF_CS5_R 0x64
#define TH_ON_CS6_R 0xC8
#define TH_OFF_CS6_R 0x64
#define TH_ON_CS7_R 0xC8
#define TH_OFF_CS7_R 0x64
#define TH_ON_CS8_R 0xC8
#define TH_OFF_CS8_R 0x64
#define TH_ON_CS9_R 0xC8
#define TH_OFF_CS9_R 0x64
#define TH_ON_CS10_R 0xC8
#define TH_OFF_CS10_R 0x64
#define TH_ON_CS11_R 0xC8
#define TH_OFF_CS11_R 0x64
#define TH_ON_CS12_R 0xC8
#define TH_OFF_CS12_R 0x64
#define TH_ON_CS13_R 0xC8
#define TH_OFF_CS13_R 0x64
#define TH_ON_CS14_R 0xC8
#define TH_OFF_CS14_R 0x64
#define TH_ON_CS15_R 0xC8
#define TH_OFF_CS15_R 0x64
#define TH_ON_CS16_R 0xC8
#define TH_OFF_CS16_R 0x64
#define TH_ON_CS17_R 0xC8
#define TH_OFF_CS17_R 0x64
#define TH_ON_CS18_R 0xC8
#define TH_OFF_CS18_R 0x64
#define TH_ON_CS19_R 0xC8
#define TH_OFF_CS19_R 0x64

#define DATA_TRESHOLD_ONOFF_L_R { TH_ON_CS0_L, TH_OFF_CS0_L, \
																	  TH_ON_CS1_L, TH_OFF_CS1_L, \
																	  TH_ON_CS2_L, TH_OFF_CS2_L, \
																	  TH_ON_CS3_L, TH_OFF_CS3_L, \
																	  TH_ON_CS4_L, TH_OFF_CS4_L, \
																	  TH_ON_CS5_L, TH_OFF_CS5_L, \
																	  TH_ON_CS6_L, TH_OFF_CS6_L, \
																	  TH_ON_CS7_L, TH_OFF_CS7_L, \
																	  TH_ON_CS8_L, TH_OFF_CS8_L, \
																	  TH_ON_CS9_L, TH_OFF_CS9_L, \
																	  TH_ON_CS10_L, TH_OFF_CS10_L, \
																	  TH_ON_CS11_L, TH_OFF_CS11_L, \
																	  TH_ON_CS12_L, TH_OFF_CS12_L, \
																	  TH_ON_CS13_L, TH_OFF_CS13_L, \
																	  TH_ON_CS14_L, TH_OFF_CS14_L, \
																	  TH_ON_CS15_L, TH_OFF_CS15_L, \
																	  TH_ON_CS16_L, TH_OFF_CS16_L, \
																	  TH_ON_CS17_L, TH_OFF_CS17_L, \
																	  TH_ON_CS18_L, TH_OFF_CS18_L, \
																	  TH_ON_CS19_L, TH_OFF_CS19_L, \
																		TH_ON_CS1_R, TH_OFF_CS1_R, \
																		TH_ON_CS2_R, TH_OFF_CS2_R, \
																		TH_ON_CS3_R, TH_OFF_CS3_R, \
																		TH_ON_CS4_R, TH_OFF_CS4_R, \
																		TH_ON_CS5_R, TH_OFF_CS5_R, \
																		TH_ON_CS6_R, TH_OFF_CS6_R, \
																		TH_ON_CS7_R, TH_OFF_CS7_R, \
																		TH_ON_CS8_R, TH_OFF_CS8_R, \
																		TH_ON_CS9_R, TH_OFF_CS9_R, \
																		TH_ON_CS10_R, TH_OFF_CS10_R, \
																		TH_ON_CS11_R, TH_OFF_CS11_R, \
																		TH_ON_CS12_R, TH_OFF_CS12_R, \
																		TH_ON_CS13_R, TH_OFF_CS13_R, \
																		TH_ON_CS14_R, TH_OFF_CS14_R, \
																		TH_ON_CS15_R, TH_OFF_CS15_R, \
																		TH_ON_CS16_R, TH_OFF_CS16_R, \
																		TH_ON_CS17_R, TH_OFF_CS17_R, \
																		TH_ON_CS18_R, TH_OFF_CS18_R, \
																		TH_ON_CS19_R, TH_OFF_CS19_R,\
																		TH_ON_CS19_R, TH_OFF_CS19_R\
																	  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * DATA SENSITIVITY, LEFT AND RIGHT BUT
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DATA_SENSITIVITY_BUT_L_R { \
    SENSI_CS0_L, SENSI_CS1_L, SENSI_CS2_L, SENSI_CS3_L, SENSI_CS4_L, \
    SENSI_CS5_L, SENSI_CS6_L, SENSI_CS7_L, SENSI_CS8_L, SENSI_CS9_L, \
    SENSI_CS10_L, SENSI_CS11_L, SENSI_CS12_L, SENSI_CS13_L, SENSI_CS14_L, \
    SENSI_CS15_L, SENSI_CS16_L, SENSI_CS17_L, SENSI_CS18_L, SENSI_CS19_L, \
    SENSI_CS0_R, SENSI_CS1_R, SENSI_CS2_R, SENSI_CS3_R, SENSI_CS4_R, \
    SENSI_CS5_R, SENSI_CS6_R, SENSI_CS7_R, SENSI_CS8_R, SENSI_CS9_R, \
    SENSI_CS10_R, SENSI_CS11_R, SENSI_CS12_R, SENSI_CS13_R, SENSI_CS14_R, \
    SENSI_CS15_R, SENSI_CS16_R, SENSI_CS17_R, SENSI_CS18_R, SENSI_CS19_R \
}

// Define sensitivity values for each switch with _L and _R
#define SENSI_CS0_L   0x07
#define SENSI_CS1_L   0x07
#define SENSI_CS2_L   0x07
#define SENSI_CS3_L   0x07
#define SENSI_CS4_L   0x07
#define SENSI_CS5_L   0x07
#define SENSI_CS6_L   0x07
#define SENSI_CS7_L   0x07
#define SENSI_CS8_L   0x07
#define SENSI_CS9_L   0x07
#define SENSI_CS10_L  0x07
#define SENSI_CS11_L  0x07
#define SENSI_CS12_L  0x07
#define SENSI_CS13_L  0x07
#define SENSI_CS14_L  0x07
#define SENSI_CS15_L  0x07
#define SENSI_CS16_L  0x07
#define SENSI_CS17_L  0x07
#define SENSI_CS18_L  0x07
#define SENSI_CS19_L  0x07

#define SENSI_CS0_R   0x07
#define SENSI_CS1_R   0x07
#define SENSI_CS2_R   0x07
#define SENSI_CS3_R   0x07
#define SENSI_CS4_R   0x07
#define SENSI_CS5_R   0x07
#define SENSI_CS6_R   0x07
#define SENSI_CS7_R   0x07
#define SENSI_CS8_R   0x07
#define SENSI_CS9_R   0x07
#define SENSI_CS10_R  0x07
#define SENSI_CS11_R  0x07
#define SENSI_CS12_R  0x07
#define SENSI_CS13_R  0x07
#define SENSI_CS14_R  0x07
#define SENSI_CS15_R  0x07
#define SENSI_CS16_R  0x07
#define SENSI_CS17_R  0x07
#define SENSI_CS18_R  0x07
#define SENSI_CS19_R  0x07




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * LED STAUTS ALL LEDS
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// tu dolocamo status LEDic, kako svetijo
/*
 *  *   0 LED Off
	 * 1 LED ON
	 * 2 LED Slow blinking
	 * 3 LED fast blinking
 */
#define DATA_LED_STATUS  { LEDStatus0, LEDStatus1, LEDStatus2, LEDStatus3, \
    LEDStatus4, LEDStatus5, LEDStatus6, LEDStatus7, \
    LEDStatus8, LEDStatus9, LEDStatus10, LEDStatus11, \
    LEDStatus12, LEDStatus13, LEDStatus14, LEDStatus15, \
    LEDStatus16, LEDStatus17, LEDStatus18, LEDStatus19, \
    LEDStatus20, LEDStatus21, LEDStatus22, LEDStatus23, \
    LEDStatus24, LEDStatus25, LEDStatus26, LEDStatus27, \
    LEDStatus28, LEDStatus29, LEDStatus30, LEDStatus31, \
    LEDStatus32, LEDStatus33, LEDStatus34, LEDStatus35, \
    LEDStatus36, LEDStatus37, LEDStatus38, LEDStatus39 \
}

#define LEDStatus0 	0x01
#define LEDStatus1	0x01
#define LEDStatus2	0x01
#define LEDStatus3	0x01
#define LEDStatus4	0x01
#define LEDStatus5	0x01
#define LEDStatus6	0x01
#define LEDStatus7	0x01
#define LEDStatus8	0x01
#define LEDStatus9	0x01
#define LEDStatus10	0x01
#define LEDStatus11	0x01
#define LEDStatus12 0x01
#define LEDStatus13	0x01
#define LEDStatus14	0x01
#define LEDStatus15	0x01
#define LEDStatus16	0x01
#define LEDStatus17	0x01
#define LEDStatus18	0x01
#define LEDStatus19	0x01
#define LEDStatus20	0x01
#define LEDStatus21	0x01
#define LEDStatus22	0x01
#define LEDStatus23	0x01
#define LEDStatus24	0x01
#define LEDStatus25	0x01
#define LEDStatus26	0x01
#define LEDStatus27	0x01
#define LEDStatus28	0x01
#define LEDStatus29	0x01
#define LEDStatus30	0x01
#define LEDStatus31	0x01
#define LEDStatus32	0x01
#define LEDStatus33	0x01
#define LEDStatus34	0x01
#define LEDStatus35	0x01
#define LEDStatus36	0x01
#define LEDStatus37	0x01
#define LEDStatus38	0x01
#define LEDStatus39	0x01


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * LED INTENSITY & LED BLINKING SETTINGS
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LED_0_BLINKY  0x0
#define LED_1_BLINKY  0x0
#define LED_2_BLINKY  0x0
#define LED_3_BLINKY  0x0
#define LED_4_BLINKY  0x0
#define LED_5_BLINKY  0x0
#define LED_6_BLINKY  0x0
#define LED_7_BLINKY  0x0
#define LED_8_BLINKY  0x0
#define LED_9_BLINKY  0x0
#define LED_10_BLINKY 0x0
#define LED_11_BLINKY 0x0
#define LED_12_BLINKY 0x0
#define LED_13_BLINKY 0x0
#define LED_14_BLINKY 0x0
#define LED_15_BLINKY 0x0
#define LED_16_BLINKY 0x0
#define LED_17_BLINKY 0x0
#define LED_18_BLINKY 0x0
#define LED_19_BLINKY 0x0
#define LED_20_BLINKY 0x0
#define LED_21_BLINKY 0x0
#define LED_22_BLINKY 0x0
#define LED_23_BLINKY 0x0
#define LED_24_BLINKY 0x0
#define LED_25_BLINKY 0x0
#define LED_26_BLINKY 0x0
#define LED_27_BLINKY 0x0
#define LED_28_BLINKY 0x0
#define LED_29_BLINKY 0x0
#define LED_30_BLINKY 0x0
#define LED_31_BLINKY 0x0
#define LED_32_BLINKY 0x0
#define LED_33_BLINKY 0x0
#define LED_34_BLINKY 0x0
#define LED_35_BLINKY 0x0
#define LED_36_BLINKY 0x0
#define LED_37_BLINKY 0x0
#define LED_38_BLINKY 0x0
#define LED_39_BLINKY 0x0

#define LED_BLINKY { \
    LED_0_BLINKY, LED_1_BLINKY, LED_2_BLINKY, LED_3_BLINKY, LED_4_BLINKY, \
    LED_5_BLINKY, LED_6_BLINKY, LED_7_BLINKY, LED_8_BLINKY, LED_9_BLINKY, \
    LED_10_BLINKY, LED_11_BLINKY, LED_12_BLINKY, LED_13_BLINKY, LED_14_BLINKY, \
    LED_15_BLINKY, LED_16_BLINKY, LED_17_BLINKY, LED_18_BLINKY, LED_19_BLINKY, \
    LED_20_BLINKY, LED_21_BLINKY, LED_22_BLINKY, LED_23_BLINKY, LED_24_BLINKY, \
    LED_25_BLINKY, LED_26_BLINKY, LED_27_BLINKY, LED_28_BLINKY, LED_29_BLINKY, \
    LED_30_BLINKY, LED_31_BLINKY, LED_32_BLINKY, LED_33_BLINKY, LED_34_BLINKY, \
    LED_35_BLINKY, LED_36_BLINKY, LED_37_BLINKY, LED_38_BLINKY, LED_39_BLINKY \
}



#define LED_0_INTENSITY 0xFF
#define LED_1_INTENSITY 0xFF
#define LED_2_INTENSITY 0xFF
#define LED_3_INTENSITY 0xFF
#define LED_4_INTENSITY 0xFF
#define LED_5_INTENSITY 0xFF
#define LED_6_INTENSITY 0xFF
#define LED_7_INTENSITY 0xFF
#define LED_8_INTENSITY 0xFF
#define LED_9_INTENSITY 0xFF
#define LED_10_INTENSITY 0xFF
#define LED_11_INTENSITY 0xFF
#define LED_12_INTENSITY 0xFF
#define LED_13_INTENSITY 0xFF
#define LED_14_INTENSITY 0xFF
#define LED_15_INTENSITY 0xFF
#define LED_16_INTENSITY 0xFF
#define LED_17_INTENSITY 0xFF
#define LED_18_INTENSITY 0xFF
#define LED_19_INTENSITY 0xFF
#define LED_20_INTENSITY 0xFF
#define LED_21_INTENSITY 0xFF
#define LED_22_INTENSITY 0xFF
#define LED_23_INTENSITY 0xFF
#define LED_24_INTENSITY 0xFF
#define LED_25_INTENSITY 0xFF
#define LED_26_INTENSITY 0xFF
#define LED_27_INTENSITY 0xFF
#define LED_28_INTENSITY 0xFF
#define LED_29_INTENSITY 0xFF
#define LED_30_INTENSITY 0xFF
#define LED_31_INTENSITY 0xFF
#define LED_32_INTENSITY 0xFF
#define LED_33_INTENSITY 0xFF
#define LED_34_INTENSITY 0xFF
#define LED_35_INTENSITY 0xFF
#define LED_36_INTENSITY 0xFF
#define LED_37_INTENSITY 0xFF
#define LED_38_INTENSITY 0xFF
#define LED_39_INTENSITY 0xFF


#define LED_INTENSITY { \
    LED_0_INTENSITY, LED_1_INTENSITY, LED_2_INTENSITY, LED_3_INTENSITY, LED_4_INTENSITY, \
    LED_5_INTENSITY, LED_6_INTENSITY, LED_7_INTENSITY, LED_8_INTENSITY, LED_9_INTENSITY, \
    LED_10_INTENSITY, LED_11_INTENSITY, LED_12_INTENSITY, LED_13_INTENSITY, LED_14_INTENSITY, \
    LED_15_INTENSITY, LED_16_INTENSITY, LED_17_INTENSITY, LED_18_INTENSITY, LED_19_INTENSITY, \
    LED_20_INTENSITY, LED_21_INTENSITY, LED_22_INTENSITY, LED_23_INTENSITY, LED_24_INTENSITY, \
    LED_25_INTENSITY, LED_26_INTENSITY, LED_27_INTENSITY, LED_28_INTENSITY, LED_29_INTENSITY, \
    LED_30_INTENSITY, LED_31_INTENSITY, LED_32_INTENSITY, LED_33_INTENSITY, \
    LED_34_INTENSITY, LED_35_INTENSITY, LED_36_INTENSITY, LED_37_INTENSITY, LED_38_INTENSITY, LED_39_INTENSITY \
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * default values of SWitch ON, SWITCH OFF AND LED STATUS
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LED_1_DEFAULT_VAL 0x0
#define LED_2_DEFAULT_VAL 0x0
#define LED_3_DEFAULT_VAL 0x0
#define LED_4_DEFAULT_VAL 0x0
#define LED_5_DEFAULT_VAL 0x0
#define LED_6_DEFAULT_VAL 0x0
#define LED_7_DEFAULT_VAL 0x0
#define LED_8_DEFAULT_VAL 0x0
#define LED_9_DEFAULT_VAL 0x0
#define LED_10_DEFAULT_VAL 0x0
#define LED_11_DEFAULT_VAL 0x0
#define LED_12_DEFAULT_VAL 0x0
#define LED_13_DEFAULT_VAL 0x0
#define LED_14_DEFAULT_VAL 0x0
#define LED_15_DEFAULT_VAL 0x0
#define LED_16_DEFAULT_VAL 0x0
#define LED_17_DEFAULT_VAL 0x0
#define LED_18_DEFAULT_VAL 0x0
#define LED_19_DEFAULT_VAL 0x0
#define LED_20_DEFAULT_VAL 0x0
#define LED_21_DEFAULT_VAL 0x0
#define LED_22_DEFAULT_VAL 0x0
#define LED_23_DEFAULT_VAL 0x0
#define LED_24_DEFAULT_VAL 0x0
#define LED_25_DEFAULT_VAL 0x0
#define LED_26_DEFAULT_VAL 0x0
#define LED_27_DEFAULT_VAL 0x0
#define LED_28_DEFAULT_VAL 0x0
#define LED_29_DEFAULT_VAL 0x0
#define LED_30_DEFAULT_VAL 0x0
#define LED_31_DEFAULT_VAL 0x0
#define LED_32_DEFAULT_VAL 0x0
#define LED_33_DEFAULT_VAL 0x0
#define LED_34_DEFAULT_VAL 0x0
#define LED_35_DEFAULT_VAL 0x0
#define LED_36_DEFAULT_VAL 0x0
#define LED_37_DEFAULT_VAL 0x0
#define LED_38_DEFAULT_VAL 0x0
#define LED_39_DEFAULT_VAL 0x0
#define LED_40_DEFAULT_VAL 0x0

#define LED_DEFAULT_VAL { \
    LED_1_DEFAULT_VAL, LED_2_DEFAULT_VAL, LED_3_DEFAULT_VAL, LED_4_DEFAULT_VAL, LED_5_DEFAULT_VAL, \
    LED_6_DEFAULT_VAL, LED_7_DEFAULT_VAL, LED_8_DEFAULT_VAL, LED_9_DEFAULT_VAL, LED_10_DEFAULT_VAL, \
    LED_11_DEFAULT_VAL, LED_12_DEFAULT_VAL, LED_13_DEFAULT_VAL, LED_14_DEFAULT_VAL, LED_15_DEFAULT_VAL, \
    LED_16_DEFAULT_VAL, LED_17_DEFAULT_VAL, LED_18_DEFAULT_VAL, LED_19_DEFAULT_VAL, LED_20_DEFAULT_VAL, \
    LED_21_DEFAULT_VAL, LED_22_DEFAULT_VAL, LED_23_DEFAULT_VAL, LED_24_DEFAULT_VAL, LED_25_DEFAULT_VAL, \
    LED_26_DEFAULT_VAL, LED_27_DEFAULT_VAL, LED_28_DEFAULT_VAL, LED_29_DEFAULT_VAL, LED_30_DEFAULT_VAL, \
    LED_31_DEFAULT_VAL, LED_32_DEFAULT_VAL, LED_33_DEFAULT_VAL, LED_34_DEFAULT_VAL, LED_35_DEFAULT_VAL, \
    LED_36_DEFAULT_VAL, LED_37_DEFAULT_VAL, LED_38_DEFAULT_VAL, LED_39_DEFAULT_VAL, LED_40_DEFAULT_VAL \
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * LED and SWITCH MAPPING
 * switches will go from 0 to 39
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define LED_IS32_OUT0        12
#define LED_IS32_OUT1        12
#define LED_IS32_OUT2        12
#define LED_IS32_OUT3        13
#define LED_IS32_OUT4        14
#define LED_IS32_OUT5        15
#define LED_IS32_OUT6        16
#define LED_IS32_OUT7        10
#define LED_IS32_OUT8        3
#define LED_IS32_OUT9        6
#define LED_IS32_OUT10       7
#define LED_IS32_OUT11       8
#define LED_IS32_OUT12       11
#define LED_IS32_OUT13       9
#define LED_IS32_OUT14       5
#define LED_IS32_OUT15       4
#define LED_IS32_OUT16       1
#define LED_IS32_OUT17       2
#define LED_IS32_OUT18       2
#define LED_IS32_OUT19       2
#define LED_IS32_OUT20       5
#define LED_IS32_OUT21       1
#define LED_IS32_OUT22       0
#define LED_IS32_OUT23       2
#define LED_IS32_OUT24       3
#define LED_IS32_OUT25       4
#define LED_IS32_OUT26       7
#define LED_IS32_OUT27       8
#define LED_IS32_OUT28       9
#define LED_IS32_OUT29       12
#define LED_IS32_OUT30       10
#define LED_IS32_OUT31       9
#define LED_IS32_OUT32       13
#define LED_IS32_OUT33       14
#define LED_IS32_OUT34       9
#define LED_IS32_OUT35       15
#define LED_IS32_OUT36       16
#define LED_IS32_OUT37       -1
#define LED_IS32_OUT38       11
#define LED_IS32_OUT39       6


// Array of LED values defined using #define
#define LED_INDEX_IN_IS32 { \
    LED_IS32_OUT0, LED_IS32_OUT1, LED_IS32_OUT2, LED_IS32_OUT3, \
    LED_IS32_OUT4, LED_IS32_OUT5, LED_IS32_OUT6, LED_IS32_OUT7, \
    LED_IS32_OUT8, LED_IS32_OUT9, LED_IS32_OUT10, LED_IS32_OUT11, \
    LED_IS32_OUT12, LED_IS32_OUT13, LED_IS32_OUT14, LED_IS32_OUT15, \
    LED_IS32_OUT16, LED_IS32_OUT17, LED_IS32_OUT18, LED_IS32_OUT19, \
    LED_IS32_OUT20, LED_IS32_OUT21, LED_IS32_OUT22, LED_IS32_OUT23, \
    LED_IS32_OUT24, LED_IS32_OUT25, LED_IS32_OUT26, LED_IS32_OUT27, \
    LED_IS32_OUT28, LED_IS32_OUT29, LED_IS32_OUT30, LED_IS32_OUT31, \
    LED_IS32_OUT32, LED_IS32_OUT33, LED_IS32_OUT34, LED_IS32_OUT35, \
    LED_IS32_OUT36, LED_IS32_OUT37, LED_IS32_OUT38, LED_IS32_OUT39  \
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////






#endif /* INC_SWITCHESINIT_H_ */
