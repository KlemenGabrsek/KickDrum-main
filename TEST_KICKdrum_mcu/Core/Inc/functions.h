/*
 * functions.h
 *
 *  Created on: Mar 12, 2024
 *      Author: Klemen
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <stdio.h>
#include "macros.h"
#include "structures.h"
#include "SwitchesInit.h"
#include "stm32f4xx_hal.h"
#include <stddef.h>
#include "Convert_slider_val_to_LCD.h"

extern  uint8_t BUT21CallBack;
extern uint16_t PreviousTempoVal;
extern uint8_t CurrentPickedInstrument;
uint8_t InitBU211();

uint8_t PrepDataForSensorFunctionReg(uint8_t* Data, struct Switch *ArrayOfSwitches , uint8_t LeftOrRightFlag);
/*
 * Funkcija SensorFunction mora podatke zapisane v strukturi za posamezen switch prenesti v obliko, ki jo bo enostavno zapisati v registre.
 *
 * input: funkcija Switch pina , output: 5x 8 bitnih številk za vpisovanje v register
 */

uint8_t PrepDataForSensitivityReg(uint8_t* Data, struct Switch *ArrayOfSwitches);
/*
 * Funkcija SensorFunction mora podatke zapisane v strukturi za posamezen switch prenesti v obliko, ki jo bo enostavno zapisati v registre.
 *
 * input: občutljivost  Switch pina , output: 5x 8 bitnih številk za vpisovanje v register
 */

uint8_t  PrepDataForONOFFTresholdReg(uint8_t* Data, struct Switch *ArrayOfSwitches,uint8_t LeftOrRightFlag);
/*
 * Funkcija SensorFunction mora podatke zapisane v strukturi za posamezen switch prenesti v obliko, ki jo bo enostavno zapisati v registre.
 *
 * input: ON treshold, OFF treshold  Switch pina , output: 70x 8 bitnih številk za vpisovanje v register
 */


uint8_t PrepDataForMultiplePatternSwitAssignmentReg(uint8_t* Data, struct Switch *ArrayOfSwitches);

/*
 * Funkcija SensorFunction mora podatke zapisane v strukturi za posamezen switch prenesti v obliko, ki jo bo enostavno zapisati v registre.
 *
 * input: ON treshold, OFF treshold  Switch pina , output: 70x 8 bitnih številk za vpisovanje v register
 */

uint8_t InitSwitchesTipke(struct Switch *ArrayOfSwitches);
/*
 * funkcija inicializira vsako struktupo posabaj s pravilnimi parametri
 */



uint8_t WriteDataI2C(uint8_t NumOfRegForIC,\
									// determinates number of registers in **DATA
									uint8_t** Data,\
									uint16_t* SizeOfData,\
									uint16_t* AddrData,\
									I2C_HandleTypeDef *I2C_Handler,\
									uint16_t DevAddr,\
									uint16_t SizeOfDataBlockInIC);
/*
 * funkcija zapiše podatke iz zbirke Arrayev v Registre na kapacitivnem senzorju BUT21
 */

uint8_t ReadDataI2C(uint8_t NumOfRegFromIC,uint8_t** Data,uint16_t* SizeOfData,uint16_t* AddrData,I2C_HandleTypeDef *I2C_Handler,uint16_t DevAddr, uint16_t SizeOfDataBlockInIC);
/*
 * funkcija zapiše podatke iz zbirke Arrayev v Registre na kapacitivnem senzorju BUT21
 */

uint8_t ParseDataFromInterruptFactor (struct Slider *Sliders,struct ReceiveData_BUT21 *DataFrom_BUT21,struct Switch *Tipke,struct SendData_BUT21 *DataFor_BUT21,uint8_t PanelLOrR);

uint8_t WriteDataI2C_Wrapper(struct SendData_BUT21 *DataFor_BUT21,uint8_t Start,uint8_t Stop);
uint8_t ReceiveDataI2C_Wrapper(struct ReceiveData_BUT21 *DataFrom_BUT21,uint8_t Start,uint8_t Stop);
uint8_t CopyDataToTipke(struct Slider *Sliders,struct Switch *Tipke,struct ReceiveData_BUT21 *DataFrom_BUT21,uint8_t StartData,uint8_t StopData,uint8_t PanelLOrR);

