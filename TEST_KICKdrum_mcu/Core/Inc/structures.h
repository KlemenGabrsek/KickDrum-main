/*
 * structures.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Klemen
 */

#ifndef INC_STRUCTURES_H_
#define INC_STRUCTURES_H_

#include <stdio.h>
#include "stm32f4xx_hal.h"
//#include "functions.h"

struct Switch{
	//Switch info
	uint8_t SwitchNumOnIC;
	//uint8_t TipkaNumOnPCB;

	//The following data describes switch state
	uint8_t SwitchOnDetection;
	uint8_t SwitchOffDetection;
	uint8_t SwitchLongPressDetection;
	uint8_t SwitchRepeatedLongPressDetection;
	uint8_t MultiPatternSwitchOnDetection;
	uint8_t MultiPatternSwitchOffDetection;
	uint8_t UnexplectedLongPressDetection;



	// The following data describes switch parameters that need to be written to registers at chip initialization
	uint8_t SensorFunction;
		/*
		 * SensorFunction=0x0		CS pin becomes a capacitive sensor pin
		 * SensorFunction=0	x1	 The CS pin outputs low level
		 * SensorFunction=0	x2	The CS pin outputs high level.
		 * SensorFunction=0	x3	 The CS pin becomes the high impedance.
		 */
	uint8_t Sensitivity;
		/*
		 * 15 steps, lower value->higher sensitivity
		 * unallowable setting value -> switch disabled
		 * allowable setting range 0x1(high)<=Sensitivity<=0xF(low)
		 * recommended range 0x3<=Sensitivity<=0xF
		 */
	uint8_t SwitchONTreshold;
	uint8_t SwitchOFFTreshold;
		/*
		 * unallowable setting value -> switch disabled
		 * allowable setting range 0x3<SwitchOFFTreshold<SwitchONTreshold<=0xF(low)
		 *Recommended range: 0x40 <= SwitchONTreshold <= 0xE0
		 *Recommended range 0x20 <=SwitchOFFTreshold
		 */

	/*
	 *
	 */
	uint8_t SwitchDetectionTime;
	/*
	 * Delay for IC to detect ON state
	 * The time until detecting the ON state of switch = SwitchDetectionTime*10ms
	 */
	uint8_t MultiplePatternSwitchesAssignment;
	/*
	 * There can be 8 groups with 2 or more switches. If all switches within a group are pressed, an interrupt is triggered.
	 *  Group 1: MultiplePatternSwitchesAssignment=A
	 *  Group 2: MultiplePatternSwitchesAssignment=B
	 *  Group 3: MultiplePatternSwitchesAssignment=C
	 *  Group 4: MultiplePatternSwitchesAssignment=D
	 *  Group 5: MultiplePatternSwitchesAssignment=E
	 *  Group 6: MultiplePatternSwitchesAssignment=F
	 *  Group 7: MultiplePatternSwitchesAssignment=G
	 *  Group 8: MultiplePatternSwitchesAssignment=H
	 */
	uint8_t LEDIndexInIS32;

	uint8_t LEDOnOff;
	/*
		 * 0 LED Off
		 *1  LED On
		 */
	uint8_t LEDIntensity;
	/*
			 * 0 -255
*/
	uint8_t LEDBlinky;
	/*
	 * 0- No blinky
	 * 1- Blinky Normal
	 *2- Blinky Fast
	 */
};

struct SendData_BUT21{
	// Z vsako s SendData lahko pišemo v pet registrov, število registrov v katere se bo pisalo je zapisano v  NumOfRegForSendData_BUT21.
	uint16_t  SizeOfDataBlockInIC ;
	I2C_HandleTypeDef *I2CHandlerForBUT21;
	uint16_t Addr_I2C_BUT21;
	uint8_t NumOfRegForSendData_BUT21;
	uint8_t *RegisterNameForSendData_BUT21[5];
	uint16_t RegistersSizeForSendData_BUT21[5];
	uint16_t RegistersAddrForSendData_BUT21[5];

};

struct ReceiveData_BUT21{

	uint16_t SizeOfDataBlockInIC;
	I2C_HandleTypeDef *I2CHandlerForBUT21;
	uint16_t Addr_I2C_BUT21;
	uint8_t NumOfRegForReceivedData_BUT21;
	uint8_t **RegisterNameForReceivedData_BUT21;
	uint16_t RegistersSizeForReceivedData_BUT21[5];
	uint16_t RegistersAddrForReceivedData_BUT21[5];

};

struct Slider{
	char * NameOfSliderOnPCBA;
	/*
	 * SwitchNumber stores values of switch numbers, eg, for CS0 a 0 is tored, for CS10 a 10 is stored
	  * the sequence must be such that the first string represents switch0, the second switch1 and the third switch 2
	 */
	uint8_t SwitchNumber[ NUMBER_OF_SLIDERS];
	/*
	 * CrossSectionNumber presents which multipattern switch assigment has been trigered, multipatterned switch assigments are marked
	 * by letters, each letter presents two switches that must be pressed simultaneosly to trigger
	 */
	uint8_t CrossSectionNumber[ NUMBER_OF_SLIDERS];
	/*
	 * The SW name of all 3 switches is put here eg. :
	 * {"CS0","CS1","CS2"} (each end of the string has a null temination)
	 * the sequence must be such that the first string represents switch0, the second switch1 and the third switch 2
	 */
	char *SwitchName[ NUMBER_OF_SLIDERS];
	/*
	 *Names of all 3 crosssections are put in here, eg
	 * {"CS0CS1","CS1CS2","CS0CS2"} (each end of the string has a null temination)
	 * CrossSection01, CrossSection12,CrossSection02
	 * this data is also written in multipattern switch assigment
	 */
	char * CrossSectionName[ NUMBER_OF_SLIDERS];
	/*
	 * status of switches and cross sections
	 * 0 - switch in off state
	 * 1 - switch in on state
	 */
	uint8_t Switch[ NUMBER_OF_SLIDERS];
	// switch0, switch1,switch2
	uint8_t CrossSection[ NUMBER_OF_SLIDERS];
	// CrossSection01, CrossSection12,CrossSection02
	/*
	 * When status is being written to switches or crossection that time will be logeed
	 * with HAL_GetTick()-> returns ms from MCU start
	 * with 32bits whis could be 49 days
	 */
	uint32_t SwitchTimeON[ NUMBER_OF_SLIDERS];
	// switch0 time on, switch1 time on ,switch2 time on
	uint32_t SwitchTimeOFF[ NUMBER_OF_SLIDERS];
		// switch0 time off, switch1 time off ,switch2 time off
	uint32_t CrossSectionTimeON[ NUMBER_OF_SLIDERS];
	// CrossSection01 Time on, CrossSection12 Time on,CrossSection23Time on
	uint32_t CrossSectionTimeOFF[ NUMBER_OF_SLIDERS];
		// CrossSection01 Time off, CrossSection12 Time off,CrossSection23Time off
	/*
	 * This represent the slider value,  min :0, max :100
	 */
	uint8_t Index;
	/*
	 *Pointer too a function that will determinate if index can or can not change
	 */
	//uint8_t  (*ChangeIndexVal)(); //potrebno še posodobiti s parametri

};

//each instance of an instrument has the following parameters
struct Instrument {
    //char Name[2];
    uint8_t Accent;
    uint8_t OutLevel;
    uint8_t Decay;
};

//each button can have up to 6 instrument playing at the same time
struct Button{
	struct Instrument pointersToInstrument[NUM_OF_INSTRUMENTS_PER_NUMBER_BUT];
	uint8_t NumOfInstruments;
	uint8_t InstrumentIndexOnThisBut[NUM_OF_INSTRUMENTS_PER_NUMBER_BUT];

};

struct SetUpAtStart{
	//0 only variant  A is used
	//variant A and B are used, so we have 32 buttons
	uint8_t varA_B_Status;
	//0 -normal speed determined by tempo
	//1 - 2x speed determined by tempo
	//2 - 1.75 speed determined by tempo
	//3 - 1.5 speed determined by tempo
	uint8_t Prescale_Status;
	//Tempo value
	uint16_t Tempo;

};



#endif /* INC_STRUCTURES_H_ */