uint8_t SliderSetUp(struct  Slider *Sliders);
uint8_t ChangeIndexVal(struct  Slider *Sliders,uint8_t WindowSizePositions[3][2][2],uint16_t Colors[2],uint8_t **AllFrames[3],uint8_t NumOfLines[10]);
uint8_t PrepareDataFor_IS32(struct SendData_BUT21 * DataFor_IS32,I2C_HandleTypeDef *phi2c1);
uint8_t TurnOnLedn(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,uint8_t* pLedIndexActionList,uint8_t IndexFromCheckTipkeFun,uint8_t PanelLOrR );
uint8_t TurnOffLedn(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,uint8_t* pLedIndexActionList, uint8_t IndexFromCheckTipkeFun,uint8_t PanelLOrR);
uint8_t CheckStructTipke(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,  TIM_HandleTypeDef **ArrayOfTimerPointers,uint8_t PanelLOrR);

uint8_t CopyDataFromSliderToInstrument(struct Instrument *Instruments,struct Switch *Tipke,struct  Slider *Sliders,uint8_t *InstrumentIndix);
uint8_t CopyDataFromSliderToGenericInfoStruct(struct Switch *Tipke,struct  Slider *Sliders,struct SetUpAtStart *pGenericInfo);

uint8_t MapButtonStepsToInstruments(struct Button *Buttons,struct Instrument *Instruments,struct Switch *Tipke,struct  Slider *Sliders,uint8_t *InstrumentIndix,uint8_t * NumberButtonIndex);
uint8_t MapButtonStepsToInstrumentsAndCheckVar(struct Button *Buttons_varA,struct Button *Buttons_varB,struct Instrument *Instruments,struct Switch *Tipke,struct  Slider *Sliders,uint8_t *InstrumentIndix,uint8_t * NumberButtonIndex);

uint8_t StartAccentTimer( TIM_HandleTypeDef *ArrayOfTimerPointers[3],uint16_t CCR_ms,uint16_t AAR_ms);
uint8_t StopAccentTimer( TIM_HandleTypeDef *ArrayOfTimerPointers[3]);
uint32_t ConvertBPM_ToTimerTicks(uint16_t BPM);
uint8_t TurnONNumberLED(struct Switch *Tipke,uint8_t * NumberButtonIndex,uint8_t LEDIndex_1_16);
uint8_t TurnOFFNumberLED(struct Switch *Tipke,uint8_t * NumberButtonIndex,uint8_t LEDIndex_1_16);
uint8_t TurnOnSequencer(struct Switch *Tipke,uint8_t * NumberButtonIndex,struct Button *Buttons_varA,struct Button *Buttons_varB,uint8_t ArrayOfTimerChannels[8][2],TIM_HandleTypeDef *ArrayOfTimerPointers2[8][2],uint16_t InstrumentEnablePin[9],GPIO_TypeDef* GPIO_INSTRUMENT_ENABLE[9],struct Instrument *Instruments);

uint8_t CheckStructTipkeSequencerMode(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,uint8_t PanelLOrR);
uint8_t TurnOFFAllNumberLED(struct Switch *Tipke,uint8_t * NumberButtonIndex);

uint8_t ConvertInstrumentDataToTimers(struct Instrument *Instruments);
uint8_t SetInstrumentValToDefault(struct Instrument *Instruments,uint8_t NumOfIterations);
uint8_t SetAndStartTimers(struct Instrument *Instruments,uint8_t ArrayOfTimerChannels[8][2],TIM_HandleTypeDef *ArrayOfTimerPointers2[8][2]);



extern uint8_t LedControlRegAll_[2][3];
extern uint8_t PwmControlReg1_18_[2][4][5];
extern uint8_t  CurrentBlinkySwitchIndex[5];
extern uint8_t gVarBlinky;
extern uint8_t o;
extern uint8_t CurrentNumberInSeqState;

//extern TIM_HandleTypeDef* phtim6;
//extern uint8_t PwmControlReg6_10_[5];
//extern uint8_t PwmControlReg11_15_[5];
//extern uint8_t PwmControlReg16_18_[3];

#endif /* INC_FUNCTIONS_H_ */
