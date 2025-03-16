/*
 * function.c
 *
 *  Created on: Mar 12, 2024
 *      Author: Klemen
 */

#include "functions.h"
/*
 * iz nekega razloga ta funkcija noče delat
uint8_t PrepareDataFor_IS32(struct SendData_BUT21 * DataFor_IS32,I2C_HandleTypeDef *phi2c1){

   * DEFINITION OF REGISTERS/STRUCTS FOR IS31, IS32 has only write registers, nothing can be read from IS31
   * DataFor_IS32[0] Shutdown register ;1 registers
   *  DataFor_IS32[1] Update register ;1 registers
   * *DataFor_IS32[2] Reset register ;1 registers
   * * DataFor_IS32[3] LED Control Register1, LED Control Register2, LED Control Register3 ;3 registers
   * * DataFor_IS32[4]PWM Register (LED 1- 5) ;5 registers
   * DataFor_IS32[5]PWM Register (LED 6- 10) ;5 registers
   * * DataFor_IS32[6]PWM Register (LED 11- 15) ;5 registers
   * * DataFor_IS32[7]PWM Register (LED 16- 18) ;3 registers

	uint8_t NumOfRegForSendData_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING] = NUM_OF_REG_REGISTER_COUNTS;
	uint16_t AddrOfRegForSendData_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING][5] =ADDR_OF_ALL_REG_FOR_IS32 ;
	//uint8_t AllRegForIS32[NUM_OF_IS32_STRUCT_FOR_SENDING][5] = ALL_REGISTERS_FOR_IS32;
	uint8_t DataForIS32_Reg_0[1]={0x01};	//1 register
	 uint8_t DataForIS32_Reg_1[1]={UPDATE_REGISTER};	//1 register
	uint8_t DataForIS32_Reg_2[1]={RESET_REGISTER};//1 register


	uint8_t LedControlRegAll[3] = LED_CONTROL_REGISTER_ALL;
	uint8_t PwmControlReg1_5[5]=PWM_CHANNELS_1_TO_5_VALUES;
	uint8_t PwmControlReg6_10[5]=PWM_CHANNELS_6_TO_10_VALUES;
	uint8_t PwmControlReg11_15[5]=PWM_CHANNELS_11_TO_15_VALUES;
	uint8_t PwmControlReg16_18[3]=PWM_CHANNELS_16_TO_18_VALUES;

	uint8_t *pLedControlRegAll[3] = {&(LedControlRegAll[0]),&(LedControlRegAll[1]),&(LedControlRegAll[2])};
	uint8_t *pPwmControlReg1_5[5] = {\
			&(PwmControlReg1_5[0]),\
			&(PwmControlReg1_5[1]),\
			&(PwmControlReg1_5[2]),\
			&(PwmControlReg1_5[3]),\
			&(PwmControlReg1_5[4]),\
	};
	uint8_t *pPwmControlReg6_10[5] = {\
				&(PwmControlReg6_10[0]),\
				&(PwmControlReg6_10[1]),\
				&(PwmControlReg6_10[2]),\
				&(PwmControlReg6_10[3]),\
				&(PwmControlReg6_10[4]),\
		};
	uint8_t *pPwmControlReg11_15[5] = {\
				&(PwmControlReg11_15[0]),\
				&(PwmControlReg11_15[1]),\
				&(PwmControlReg11_15[2]),\
				&(PwmControlReg11_15[3]),\
				&(PwmControlReg11_15[4]),\
		};
	uint8_t *pPwmControlReg16_18[3] = {\
				&(PwmControlReg16_18[0]),\
				&(PwmControlReg16_18[1]),\
				&(PwmControlReg16_18[2])\
		};

	// to je zbirka kazalcev na zgornje arraye, v zgornjih zbirkah imamo nekje 1, nekje 3 in nekje 5 registrov pod istim kazalcem
	uint8_t *DataForIS32_Type1[3] = {DataForIS32_Reg_0,\
			DataForIS32_Reg_1,\
			DataForIS32_Reg_2};

	uint8_t **DataForIS32_Type2[5]={pLedControlRegAll,pPwmControlReg1_5,pPwmControlReg6_10,pPwmControlReg11_15,pPwmControlReg16_18};
	// IndexCorrection
	uint8_t a=0;

	for(uint8_t i=0;i<NUM_OF_IS32_STRUCT_FOR_SENDING;i++ ){

		DataFor_IS32[i].Addr_I2C_BUT21 = I2C_ADDR_IS31FL3218;
		DataFor_IS32[i].I2CHandlerForBUT21 = phi2c1;
		DataFor_IS32[i].SizeOfDataBlockInIC = SIZE_OF_REG_IN_LED_DRIVER;
		DataFor_IS32[i].NumOfRegForSendData_BUT21 =NumOfRegForSendData_IS32[i];
		for (uint8_t j=0;j<NumOfRegForSendData_IS32[i];j++ ){
		DataFor_IS32[i].RegistersAddrForSendData_BUT21[j] =AddrOfRegForSendData_IS32[i][j];
		DataFor_IS32[i].RegistersSizeForSendData_BUT21[j] = 1;
		if(i<3){
	DataFor_IS32[i].RegisterNameForSendData_BUT21[j]=DataForIS32_Type1[i];
		}else if (i>=3) {
			a=i-3;
			DataFor_IS32[i].RegisterNameForSendData_BUT21[j]=*(DataForIS32_Type2[a]+j);
		}
		}
	}


	return 0;
}

*/

uint8_t InitBU211(){

return 0;
}

uint8_t PrepDataForSensorFunctionReg(uint8_t *Data, struct Switch *ArrayOfSwitches, uint8_t LeftOrRightFlag){

uint8_t SensorFunctionReg [SIZE_SENSOR_FUNCTION]={0x00,0x00,0x00,0x00,0x00};
uint8_t BitShift=0;
uint8_t OstanekCeloDel = 0;
uint8_t OstanekNormDel = 0;

uint8_t StartStopForLeftRightPanel[3] = {0,20,40};

//if LeftOrRightFlag ==0 -> left panel
//if LeftOrRightFlag ==1 -> right panel

uint8_t ForLoopStartVal=0;
uint8_t ForLoopStopVal=0;

if (LeftOrRightFlag ==0){ //left panel
	ForLoopStartVal = StartStopForLeftRightPanel[0];
	ForLoopStopVal = StartStopForLeftRightPanel[1];
} else if( LeftOrRightFlag ==1 ){// right panel
	ForLoopStartVal = StartStopForLeftRightPanel[1];
	ForLoopStopVal = StartStopForLeftRightPanel[2];
}

for (uint8_t i=ForLoopStartVal;i<ForLoopStopVal;i++){
	OstanekCeloDel = (ArrayOfSwitches[i].SwitchNumOnIC)%4;
	OstanekNormDel = (ArrayOfSwitches[i].SwitchNumOnIC)/4;
	switch(OstanekCeloDel) {
					case 0:
												BitShift = 0;
												break;
					case 1:
												BitShift = 2;
												break;
					case 2:
												BitShift = 4;
												break;
					case 3:
												BitShift = 6;
												break;
					default:
												printf("Error");
												return 1;
	}
	Data[OstanekNormDel]=(Data[OstanekNormDel] )| ((ArrayOfSwitches[i].SensorFunction)<<BitShift);
	SensorFunctionReg[OstanekNormDel]=(SensorFunctionReg[OstanekNormDel] )| ((ArrayOfSwitches[i].SensorFunction)<<BitShift);
}
//Data = SensorFunctionReg;
return 0;
}

uint8_t PrepDataForSensitivityReg(uint8_t *Data, struct Switch *ArrayOfSwitches){

//uint8_t SensorSensitivityReg [SIZE_SENSITIVITY]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t BitShift=0;
uint8_t OstanekCeloDel =0;
uint8_t OstanekNormDel = 0;

for (uint8_t i=0;i<20;i++){

	OstanekCeloDel = (ArrayOfSwitches[i].SwitchNumOnIC)%2;//določa kolikšen bit shift je potreben
	OstanekNormDel = (ArrayOfSwitches[i].SwitchNumOnIC)/2;//določa na katero mesto v zbirki gre, glede številko switcha
	switch(OstanekCeloDel) {
					case 0:
												BitShift = 0;
												break;
					case 1:
												BitShift = 4;
												break;
					default:
												printf("Error");
												return 1;
	}
	//Data[OstanekNormDel]=(Data[OstanekNormDel]) | ((ArrayOfSwitches[i].Sensitivity)<<BitShift);
	Data[OstanekNormDel]=(Data[OstanekNormDel]) | ((ArrayOfSwitches[i].Sensitivity)<<BitShift);
}

return 0;
}

uint8_t PrepDataForONOFFTresholdReg(uint8_t *Data, struct Switch *ArrayOfSwitches,uint8_t LeftOrRightFlag){

//uint8_t ONOFFTresholdReg [SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD];
uint8_t j=0;
uint8_t StartStopForLeftRightPanel[3] = {0,20,40};

//if LeftOrRightFlag ==0 -> left panel
//if LeftOrRightFlag ==1 -> right panel

uint8_t ForLoopStartVal=0;
uint8_t ForLoopStopVal=0;

if (LeftOrRightFlag ==0){ //left panel
	ForLoopStartVal = StartStopForLeftRightPanel[0];
	ForLoopStopVal = StartStopForLeftRightPanel[1];
} else if( LeftOrRightFlag ==1 ){
	ForLoopStartVal = StartStopForLeftRightPanel[1];
	ForLoopStopVal = StartStopForLeftRightPanel[2];
}
for (uint8_t i=ForLoopStartVal;i<ForLoopStopVal;i++){
	 Data[j]=ArrayOfSwitches[i].SwitchONTreshold;
	j++;
	 Data[j]=ArrayOfSwitches[i].SwitchOFFTreshold;
	j++;
	if (j>SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD){
		printf("Error in PrepDataForONOFFTresholdReg");
		return 1;
	}
}

return 0;
}

uint8_t InitSwitchesTipke(struct Switch *ArrayOfSwitches){
/*
 * Function description: Data that is written in MACROS is assigned to Instances of Switch structures
 */
//Macros need to be assignet to a variable, and then the variable is used in the function
uint8_t DataSensitivity[] =DATA_SENSITIVITY_BUT_L_R  ;
uint8_t DataSensorFun[] =  DATA_SENSOR_FUNCTION_L_R;
//unused variable
//uint8_t DataTipkaNumOnPcb[] = DATA_TIPKA_NUM_ONPCB;
//uint8_t DataLedStatus[] = DATA_LED_STATUS;

uint8_t DataTresholdONOFF[] = DATA_TRESHOLD_ONOFF_L_R;


uint8_t LED_Intensity[]= LED_INTENSITY;
uint8_t LED_Blinky[]= LED_BLINKY;

uint8_t LED_OnOff[]= LED_DEFAULT_VAL;

uint8_t LedIndexInIS32 []=LED_INDEX_IN_IS32;




/*
Zaradi načina, kako so podatki zapisani v DATA_TRESHOLD_MACROJU je potreben dodaten števec
*/
int j =0;
//s for loop-om se sprehodimo skozi vse strukture, in jim dodelimo podatke
for( int i = 0;i<NUM_OF_SWITCHES;i++){
	ArrayOfSwitches[i].SwitchNumOnIC=i;
	ArrayOfSwitches[i].LEDIntensity=LED_Intensity[i];
	ArrayOfSwitches[i].LEDOnOff= LED_OnOff[i];

	ArrayOfSwitches[i].SwitchOnDetection= LED_OnOff[i];
	ArrayOfSwitches[i].SwitchOffDetection= LED_OnOff[i];
	ArrayOfSwitches[i].LEDIndexInIS32= LedIndexInIS32[i];


	ArrayOfSwitches[i].LEDBlinky=LED_Blinky[i];

	//ArrayOfSwitches[i]. TipkaNumOnPCB=DataTipkaNumOnPcb[i];
	ArrayOfSwitches[i].SensorFunction =DataSensorFun[i];
	ArrayOfSwitches[i].Sensitivity = DataSensitivity[i];
	ArrayOfSwitches[i].SwitchONTreshold = DataTresholdONOFF [j];
	 j++;
	ArrayOfSwitches[i].SwitchOFFTreshold = DataTresholdONOFF [j];
    j++;

}
	return 0;
}


uint8_t WriteDataI2C(uint8_t NumOfRegForIC,\
									// determinates number of registers in **DATA
									uint8_t** Data,\
									uint16_t* SizeOfData,\
									uint16_t* AddrData,\
									I2C_HandleTypeDef *I2C_Handler,\
									uint16_t DevAddr,\
									uint16_t SizeOfDataBlockInIC){

	HAL_StatusTypeDef ret ;
	// go trrough all Data
	for (uint8_t i=0;i<NumOfRegForIC;i++){
		ret = HAL_I2C_Mem_Write(I2C_Handler,		 DevAddr,		AddrData[i],			SizeOfDataBlockInIC,		*(Data+i), 		SizeOfData[i], 		50);
		if (ret != HAL_OK){
			return 1;
		}
	}
	return 0;
}

uint8_t ReadDataI2C(uint8_t NumOfRegFromIC,\
									// determinates number of registers in **DATA, to so registri ki se v ICju držijo skupaj
									uint8_t** Data,\
									uint16_t* SizeOfData,\
									uint16_t* AddrData,\
									I2C_HandleTypeDef *I2C_Handler,\
									uint16_t DevAddr,\
									uint16_t SizeOfDataBlockInIC){

	HAL_StatusTypeDef ret ;
	// go trrough all Data
	for (uint8_t i=0;i<NumOfRegFromIC;i++){
		ret = HAL_I2C_Mem_Read(I2C_Handler,		 DevAddr,		AddrData[i],			SizeOfDataBlockInIC,		Data[i], 		SizeOfData[i], 		50);
		if (ret != HAL_OK){
			return 1;
		}
	}
	return 0;
}


uint8_t ParseDataFromInterruptFactor (struct Slider *Sliders,struct ReceiveData_BUT21 *DataFrom_BUT21,struct Switch *Tipke, struct SendData_BUT21 *DataFor_BUT21,uint8_t PanelLOrR){

	uint8_t NumOfBitsInOneReg = 8;
	//uint8_t SwitchCaseVar=0x0 ;


	//uint8_t ArrOfFlagsInRegsOfINTFAC[SIZE_INTERRUPT_FACTOR]=INTERRUPT_FACTOR_FLAGS;
	uint8_t FlagForDetecting = 0x00;
	uint8_t *PIntFact = DataFrom_BUT21[0].RegisterNameForReceivedData_BUT21[0];

//go trough all 3 registers of interrupt factor
	for(uint8_t i =0; i< SIZE_INTERRUPT_FACTOR;i++){
		FlagForDetecting = 0x00;
		// rom 0 to 8, 1 byte long registers
		for (uint8_t j =0; j<NumOfBitsInOneReg; j++){
			FlagForDetecting  = PIntFact[i] & (1 << j);
			// the following if  detects if there is a bit set in interupt register
			if ( FlagForDetecting){

				if (i==0){ //register 1in interrupt factor
					//SwitchCaseVar=j+1;
					switch (FlagForDetecting){// +1 because of offset to macros
						case INITIALIZATION_COMPLETION_INTERRUPT:
							// clear interrupt factor
							WriteDataI2C_Wrapper(DataFor_BUT21, 1, 2);

							break;
						case SOFTWARE_CALIBRATION_COMPLETION_INTERRUPT:
							// clear interrupt factor
								WriteDataI2C_Wrapper(DataFor_BUT21, 1, 2);

							break;
						case CALIBRATION_FAILURE_INTERRUPT:
							WriteDataI2C_Wrapper(DataFor_BUT21, 1, 2);

							break;
						case UNEXPECTED_LONG_PRESS_DETECTION_INTERRUPT:
							CopyDataToTipke(Sliders,Tipke, DataFrom_BUT21,7,8,PanelLOrR);
							break;
						case NOISE_DETECTION_INTERRUPT:

							break;
						}

				}else if(i==1){ //register 2in interrupt factor
					//SwitchCaseVar=j+1;

					switch (FlagForDetecting) {  // +1 because of offset to macros
					case SWITCH_ON_DETECTION_INTERRUPT:
							//read data from BUT
							ReceiveDataI2C_Wrapper(DataFrom_BUT21, 1,2);
							// copy data to Tipke array
							CopyDataToTipke(Sliders,Tipke, DataFrom_BUT21,1,2,PanelLOrR);
							//CLEAR_SWITCH_ON_DETECTION
							WriteDataI2C_Wrapper(DataFor_BUT21, 2, 3);
					        break;
					    case SWITCH_OFF_DETECTION_INTERRUPT:
					    	//read data from BUT
					    	ReceiveDataI2C_Wrapper(DataFrom_BUT21, 2,3);
					    	// copy data to Tipke array
					    	CopyDataToTipke(Sliders,Tipke, DataFrom_BUT21,2,3,PanelLOrR);
					    	//CLEAR_SWITCH_OFF_DETECTION
							WriteDataI2C_Wrapper(DataFor_BUT21, 3, 4);
					        break;
					    case SWITCH_LONG_PRESS_DETECTION_INTERRUPT:

					        // Handle long press interrupt
					        break;
					    case SWITCH_REPEATED_LONG_PRESS_DETECTION_INTERRUPT:
					        // Handle repeated long press interrupt
					        break;
					    case MULTIPLE_PATTERN_SWITCHES_ON_DETECTION_INTERRUPT:
					        // Handle multiple pattern switches ON detection

					    	ReceiveDataI2C_Wrapper(DataFrom_BUT21, 5,6);
					    	// copy data to Tipke array, this array combines all data regarding switches from bots sensors
					    	CopyDataToTipke(Sliders,Tipke, DataFrom_BUT21,5,6,PanelLOrR);
					    	//CLEAR_MULTIPLE_PATTERN_SWITCH_ON_DETECTION
							WriteDataI2C_Wrapper(DataFor_BUT21, 6, 7);
					        break;
					    case MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION_INTERRUPT:
					        // Handle multiple pattern switches OFF detection

					    	ReceiveDataI2C_Wrapper(DataFrom_BUT21, 6,7);
					    	// copy data to Tipke array, this array combines all data regarding switches from bots sensors
							CopyDataToTipke(Sliders,Tipke, DataFrom_BUT21,6,7,PanelLOrR);
					    	//CLEAR_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION
							WriteDataI2C_Wrapper(DataFor_BUT21, 7, 8);
							break;
					    default:
					        // Handle unexpected cases
					        break;
					}


				}else if (i == 2){//register 3 in interrupt factor
					//SwitchCaseVar=j+1;
					switch (FlagForDetecting){// +1 because of offset to macros
										case AVDD_ON_DETECTION_INTERRUPT:
											// clear interrupt factor
												WriteDataI2C_Wrapper(DataFor_BUT21, 1, 2);

											break;
										case AVDD_OFF_DETECTION_INTERRUPT:

											break;

					}

			}
		}
	}
	}
	return 0;
}

uint8_t WriteDataI2C_Wrapper(struct SendData_BUT21 *DataFor_BUT21,uint8_t Start,uint8_t Stop){
// Za enostavnejše pošiljanje podatkov v gnezdenih funkcijah
uint8_t WriteDataI2C_ret =0;


for (uint8_t i = Start; i<Stop; i++){
	WriteDataI2C_ret = WriteDataI2C(DataFor_BUT21[i].NumOfRegForSendData_BUT21,     DataFor_BUT21[i].RegisterNameForSendData_BUT21,     DataFor_BUT21[i].RegistersSizeForSendData_BUT21,    DataFor_BUT21[i].RegistersAddrForSendData_BUT21,     DataFor_BUT21[i].I2CHandlerForBUT21,    DataFor_BUT21[i].Addr_I2C_BUT21,      DataFor_BUT21[i].SizeOfDataBlockInIC);

	if( WriteDataI2C_ret){
		while(1);

	}
}
return 0;
}


uint8_t ReceiveDataI2C_Wrapper(struct ReceiveData_BUT21 *DataFrom_BUT21,uint8_t Start,uint8_t Stop){
// Za enostavnejše pošiljanje podatkov v gnezdenih funkcijah
uint8_t DataI2C_ret =0;


for (uint8_t i = Start; i<Stop; i++){
	DataI2C_ret =ReadDataI2C(DataFrom_BUT21[i].NumOfRegForReceivedData_BUT21,     DataFrom_BUT21[i].RegisterNameForReceivedData_BUT21,      DataFrom_BUT21[i].RegistersSizeForReceivedData_BUT21,     DataFrom_BUT21[i].RegistersAddrForReceivedData_BUT21,     DataFrom_BUT21[i].I2CHandlerForBUT21,    DataFrom_BUT21[i].Addr_I2C_BUT21,       DataFrom_BUT21[i].SizeOfDataBlockInIC);

	if( DataI2C_ret){
		while(1);
	}
}
return 0;
}


uint8_t CopyDataToTipke(struct Slider *Sliders,struct Switch *Tipke,struct ReceiveData_BUT21 *DataFrom_BUT21,uint8_t StartData,uint8_t StopData,uint8_t PanelLOrR){
//This function will only read data from :
/*	Switch ON Detection
 * Switch OFF Detection
 * Switch Long Press Detection
 * Switch Repeated Long Press Detection
 * Multiple Pattern Switches ON Detection
 * Multiple Pattern Switches OFF Detection
 * Unexpected Long Press Detection
 * Switch ON / OFF State
 * and write this data to struct Tipke
 *
 * All registers have length of 6byts except Multiple Pattern Switches OFF Detection,Multiple Pattern Switches ON Detection these two have 2 byte
 */
	//2 bytes are stored in:
	uint8_t DataFromReg;
	//Register size in bytes, most will have 3, some 1
	uint8_t RegisterSize;
	//result of biwise operation for finding 1 in registers
	uint8_t BitWiseRes;
	//this is the number with bit position
	uint8_t BitWiseCompare;
	//this numbere determinates which capacitive sensor was changed, it is calculated from j and k
	uint8_t StTipke;
	// dodaten offset, glede na to ali je left ali right panel,
	// left PanelKOffset = 0
	// left PanelKOffset = 19;
	uint8_t PanelKOffset =0;

	if (PanelLOrR == 2){
		PanelKOffset =20;
	}else if(PanelLOrR == 1){
		PanelKOffset =0;
	}else{
		while(1);
	}

	//this variable is for holding the value of CrossSection from stucture Slider
	uint8_t CrossSectionNum =0;
	//this variable is for holding the value of Switch number from stucture Slider
		uint8_t SwitchNum =0;

//Goes trough all registers in DataFromBUT21 that we wish to read, StartData and StopData mark what registers we wish to read
for(uint8_t i = StartData; i<StopData; i++){
	//From DataFrom_BUT21 we receive info on register length
	RegisterSize = DataFrom_BUT21[i].RegistersSizeForReceivedData_BUT21[0];
	//we have to read all bytes in the register
	//go trough each arrdes inside the register
	for (uint8_t j =RegisterSize;j>0;j--){
		//in the DataFrom_BUT21 structure a pointer to pointer is stored of the register we wish to read
		DataFromReg = *(*(DataFrom_BUT21[i].RegisterNameForReceivedData_BUT21)+j-1);
		// walk trough all bits in one register address
		for (uint8_t k =0; k < 8;k++){
			//check if any bit is set
			 BitWiseRes = DataFromReg & (1<<k);
			 //form a 8 bit num to compare
			 BitWiseCompare = (1<<k);
			 //compare
			 if (BitWiseCompare == BitWiseRes){
				 //determinate what capacitive switch does it effect, calculate from j and k what "Tipka" needs to be updated
				 if (j==1){
					 /*
					  * tukaj je potrebno spremeniti vrednost k-ja , če gre za right panel, prištejemo 19 trenutnih
					  * vrednostim, če je rightpanel
					  */

					 StTipke = k+ PanelKOffset;
				 }else if (j==2){
					 StTipke = k+8+PanelKOffset;
				  }else if (j==3){
					 StTipke = k+16+PanelKOffset;
				 } else {
					 return 1;
				 }
				 // write new status to Tipke
				 switch (StartData) {
				        case 1:
				        	//write data to master array Tipke
				            Tipke[StTipke].SwitchOnDetection =1;
				            //write data to Struct Slider
				            // loop trough all Sliders in struct Slider
							for(uint8_t i =0;i< NUMBER_OF_SLIDERS;i++){
								// loop trough all data in Slider CrossSection
								for(uint8_t j =0;j< NUMBER_OF_SLIDERS;j++){
									SwitchNum = Sliders[i].SwitchNumber[j];
									if(StTipke == SwitchNum){
										Sliders[i].Switch[j] = 1;
										Sliders[i].SwitchTimeON[j] = HAL_GetTick();
									}
								}
							}
				            break;
				        case 2:
				        	//write data to master array Tipke
				            Tipke[StTipke].SwitchOffDetection =1;
				            //write data to Struct Slider
				            for(uint8_t i =0;i< NUMBER_OF_SLIDERS;i++){
								// loop trough all data in Slider CrossSection
								for(uint8_t j =0;j< NUMBER_OF_SLIDERS;j++){
									SwitchNum = Sliders[i].SwitchNumber[j];
									if(StTipke == SwitchNum){
										Sliders[i].Switch[j] = 0;
										Sliders[i].SwitchTimeOFF[j] = HAL_GetTick();
									}
								}
							}
				            break;
				        case 3:
				            Tipke[StTipke].SwitchLongPressDetection = 1;
				            break;
				        case 4:
				            Tipke[StTipke].SwitchRepeatedLongPressDetection =1;
				            break;
				        case 5:
				        	// the following has no meaning as Multiple patter detectin can not be written to Tipke
				        	//Tipke[StTipke].MultiPatternSwitchOnDetection =1;

				        	// loop trough all Sliders in struct Slider
				        	for(uint8_t i =0;i< NUMBER_OF_SLIDERS;i++){
				        		// loop trough all data in Slider CrossSection
				        		for(uint8_t j =0;j< NUMBER_OF_SLIDERS;j++){
				        			//write CrossSection to local variable
									CrossSectionNum =Sliders[i].CrossSectionNumber[j];
									//compare StTipke, which representsthe MultiplePatternSwitch assigment (0->A, 1->B....7->H); this data is read from BUT;,
									//with what CrossSection is looked for in a particular Slider struct
									if (StTipke == CrossSectionNum ){
										//change status of particular CrossSection
										Sliders[i].CrossSection[j]=1;
										//capture time of this change in ms
										Sliders[i].CrossSectionTimeON[j]=HAL_GetTick();
									}
				        		}
				        	}
				            break;
				        case 6:
				        	// the following has no meaning as Multiple patter detectin can not be written to Tipke
				            //Tipke[StTipke].MultiPatternSwitchOffDetection = 1;

				        	for(uint8_t i =0;i< NUMBER_OF_SLIDERS;i++){
								// loop trough all data in Slider CrossSection
								for(uint8_t j =0;j< NUMBER_OF_SLIDERS;j++){
									//write CrossSection to local variable
									CrossSectionNum =Sliders[i].CrossSectionNumber[j];
									//compare StTipke, which representsthe MultiplePatternSwitch assigment (0->A, 1->B....7->H); this data is read from BUT;,
									//with what CrossSection is looked for in a particular Slider struct
									if (StTipke == CrossSectionNum ){
										//change status of particular CrossSection
										Sliders[i].CrossSection[j]=0;
										//capture time of this change in ms
										Sliders[i].CrossSectionTimeOFF[j]=HAL_GetTick();
									}
								}
							}
				            break;
				        case 7:
				            Tipke[StTipke].UnexplectedLongPressDetection = 1;
				            break;
				        default:
				            return 1;
				            break;
				 }
			 }
			 }
	}
}
return 0;
}
uint8_t CheckTipkeAndChangeStausLED(struct Switch *Tipke, uint8_t LEDStatus){
	/*This function reads ON OF status in Tipke and depending on the LEDStatus paremater these LEDs start to glow in a curtain way.
	 * Glowing options:
	 *   0 LED Off
	 * 1 LED ON
	 * 2 LED Slow blinking
	 * 3 LED fast blinking
	 * LED status parameter is written in Tipke, to change it, change the Macro
	 */
	//Was the switch turned on
	uint8_t TipkaOnStatus;
	//Was the switch turned off
	uint8_t TipkaOffStatus;
	// go trough all switches in Tipke
	for (uint8_t i =0; i<40;i++){
		// write status of switch on detection to local variable
		TipkaOnStatus = Tipke[i].SwitchOnDetection;
		// write status of switch off detection to local variable
		TipkaOffStatus = Tipke[i].SwitchOffDetection;
		// compare status, if  both are 1 enable the light, else dissable the LED
		if(TipkaOffStatus&TipkaOnStatus){
			Tipke[i].LEDOnOff=1;
		}else{
			Tipke[i].LEDOnOff=0;
		}
		/*
		 * potrebno bo dodati mehanizem za spremembo stanja Tipke[i].SwitchOffDetection, saj ko se izvede neka akcija se mora stanje resetirati
		 *da se akcija lahko izvede ob naslednjem pritisku gumba
		 */
	}
return 0;
}

uint8_t ChangeIndexVal(struct  Slider *Sliders,uint8_t WindowSizePositions[3][2][2],uint16_t Colors[2],uint8_t **AllFrames[3],uint8_t NumOfLines[10]){
	//because there are different layout we need  to change the index calculation between the first and second  slider
	//uint8_t SliderIndexCorrestion =1;

	// Local variable for SliderIndex
	uint8_t SliderIndex =0;
	//variable for counting how many switches have correct time diff to other switches in clockwise rotation
	uint8_t SwitchDifClockWiseIndex =0;
	//variable for counting how many switches have correct time diff to other switches in clockwise rotation
		uint8_t SwitchDifAntiClockWiseIndex =0;
	//variable for determinating in which directinon the finger is spinning
	// 1 - clockwise
	// 2 -  anti-clockwise
	uint8_t DirectionOfRotation=0;
	//pointers to switch on time arrays and switch off time arrays
	uint32_t *SwitchTimeON;
	uint32_t *SwitchTimeOFF;
	uint32_t SwitchTimeDiff[NUMBER_OF_SLIDERS];
	//value storing for subtraction of ON and OFF times to determinate rotation direction
	uint32_t SwitchTimeDiffClockWise[NUMBER_OF_SLIDERS];
	uint32_t SwitchTimeDiffCounterClockWise[NUMBER_OF_SLIDERS];
	//this variable tracks how many switches have turende on and off in the predetermined time slot
	uint8_t SwitchOnOfTiming=0;
	//Status of 1. condition
	uint8_t ConditionOneStatus=0;
	//variable for calculating edge case with second criteria
	uint8_t a=0;
	//variable to reset the Sliders[i].SwitchTimeON and Sliders[i].SwitchTimeOFF
	const uint32_t SwitchTimeONOFFReset[NUMBER_OF_SLIDERS]={0,0,0};

	for(uint8_t i =0; i<NUMBER_OF_SLIDERS;i++){
		//zapis iz trenutnega i-tega sliderja v lokalne spr
		SwitchTimeON=Sliders[i].SwitchTimeON;
		SwitchTimeOFF=Sliders[i].SwitchTimeOFF;
		SliderIndex = Sliders[i].Index;
		//each slider must start with a 0, it can not take status from other sliders
		SwitchOnOfTiming=0;
		SwitchDifClockWiseIndex=0;
		SwitchDifAntiClockWiseIndex=0;

		/*
		 * 1. condition for slier index increase:
		 * two of 3 switches must have turned on and off in a determinated time, the third is the border switch
		 * that is currently being couched
		 */
		// go trough all slider i switches
		for(uint8_t j=0;j<NUMBER_OF_SLIDERS;j++){
			//calculate time differnece between switch on and switch off for all switches in particular i Slider
			SwitchTimeDiff [j] =(*(SwitchTimeOFF+j))-(*(SwitchTimeON+j));
			// in almost all cases one difference goes into overflow and the result in smt in range of 4294966997
			if (SwitchTimeDiff [j] >120 && SwitchTimeDiff [j]<700 ){
				// max value of SwitchOnOfTiming can be 3 as it is incremented only in for loop
				SwitchOnOfTiming++;
			}
			if(SwitchOnOfTiming>= 2){
				ConditionOneStatus = 1;
			}else{
				ConditionOneStatus = 0;
			}
		}


		/*
		 * 2. condition for determinating slider rotation
		 * two out of three switches must fullfill the criteria of differences between ON and OF times of different switches
		 */
		if (ConditionOneStatus==1){
			for(uint8_t j=0;j<NUMBER_OF_SLIDERS;j++){
					a=j+1;
					//calculate time differnece between  on times for different whitches in one slider for clock wise rotation
					//uint32_t SwitchTimeDiffClockWise = {t1-t0,t2-t1-t0-t2}
					if(a==3){
						a=0;
					}
					SwitchTimeDiffClockWise [j] =(*(SwitchTimeON+a))-(*(SwitchTimeON+j));

				//calculate time differnece between  on times for different whitches in one slider for anti clock wise rotation
				//uint32_t SwitchTimeDiffClockWise = {t0-t1,t1-t2,t2-t0}
				SwitchTimeDiffCounterClockWise [j] =(*(SwitchTimeON+j))-(*(SwitchTimeON+a));

				if (SwitchTimeDiffCounterClockWise [j] >150 && SwitchTimeDiffCounterClockWise [j]<500 ){
					// max value of SwitchOnOfTiming can be 3 as it is incremented only in for loop
				SwitchDifAntiClockWiseIndex++;
				}
				if (SwitchTimeDiffClockWise [j] >150 && SwitchTimeDiffClockWise [j]<500 ){
					// max value of SwitchOnOfTiming can be 3 as it is incremented only in for loop
				SwitchDifClockWiseIndex++;
				}
			}
			if(SwitchDifClockWiseIndex>= 2){
				DirectionOfRotation = 1;
			}else if (SwitchDifAntiClockWiseIndex>= 2) {
				DirectionOfRotation = 2;
			}else{
				DirectionOfRotation = 0;
			}
		}
/*
 * combinig all conditions and checking the existing value
 */
			if( ConditionOneStatus==1 &&  DirectionOfRotation !=0 ){

				if(DirectionOfRotation ==1 && SliderIndex <100 ){
					Sliders[i].Index =SliderIndex+1;
					DisplaySliderDataOnLCD (Sliders[i].Index,WindowSizePositions,Colors,AllFrames,NumOfLines );
					for(int j = 0;j<NUMBER_OF_SLIDERS;j++){
						Sliders[i].SwitchTimeON[j] =SwitchTimeONOFFReset[j];
						Sliders[i].SwitchTimeOFF[j]=SwitchTimeONOFFReset[j];
					}

				}else if (DirectionOfRotation ==2 && SliderIndex > 0) {
					Sliders[i].Index =SliderIndex-1;
					DisplaySliderDataOnLCD (Sliders[i].Index,WindowSizePositions,Colors,AllFrames,NumOfLines );
					for(int j = 0;j<NUMBER_OF_SLIDERS;j++){
						Sliders[i].SwitchTimeON[j] =SwitchTimeONOFFReset[j];
						Sliders[i].SwitchTimeOFF[j]=SwitchTimeONOFFReset[j];
					}
				}
			}

	}

	return 0;
}



uint8_t SliderSetUp(struct  Slider *Sliders){
	//create a variable with number of sliders from macro
	uint8_t NumOfSliders = NUMBER_OF_SLIDERS;
	//create an instance of a pointer to slider names, SLIDE_NAMES is an array with 3 strings,
	//an array of charater pointers is created (3 slots), and each string from SLIDER NAME gets a pointer
	char *SliderNames[NUMBER_OF_SLIDERS]=SLIDER_NAMES;
	/*
	 * SLIDER_SWITCHES is an  3x3 array of strings, here we create an array of 3x3 character pointers
	 * each string from SLIDER_SWITCHES gets pointer
	 * the same with SLIDER_CROSSSECTIONS
	 */
	char *SliderSwitches[NUMBER_OF_SLIDERS][NUMBER_OF_SLIDERS]=SLIDER_SWITCHES;
	char *SliderCrosssections[NUMBER_OF_SLIDERS][NUMBER_OF_SLIDERS]=SLIDER_CROSSSECTIONS;
	uint8_t SliderCrosssectionNumber[NUMBER_OF_SLIDERS][NUMBER_OF_SLIDERS]=SLIDER_CROSSSECTION_NUMBERS;
	uint8_t SwitchNumber [NUMBER_OF_SLIDERS][NUMBER_OF_SLIDERS] = SWITCH_NUMBER;

//here we assign values from MACROS to SLIDERS structure
//this for goes trough all instances of Sliders
for(uint8_t i=0;i<NumOfSliders;i++){
	// each instance of slider gets its name
	Sliders[i].NameOfSliderOnPCBA = SliderNames[i];
	//this for goes trough number of switches and number of crosssection, these two numbers are always the same
	// this is why the same variable is used 2 times
	// as each slider has multiple switches and crosssections, each character pointer must be passed to the right slider
	for(uint8_t j=0;j<NumOfSliders;j++){
		Sliders[i].SwitchName[j]= SliderSwitches[i][j];
		Sliders[i].CrossSectionName[j]= SliderCrosssections[i][j];

		//set default values
		Sliders[i].Switch[j]=0;
		Sliders[i].CrossSection[j]=0;
		Sliders[i].SwitchTimeON[j]=0;
		Sliders[i].CrossSectionTimeON[j]=0;

		Sliders[i].SwitchTimeOFF[j]=0;
		Sliders[i].CrossSectionTimeOFF[j]=0;

		Sliders[i].SwitchNumber[j]=SwitchNumber [i][j];
		Sliders[i].CrossSectionNumber[j]= SliderCrosssectionNumber[i][j];
	}
	// default values of Index is 0
	Sliders[i].Index = 0;
	//add the function address to the function pointer
	//Sliders[i].ChangeIndexVal =ChangeIndexVal;
	//pointer na funkcijo ni potreben, saj bo v mainu glavna funkcija, ki bo šla skozi vse 3 sliderje

}

return 0;
}

uint8_t TurnOnLedn(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,uint8_t* pLedIndexActionList,uint8_t IndexFromCheckTipkeFun,uint8_t PanelLOrR){

/*
   * DEFINITION OF REGISTERS/STRUCTS FOR IS31, IS32 has only write registers, nothing can be read from IS31
   * DataFor_IS32[0] Shutdown register ;1 registers
   *  DataFor_IS32[1] Update register ;1 registers
   * *DataFor_IS32[2] Reset register ;1 registers
   * * DataFor_IS32[3] LED Control Register1, LED Control Register2, LED Control Register3 ;3 registers
   * * DataFor_IS32[4]PWM Register (LED 1- 5) ;5 registers
   * DataFor_IS32[5]PWM Register (LED 6- 10) ;5 registers
   * * DataFor_IS32[6]PWM Register (LED 11- 15) ;5 registers
   * * DataFor_IS32[7]PWM Register (LED 16- 18) ;3 registers
   */

	uint8_t CurrentLEDBlinky=0;
	uint8_t CurrentLEDIndex=0;
	uint8_t CurrentLEDOnOff=0;
	uint8_t CurrentLEDIntensity=0;
	uint8_t CurrentLEDSwitchOnDetection=0;
	uint8_t CurrentLEDSwitchOffDetection=0;
	//potrebujem spr za vmesno hranjenje, za kasnejše pisanje v IS32 strukturo
	uint8_t LEDControlReg[3] ={0,0,0};

	uint8_t LEDPWMControlReg[4][5] = {
		{0, 0, 0, 0, 0}, // First row
		{0, 0, 0, 0, 0}, // Second row
		{0, 0, 0, 0, 0}, // Third row
		{0, 0, 0, 0, 0}  // Fourth row
	};

	uint8_t NumOfRegForSendData_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING] = NUM_OF_REG_REGISTER_COUNTS;
	//uint8_t PwmControlReg1_18[4][5]=PWM_CHANNELS_1_TO_18_VALUES;
	uint8_t IndexForLedControlReg =0;

	//uint8_t LedControlRegAll_[3];


	//uint8_t PwmControlReg1_18_[4][5];

	uint8_t *pPwmControlReg[4][5];

	//writing all addresses from each element in LedControlRegAll_ (each element is one register) to an array of pointers
	uint8_t *pLedControlRegAll[3] = {&(LedControlRegAll_[PanelLOrR][0]),&(LedControlRegAll_[PanelLOrR][1]),&(LedControlRegAll_[PanelLOrR][2])};

	//writing all addresses from each element in PwmControlReg1_18_ (each element is one register) to an array of pointers
	//zapis pointerjev v array, za LEDPWM
	for(uint8_t j = 0;j<4; j++){
		for(uint8_t i = 0;i<5; i++){
			pPwmControlReg[j][i] = &( PwmControlReg1_18_[PanelLOrR][j][i]);
		}
	}

	uint8_t **DataForIS32_Type2[5]={pLedControlRegAll,pPwmControlReg[0],pPwmControlReg[1],pPwmControlReg[2],pPwmControlReg[3]};

	// IndexCorrection for writing to IS32 structure
		uint8_t a=0;




	for (uint8_t i = 0;i < IndexFromCheckTipkeFun;i++){

		// all relavant variables are written from Tipke structure to local variable
		//potrebno je paziti na indeks, tu se za index uporabi število iz prejetega arraya v funkcijo
		CurrentLEDBlinky = Tipke[pLedIndexActionList[i]].LEDBlinky;
		// CurrentLEDOnOff = Tipke[pLedIndexActionList[i]].LEDOnOff;
		CurrentLEDIntensity = Tipke[pLedIndexActionList[i]].LEDIntensity;
		//CurrentLEDSwitchOnDetection = Tipke[pLedIndexActionList[i]].SwitchOnDetection;
		//CurrentLEDSwitchOffDetection = Tipke[pLedIndexActionList[i]].SwitchOffDetection;
		CurrentLEDIndex = Tipke[pLedIndexActionList[i]].LEDIndexInIS32;
/*
		//this section of code will check and TURN LED ON
		//if LED i is off and switch i has been pressed, then do
		//if ( CurrentLEDOnOff == 0 && CurrentLEDSwitchOnDetection ==1 ){//ko bo funkcija \
			za česanje Tipk narejena, ne bo potrebe po tem zgornjem pogoju, saj bo že funkcija\
			za česanje določila, kdaj naj se kej ugasne in kdaj naj se kaj prizge

*/

			//SETTING CONTROL REG
			//ugotovimo v kateri register bo potrebno i-ti bit uvrstiti
			if(CurrentLEDIndex <= 5 && CurrentLEDIndex >= 0){

				LEDControlReg[0]=LEDControlReg[0] | (1<<CurrentLEDIndex);

			}else if (CurrentLEDIndex > 5 && CurrentLEDIndex <=11) {
				//index must always be in range of 0 to 5
				IndexForLedControlReg = CurrentLEDIndex-6;
				LEDControlReg[1]=  LEDControlReg[1] |(1<<IndexForLedControlReg);

			}else if (CurrentLEDIndex <= 17 && CurrentLEDIndex > 11) {
				//index must always be in range of 0 to 5
				IndexForLedControlReg = CurrentLEDIndex-12;
				LEDControlReg[2]=LEDControlReg[2] | (1<<IndexForLedControlReg);

			}else if (CurrentLEDIndex ==255){

			}else {

				return 1;
			}
			//SETTING PWM CONTROL REG in local variable
			//ugotovimo v kateri register bo potrebno i-ti bit uvrstiti
			if(CurrentLEDIndex <= 4 && CurrentLEDIndex >= 0){

				LEDPWMControlReg[0][CurrentLEDIndex]=CurrentLEDIntensity;

			}else if (CurrentLEDIndex > 4 && CurrentLEDIndex <=9) {
				//index must always be in range of 0 to 5
				IndexForLedControlReg = CurrentLEDIndex-5;
				LEDPWMControlReg[1][IndexForLedControlReg]=  CurrentLEDIntensity;

			}else if (CurrentLEDIndex > 9 && CurrentLEDIndex <= 14) {
				//index must always be in range of 0 to 5
				IndexForLedControlReg = CurrentLEDIndex-10;
				LEDPWMControlReg[2][IndexForLedControlReg]= CurrentLEDIntensity;

			}else if (CurrentLEDIndex > 14 && CurrentLEDIndex <= 17) {
				IndexForLedControlReg = CurrentLEDIndex-15;
				//LEDPWMControlReg[3][IndexForLedControlReg]=LEDPWMControlReg[3][IndexForLedControlReg] |  (PwmControlReg1_18[3][CurrentLEDIndex]);
				LEDPWMControlReg[3][IndexForLedControlReg]=CurrentLEDIntensity;

			}else if (CurrentLEDIndex ==255){

			}else {
				return 1;
			}

			// set LEDOnOff variable as LED ON




	// writing  CONTROL REG from local variable to extern variable
		for(uint8_t j = 0;j<3; j++){
		// potrebno je sestaviti LEDControl RegAll, da ga lahko zapišemo v IS32 strukturo
			// vzamemo preteklo "staro" vrednost externe spremenljivke LedControlRegAll in jo ponovno zapišemo v LedControlRegAll
			// s tem zagotovimo, da LEDice, ki so že prižgane ostane tudi sedaj prižgane
			LedControlRegAll_[PanelLOrR][j] = (LedControlRegAll_[PanelLOrR][j] | LEDControlReg [j]);
		}
		// writing  PWM CONTROL REG from local variable to extern variable
		for (uint8_t i = 0;i<4; i++){
			for(uint8_t j = 0;j<5; j++){
				// potrebno je sestaviti LEDControl RegAll, da ga lahko zapišemo v IS32 strukturo
					// vzamemo preteklo "staro" vrednost externe spremenljivke LedControlRegAll in jo ponovno zapišemo v LedControlRegAll
					// s tem zagotovimo, da LEDice, ki so že prižgane ostane tudi sedaj prižgane
			 	 	 PwmControlReg1_18_[PanelLOrR][i][j]= PwmControlReg1_18_[PanelLOrR][i][j] |  LEDPWMControlReg[i][j];

				}
		}

	// writing PWM control data and controll data to IS32 structure
	for(uint8_t k=3;k<NUM_OF_IS32_STRUCT_FOR_SENDING;k++ ){
		// podatke za ta del strukturepošljem že v inicializaciji

		for (uint8_t j=0;j<NumOfRegForSendData_IS32[k];j++ ){
		//DataFor_IS32[i].RegistersAddrForSendData_BUT21[j] =AddrOfRegForSendData_IS32[i][j];
		//DataFor_IS32[i].RegistersSizeForSendData_BUT21[j] = 1;
			a=k-3;
			DataFor_IS32[k].RegisterNameForSendData_BUT21[j]=*(DataForIS32_Type2[a]+j);
		}
		}

	WriteDataI2C_Wrapper(DataFor_IS32, 3, 8);//write all PWMs and LED controll
	WriteDataI2C_Wrapper(DataFor_IS32, 1, 2);//update registers
	Tipke[pLedIndexActionList[i]].LEDOnOff = 1; // set flag in current tipke
		}
	//}
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TurnOffLedn(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,uint8_t* pLedIndexActionList,uint8_t IndexFromCheckTipkeFun,uint8_t PanelLOrR ){

/*
   * DEFINITION OF REGISTERS/STRUCTS FOR IS31, IS32 has only write registers, nothing can be read from IS31
   * DataFor_IS32[0] Shutdown register ;1 registers
   *  DataFor_IS32[1] Update register ;1 registers
   * *DataFor_IS32[2] Reset register ;1 registers
   * * DataFor_IS32[3] LED Control Register1, LED Control Register2, LED Control Register3 ;3 registers
   * * DataFor_IS32[4]PWM Register (LED 1- 5) ;5 registers
   * DataFor_IS32[5]PWM Register (LED 6- 10) ;5 registers
   * * DataFor_IS32[6]PWM Register (LED 11- 15) ;5 registers
   * * DataFor_IS32[7]PWM Register (LED 16- 18) ;3 registers
   */

	uint8_t CurrentLEDBlinky=0;
	uint8_t CurrentLEDIndex=0;
	uint8_t CurrentLEDOnOff=0;
	uint8_t CurrentLEDIntensity=0;
	uint8_t CurrentLEDSwitchOnDetection=0;
	uint8_t CurrentLEDSwitchOffDetection=0;
	//potrebujem spr za vmesno hranjenje, za kasnejše pisanje v IS32 strukturo
	uint8_t LEDControlReg[3] ={0,0,0};
/*
	uint8_t LEDPWMControlReg[4][5] = {
		{0, 0, 0, 0, 0}, // First row
		{0, 0, 0, 0, 0}, // Second row
		{0, 0, 0, 0, 0}, // Third row
		{0, 0, 0, 0, 0}  // Fourth row
	};
*/
	uint8_t NumOfRegForSendData_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING] = NUM_OF_REG_REGISTER_COUNTS;
	//uint8_t PwmControlReg1_18[4][5]=PWM_CHANNELS_1_TO_18_VALUES;
	uint8_t IndexForLedControlReg =0;

	//uint8_t LedControlRegAll_[3];
	//uint8_t LedControlRegAll_[3]={0,0,0};
/*
	uint8_t PwmControlReg1_18_[4][5]= {
			{0, 0, 0, 0, 0}, // First row
			{0, 0, 0, 0, 0}, // Second row
			{0, 0, 0, 0, 0}, // Third row
			{0, 0, 0, 0, 0}  // Fourth row
		};
*/
	//uint8_t PwmControlReg1_18_[4][5];



	//writing all addresses from each element in LedControlRegAll_ (each element is one register) to an array of pointers
	uint8_t *pLedControlRegAll[3] = {&(LedControlRegAll_[PanelLOrR][0]),&(LedControlRegAll_[PanelLOrR][1]),&(LedControlRegAll_[PanelLOrR][2])};



	uint8_t **DataForIS32_Type2[1]={pLedControlRegAll};

	// IndexCorrection for writing to IS32 structure
		uint8_t a=0;




	for (uint8_t i = 0;i <IndexFromCheckTipkeFun;i++){

		// all relavant variables are written from Tipke structure to local variable
		//potrebno je paziti na indeks, tu se za index uporabi število iz prejetega arraya v funkcijo
		CurrentLEDBlinky = Tipke[pLedIndexActionList[i]].LEDBlinky;
		 CurrentLEDOnOff = Tipke[pLedIndexActionList[i]].LEDOnOff;
		CurrentLEDIntensity = Tipke[pLedIndexActionList[i]].LEDIntensity;
		CurrentLEDSwitchOnDetection = Tipke[pLedIndexActionList[i]].SwitchOnDetection;
		CurrentLEDSwitchOffDetection = Tipke[pLedIndexActionList[i]].SwitchOffDetection;
		CurrentLEDIndex = Tipke[pLedIndexActionList[i]].LEDIndexInIS32;

		//this section of code will check and TURN LED ON
		//if LED i is off and switch i has been pressed, then do
		//if ( CurrentLEDOnOff == 1 && CurrentLEDSwitchOnDetection ==1 ){//ko bo funkcija \
			za česanje Tipk narejena, ne bo potrebe po tem zgornjem pogoju, saj bo že funkcija\
			za česanje določila, kdaj naj se kej ugasne in kdaj naj se kaj prizge



			//SETTING CONTROL REG
			//ugotovimo v kateri register bo potrebno i-ti bit uvrstiti
			if(CurrentLEDIndex <= 5 && CurrentLEDIndex >= 0){

				LEDControlReg[0]=LEDControlReg[0] | (1<<CurrentLEDIndex);

			}else if (CurrentLEDIndex > 5 && CurrentLEDIndex <=11) {
				//index must always be in range of 0 to 5
				IndexForLedControlReg = CurrentLEDIndex-6;
				LEDControlReg[1]=  LEDControlReg[1] |(1<<IndexForLedControlReg);

			}else if (CurrentLEDIndex <= 17 && CurrentLEDIndex > 11) {
				//index must always be in range of 0 to 5
				IndexForLedControlReg = CurrentLEDIndex-12;
				LEDControlReg[2]=LEDControlReg[2] | (1<<IndexForLedControlReg);

			}else if (CurrentLEDIndex ==255){
			}else {
				return 1;
			}


	// writing  CONTROL REG from local variable to extern variable
		for(uint8_t j = 0;j<3; j++){
		// potrebno je sestaviti LEDControl RegAll, da ga lahko zapišemo v IS32 strukturo
			// vzamemo preteklo "staro" vrednost externe spremenljivke LedControlRegAll in jo ponovno zapišemo v LedControlRegAll
			// s tem zagotovimo, da LEDice, ki so že prižgane ostane tudi sedaj prižgane
			LedControlRegAll_[PanelLOrR][j] = (LedControlRegAll_[PanelLOrR][j] &(~( LEDControlReg [j])));
		}

	// writing PWM control data and controll data to IS32 structure
	for(uint8_t k=3;k<4;k++ ){
		// podatke za ta del strukturepošljem že v inicializaciji

		for (uint8_t j=0;j<NumOfRegForSendData_IS32[k];j++ ){
		//DataFor_IS32[i].RegistersAddrForSendData_BUT21[j] =AddrOfRegForSendData_IS32[i][j];
		//DataFor_IS32[i].RegistersSizeForSendData_BUT21[j] = 1;
			a=k-3;
			DataFor_IS32[k].RegisterNameForSendData_BUT21[j]=*(DataForIS32_Type2[a]+j);
		}
		}

	WriteDataI2C_Wrapper(DataFor_IS32, 3, 4);//write all PWMs and LED controll
	WriteDataI2C_Wrapper(DataFor_IS32, 1, 2);//update registers
	Tipke[pLedIndexActionList[i]].LEDOnOff = 0; // set flag in current tipke
		}
	//}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t CheckStructTipke(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke, TIM_HandleTypeDef **ArrayOfTimerPointers,uint8_t PanelLOrR){

	uint8_t CurrentLEDBlinky=0;
	uint8_t CurrentLEDOnOff=0;
	uint8_t CurrentLEDSwitchOnDetection=0;
	uint8_t CurrentLEDSwitchOffDetection=0;
	uint8_t LedIndexActionListON[5]={0,0,0,0,0};
	uint8_t LedIndexActionListOFF[5]={0,0,0,0,0};
	//index for LedIndexActionList
	uint8_t k =0; // this index goes from 0 to 4, the same as number of spaces in LedIndexActionListON/OFF
	uint8_t j =0;
	//return status
	uint8_t ret=0;

	uint8_t IndexSwitch[3]={0,20,40};
	uint8_t IndexSwitchSelectStart =0;
	uint8_t IndexSwitchSelectStop =0;


	// local var for tracking blinky switches , max number of simulatanius blinking LEDs is 5
	if (PanelLOrR == 1){ // right panel
		IndexSwitchSelectStart =1;
		IndexSwitchSelectStop =2;
		}else if(PanelLOrR == 0){// LEFT panel
			IndexSwitchSelectStart =0;
			IndexSwitchSelectStop =1;
		}else{
			while(1);
		}


	for (uint8_t i= IndexSwitch[IndexSwitchSelectStart];i<  IndexSwitch[IndexSwitchSelectStop];i++){

		CurrentLEDBlinky = Tipke[i].LEDBlinky;
		 CurrentLEDOnOff = Tipke[i].LEDOnOff;
		CurrentLEDSwitchOnDetection = Tipke[i].SwitchOnDetection;
		CurrentLEDSwitchOffDetection = Tipke[i].SwitchOffDetection;

		// predpostavka: določena tipka lahko v eneme trenutku samo prižiga ali ugaša LED, ne more to narediti hkrati
		// zato  spidnji if stavek dela eno ali drugo
		// sestavlanje zbirke  actionlist za prižiganje LED
		if(CurrentLEDSwitchOnDetection == 1  && CurrentLEDOnOff ==0 && CurrentLEDBlinky ==0){

			LedIndexActionListON[j] = i;	// na eno od 5-ih mest dam trenutni index switcha, ki je bil prižgan
			// povečamo index j za naslednji element v listi LedIndexActionListON
			j= j+1;
			// zaščita za index j, če gre preko namišljene vrednosti , je to error
			if (j>4){// predpostavim da v enem branju strukture tipk, ne bo več kot 4 pritisnjene tipke
				return 1;
			}
			 Tipke[i].SwitchOnDetection = 0; //resetiramo flag
			 //current LED on off se postavi v funkciji za prižiganje LED

			 // sestavlanje zbirke  actionlist za ugašanje  LED
		} else if (CurrentLEDSwitchOnDetection == 1  && CurrentLEDOnOff ==1 && CurrentLEDSwitchOffDetection == 1 && CurrentLEDBlinky ==0) {

			LedIndexActionListOFF[k] = i;	// na eno od 5-ih mest dam trenutni index switcha, ki je bil prižgan
			// povečamo index j za naslednji element v listi LedIndexActionListON
			k= k+1;
			// zaščita za index j, če gre preko namišljene vrednosti , je to error
			if (k>4){// predpostavim da v enem branju strukture tipk, ne bo več kot 4 pritisnjene tipke
				return 1;
			}
			 Tipke[i].SwitchOnDetection = 0; //resetiramo flag
			 Tipke[i].SwitchOffDetection = 0; //resetiramo flag
			 //current LED on off se postavi v funkciji za prižiganje LED

			 //del za prižiganje  blinkija in start timerja
		}else if ((CurrentLEDSwitchOnDetection == 1 && CurrentLEDBlinky ==1  &&  gVarBlinky == 2  )||  \
				((gVarBlinky == 0 || gVarBlinky ==1 )&& ((CurrentBlinkySwitchIndex[0] != i)\
						&&(CurrentBlinkySwitchIndex[1] != i)\
						&&(CurrentBlinkySwitchIndex[2] != i)\
						&&(CurrentBlinkySwitchIndex[3] != i)\
						&&(CurrentBlinkySwitchIndex[4] != i)\

				) && CurrentLEDBlinky ==1 && CurrentLEDSwitchOnDetection == 1  )) {
			//one timer is used for all blinky, when one button enables the timer, the next blinky button should
			if (o < 1){
			//start timer
			HAL_TIM_Base_Start_IT(ArrayOfTimerPointers[1]);
			}

			//zapis switch Indeksa v CurrentBlinkySwitchIndex, tako lahko trackamo kateri switchi morajo utripati
			for (uint8_t w=0;w<5;w++){
						if(CurrentBlinkySwitchIndex[w] == 100){
							CurrentBlinkySwitchIndex[w] = i;
							break;
						}
			}



			//reset switch
			Tipke[i].SwitchOnDetection = 0;
			// povečamo index o za naslednji element v listi CurrentBlinkySwitchIndex
			o= o+1;
			// zaščita za index j, če gre preko namišljene vrednosti , je to error
			if (o>4){// predpostavim da v enem branju strukture tipk, ne bo več kot 4 pritisnjene tipke
				return 1;
			}

			//del za ugašanje  blinkija in end timerja timerja
		} else if (CurrentLEDSwitchOnDetection == 1 && CurrentLEDBlinky ==1 && CurrentLEDSwitchOffDetection == 1 && (gVarBlinky == 0 || gVarBlinky ==1 )) {
			// timer ugasnemo ko zadnjo tipko ki blinka ugasnemo, pred tem ne smemo ugasnit tajmerja!!
			if (o==1){

				HAL_TIM_Base_Stop_IT(ArrayOfTimerPointers[1]);

				//globalno spremenljivko postavimo na 2 tako, da se spodnja if stavka ne moreta sprožit
				gVarBlinky = 2;
			}
			//v globalni array je potrbno izbrisat trenutni index, ki se je pritisnil, ne vemo v kakšenem zaporedju se tej gumbi pritiskajo, zato
			//je potrbno pregledati celoten array
			for (uint8_t w=0;w<5;w++){
				if(CurrentBlinkySwitchIndex[w] == i){
					CurrentBlinkySwitchIndex[w] =100;
				}
			}
				// vse prižgane blinkije je potrebno ugasnit, ne vemo ali so takrat ko smo pritisnili switch prizgani ali niso prizgani,
			// array LedIndexActionListOFF je potrebno sestaviti tu, saj se kasnejši if stvki z gVarBlinky ne bodo prožili saj je gVarBlinky enak 2
				LedIndexActionListOFF[k] =i;
						// ob pisanju v LedIndexActionListOFF je potrebno zvišati indeks
						k++;
				//CurrentBlinkySwitchIndex[o] = 0;
			// ko se en blinky ugasen se mora indeks, ki tracka število prižganih blinkijev zmanjšate
				o = o-1;
				// zaščita za index j, če gre preko namišljene vrednosti , je to error
				if (o<0){// predpostavim da v enem branju strukture tipk, ne bo več kot 4 pritisnjene tipke
					return 1;
				}

			//resetiramo flag
			Tipke[i].SwitchOnDetection = 0;
			//resetiramo flag
			 Tipke[i].SwitchOffDetection = 0;
			 // postavimo blikija na 2, tako da se spodnji del kode, ki dodaja elemente v LedIndexActionListON ali LedIndexActionListOFF ne izvaja

		}
	} // for loop za branje tipk se konca

	//preverimo ali moramo v LedIndexActionListON ali LedIndexActionListOFF dodati kaksen index zaradi blinkija
	if (gVarBlinky == 0){// v tem primeru se LED ugasne
		//
		//for (uint8_t q=0; q<o;q++){

		// nekako v smislu, če je CurrentBlinkySwitchIndex[q] != 100 potem zapiši ta i v LedIndexActionList
		for (uint8_t w=0;w<5;w++){
			// preverimo ali je v globalnem arrayu, kaksna tipka
			if(CurrentBlinkySwitchIndex[w] != 100){
			//nalednji pogoji skrbijo za to da tipke iz levega panela ne ugašajo ledic
			// na desnem panelu
			if(PanelLOrR == 0){ // left panel
				//check if current switch index in global array belongs to left panel
				if((0 <= CurrentBlinkySwitchIndex[w]) && (CurrentBlinkySwitchIndex[w]< 20)){
					// CurrentBlinkySwitchIndex je globalni array, ki si zapomne, kater tipke so shranjene v blinkiju
					LedIndexActionListOFF[k] = CurrentBlinkySwitchIndex[w];
					// povecamo indeks za stevilo elementov, ki jih moramo dodati v strukturo LedIndexActionListOFF da jih kasneje ugasne
					k++;
				}
			} else if (PanelLOrR ==1 ) { // right panel
				if((20 <= CurrentBlinkySwitchIndex[w]) && (CurrentBlinkySwitchIndex[w]< 40)){
					// CurrentBlinkySwitchIndex je globalni array, ki si zapomne, kater tipke so shranjene v blinkiju
					LedIndexActionListOFF[k] = CurrentBlinkySwitchIndex[w];
					// povecamo indeks za stevilo elementov, ki jih moramo dodati v strukturo LedIndexActionListOFF da jih kasneje ugasne
					k++;
				}
			}else {
				while (1);
			}


			}
		}
	}else if (gVarBlinky== 1) { // v tem primeru se LED prizge
		//for (uint8_t q=0; q<o;q++){
					// CurrentBlinkySwitchIndex je globalni array, ki si zapomne, kater tipke so shranjene v blinkiju
		for (uint8_t w=0;w<5;w++){
			if(CurrentBlinkySwitchIndex[w] != 100){
					if(PanelLOrR == 0){ // left panel
						//check if current switch index in global array belongs to left panel
						if((0 <= CurrentBlinkySwitchIndex[w]) && (CurrentBlinkySwitchIndex[w]< 20)){
							// CurrentBlinkySwitchIndex je globalni array, ki si zapomne, kater tipke so shranjene v blinkiju
							LedIndexActionListON[j] = CurrentBlinkySwitchIndex[w];
							// povecamo indeks za stevilo elementov, ki jih moramo dodati v strukturo LedIndexActionListOFF da jih kasneje ugasne
							j++;
						}
					} else if (PanelLOrR ==1 ) { // right panel
						if((20 <= CurrentBlinkySwitchIndex[w]) && (CurrentBlinkySwitchIndex[w]< 40)){
							// CurrentBlinkySwitchIndex je globalni array, ki si zapomne, kater tipke so shranjene v blinkiju
							LedIndexActionListON[j] = CurrentBlinkySwitchIndex[w];
							// povecamo indeks za stevilo elementov, ki jih moramo dodati v strukturo LedIndexActionListOFF da jih kasneje ugasne
							j++;
						}
					}else {
						while (1);
					}
				}

		}

	}

	// preverjamo če je sploh bil kakšen vnos v LedIndexActionListON, če ni bilo nobenega vnosa
	//potem ni potrebe po pisanju v IS32 čip
	if (j > 0){
		// priziganje  LED
		ret =TurnOnLedn(DataFor_IS32,Tipke,LedIndexActionListON,j,PanelLOrR);
		if (ret != 0){
			while(1);
		}
	}
	// preverjamo če je sploh bil kakšen vnos v LedIndexActionListON, če ni bilo nobenega vnosa
		//potem ni potrebe po pisanju v IS32 čip
	if(k>0){
		//ugasanje LED
		ret = TurnOffLedn(DataFor_IS32,Tipke,LedIndexActionListOFF,k,PanelLOrR);
		if (ret != 0){
				while(1);
		}
	}



	return 0;
}


uint8_t CopyDataFromSliderToGenericInfoStruct(struct Switch *Tipke,struct  Slider *Sliders,struct SetUpAtStart *pGenericInfo){
	// check if Accent Tipka is pressed, Tipke[5] is Accent
	if (Tipke[5].LEDOnOff == 0){	// Accent tipka not pressed -> TEPO is being used for tempo
		//check if TEMPO SLIDER vas has changed
		if(PreviousTempoVal != Sliders[2].Index){
			//transfer data from Slider struct to GenericInfor struct
			//transfer TEMPO
			pGenericInfo -> Tempo = Sliders[2].Index;
			PreviousTempoVal = Sliders[2].Index;
		}
	}
	//set prescale
	if ((Tipke[4].LEDOnOff == 0) && (Tipke[3].LEDOnOff == 0)) {
	    pGenericInfo->Prescale_Status = 0;
	}
	if ((Tipke[4].LEDOnOff == 1) && (Tipke[3].LEDOnOff == 0)) {
	    pGenericInfo->Prescale_Status = 1;
	}
	if ((Tipke[4].LEDOnOff == 0) && (Tipke[3].LEDOnOff == 1)) {
	    pGenericInfo->Prescale_Status = 2;
	}
	if ((Tipke[4].LEDOnOff == 1) && (Tipke[3].LEDOnOff == 1)) {
	    pGenericInfo->Prescale_Status = 3;
	}
	// set var A/B
	if (Tipke[29].LEDOnOff == 0){ // button is not pressed
		pGenericInfo -> varA_B_Status = 0;	// only variant A is used
	} else if (Tipke[29].LEDOnOff == 1) {
		pGenericInfo -> varA_B_Status = 1;	// firstly varian A is used and then variant B
	}
	return 0;
}

uint8_t CopyDataFromSliderToInstrument(struct Instrument *Instruments,struct Switch *Tipke,struct  Slider *Sliders,uint8_t *InstrumentIndix){

	//check if there is any previously pressed instrument button
	if(Tipke[InstrumentIndix[CurrentPickedInstrument]].LEDOnOff == 1 ){
		for(uint8_t i =0; i<8;i++){ // go trough all instruments
			if (i != CurrentPickedInstrument){//
				//set all other instruments LED's OFF, except pressed instrument
				Tipke[InstrumentIndix[i]].SwitchOffDetection = 0;
				Tipke[InstrumentIndix[i]].SwitchOnDetection = 0;
			}
		}
		// check if Accent Tipka is pressed, Tipke[5] is Accent
					if (Tipke[5].LEDOnOff == 1){	// Accent tipka pressed -> TEMPO is being used for ACCENT
						//transfer data from Slider struct to Instrument struct
						//transfer ACCENT
						Instruments[CurrentPickedInstrument].Accent =  Sliders[2].Index;	// copy Accent slider data to Instrument struct
					}else if (Tipke[5].LEDOnOff == 0) {// if accent is not yet pressed defaul values of accent in 50
						Instruments[CurrentPickedInstrument].Accent = 100;
					}else {
						while(1);
					}
					//transfer Decay data only for BaseDrum (index 1) and SnareDrum (index 0), as only these two use Decay
					if((CurrentPickedInstrument == 0) || (CurrentPickedInstrument ==1)){
						Instruments[CurrentPickedInstrument].Decay = Sliders[1].Index; // copy Decay Slider data to Instrument structure
					}
					// TRANSFER out LEVEL FOR ALL INSTRUMENTS
					Instruments[CurrentPickedInstrument].OutLevel = Sliders[0].Index; // copy Out level Slider data to Instrument structure
	}else{

		// copy data from slider struct to Instrument struct
		for(uint8_t i =0; i<8;i++){ // go trough all instruments
			//check if any instrument button is pressed
			if (Tipke[InstrumentIndix[i]].SwitchOnDetection == 1){
				// to global variable we write which instrument is currenly being setup
				CurrentPickedInstrument = i;
				//for eliminating multiple pressing we set all other pressed button to not pressed
				for(uint8_t j =0; j<8;j++){ // go trough all instruments
						if (j != i){//
							//set all other instruments LED's OFF, except pressed instrument
							Tipke[InstrumentIndix[j]].SwitchOffDetection = 0;
							Tipke[InstrumentIndix[j]].SwitchOnDetection = 0;
						}
					}
				// check if Accent Tipka is pressed, Tipke[5] is Accent
				if (Tipke[5].SwitchOnDetection == 1){	// Accent tipka pressed -> TEMPO is being used for ACCENT
					//transfer data from Slider struct to Instrument struct
					//transfer ACCENT
					Instruments[i].Accent =  Sliders[2].Index;	// copy Accent slider data to Instrument struct
				}else if (Tipke[5].SwitchOnDetection == 0) {// if accent is not jet pressed defaul values of accent in 50
					Instruments[i].Accent = 50;
				}else {
					while(1);
				}
				//transfer Decay data only for BaseDrum (index 1) , SnareDrum (index 0), Cymbal (index 2), as only these three use Decay
				if((i == 0) || (i ==1)|| (i ==2)){
					Instruments[i].Decay = Sliders[1].Index; // copy Decay Slider data to Instrument structure
				}
				// TRANSFER out LEVEL FOR ALL INSTRUMENTS
				Instruments[i].OutLevel = Sliders[0].Index; // copy Out level Slider data to Instrument structure
			}
		}
	}
	return 0;
}

uint8_t MapButtonStepsToInstruments(struct Button *Buttons,struct Instrument *Instruments,struct Switch *Tipke,struct  Slider *Sliders,uint8_t *InstrumentIndix,uint8_t * NumberButtonIndex){
	uint8_t j=0;
	uint8_t InstrumenRepetionFlag=0;

	//chack what variant is it A or B

	//check if there is any pressed instruments
	if(Tipke[InstrumentIndix[CurrentPickedInstrument]].LEDOnOff == 1 ){
		//go trough all number buttons
		for(uint8_t i=0; i< 16;i++){
			//set accent level of each button to 0, if there are no instruments on this button
			// accent will be 0
			//Buttons[i].pointersToInstrument[0].Timer_Accent =0;
			//for each button set j index to 0
			j=0;
			//check if any button is pressed
			if(Tipke[NumberButtonIndex[i]].LEDOnOff == 1){
				//j=Buttons[i].NumOfInstruments;
				if ((j == 0) && (Buttons[i].NumOfInstruments == 0)){
					//write instrument pointer to button structure (array of pointers)
					Buttons[i].pointersToInstrument[j] =&Instruments[CurrentPickedInstrument];
					//after each writing increse counter of instrument in each Buttone
					//j++;
					Buttons[i].NumOfInstruments = 1;
					Buttons[i].InstrumentIndexOnThisBut[0] = CurrentPickedInstrument;
				} else {
					j=Buttons[i].NumOfInstruments;
				// check if this instrument is already written in the Buttons array
					for (uint8_t k = 0; k<j;k++){
						// if the instrument is already in the array go to next instance of button
						if (Buttons[i].InstrumentIndexOnThisBut[k] ==  CurrentPickedInstrument){
							//set the repetiotion flag
							InstrumenRepetionFlag = 1;
							break;
						}
					}
					//check flag,if the instruemnt is already present, do not write again
					if (InstrumenRepetionFlag !=1 ){

						//to local variable write number of used spaces in one Button Array for instruements
						j=Buttons[i].NumOfInstruments;
						if(j==NUM_OF_INSTRUMENTS_PER_NUMBER_BUT){
							j=0;
						}
						Buttons[i].InstrumentIndexOnThisBut[j] =  CurrentPickedInstrument;
						//write instrument pointer to button structure (array of pointers)
						Buttons[i].pointersToInstrument[j] =&Instruments[CurrentPickedInstrument];
						//after each writing increse counter of instrument in each Buttone
						j++;
						//check if j is bigger then max num of available spaces for instruement in one Button structure
						//if(j < NUM_OF_INSTRUMENTS_PER_NUMBER_BUT){
							//write counter j to struct Button
							Buttons[i].NumOfInstruments = j;
						//}else if (j == NUM_OF_INSTRUMENTS_PER_NUMBER_BUT) {
							// if j is bigger then the number of spaces in Button struct, reset j
							//Buttons[i].NumOfInstruments=0;
						//}
					}

					}
				}
		}
	}
	return 0;
}

uint8_t MapButtonStepsToInstrumentsAndCheckVar(struct Button *Buttons_varA,struct Button *Buttons_varB,struct Instrument *Instruments,struct Switch *Tipke,struct  Slider *Sliders,uint8_t *InstrumentIndix,uint8_t * NumberButtonIndex){
	if (Tipke[29].LEDOnOff == 0 ){ //var A
		MapButtonStepsToInstruments(Buttons_varA,Instruments,Tipke,Sliders,InstrumentIndix,NumberButtonIndex);
	} else if (Tipke[29].LEDOnOff == 1) { // var B
		MapButtonStepsToInstruments(Buttons_varB,Instruments,Tipke,Sliders,InstrumentIndix,NumberButtonIndex);
	}
	return 0;
}


uint8_t StartAccentTimer( TIM_HandleTypeDef *ArrayOfTimerPointers[3],uint16_t CCR_ms,uint16_t AAR_ms){
	//start timer
	HAL_TIM_PWM_Start_IT(ArrayOfTimerPointers[2], TIM_CHANNEL_2);
	 // HAL_TIM_Base_Start_IT
	//set PWM on time to 1 ms
	TIM4->CCR2 = CCR_ms;
	TIM4->ARR = AAR_ms;


	return 0;
}

uint8_t StopAccentTimer( TIM_HandleTypeDef *ArrayOfTimerPointers[3]){
	HAL_TIM_PWM_Stop_IT(ArrayOfTimerPointers[2], TIM_CHANNEL_2);
	return 0;
}

uint32_t ConvertBPM_ToTimerTicks(uint16_t BPM){
	uint32_t TimerTicks = 0;
	TimerTicks = 180000/(uint32_t)BPM;
	return TimerTicks;
}

uint8_t TurnONNumberLED(struct Switch *Tipke,uint8_t * NumberButtonIndex,uint8_t LEDIndex_1_16){
	Tipke[NumberButtonIndex[LEDIndex_1_16-1]].SwitchOnDetection = 1;
	Tipke[NumberButtonIndex[LEDIndex_1_16-1]].SwitchOffDetection = 0;

	return 0;
}

uint8_t TurnOFFNumberLED(struct Switch *Tipke,uint8_t * NumberButtonIndex,uint8_t LEDIndex_1_16){
	Tipke[NumberButtonIndex[LEDIndex_1_16-1]].SwitchOnDetection = 0;
	Tipke[NumberButtonIndex[LEDIndex_1_16-1]].SwitchOffDetection = 0;
	Tipke[NumberButtonIndex[LEDIndex_1_16-1]].LEDOnOff = 1;
	return 0;
}

uint8_t TurnOFFAllNumberLED(struct Switch *Tipke,uint8_t * NumberButtonIndex){
	for(uint8_t i = 1 ; i<17;i++){
		Tipke[NumberButtonIndex[i-1]].SwitchOnDetection = 1;
		Tipke[NumberButtonIndex[i-1]].SwitchOffDetection = 1;
		Tipke[NumberButtonIndex[i-1]].LEDOnOff = 1;
	}
	return 0;
}

uint8_t TurnOnSequencer(	struct Switch *Tipke,
							uint8_t * NumberButtonIndex,
							struct Button *Buttons_varA,
							struct Button *Buttons_varB,
							uint8_t ArrayOfTimerChannels[8][2],
							TIM_HandleTypeDef *ArrayOfTimerPointers2[8][2],
							uint16_t InstrumentEnablePin[9],
							GPIO_TypeDef* GPIO_INSTRUMENT_ENABLE[9],
							struct Instrument *Instruments){

	static uint8_t LocalCurrentNumberInSeqState = 0;
	uint8_t k;
	//check if sequencer number has changed, if it did do next steps
	if(LocalCurrentNumberInSeqState != CurrentNumberInSeqState){
		//__disable_irq();
		LocalCurrentNumberInSeqState= CurrentNumberInSeqState;

		//disable all instrumnets GPIOs from previous button
		//check that current LocalCurrentNumberInSeqState is not 1
		if(LocalCurrentNumberInSeqState != 1){
			//disable all instrumnets GPIOs from previous button
			for (uint8_t i = 0;i < Buttons_varA[LocalCurrentNumberInSeqState-2].NumOfInstruments;i++){
				k = Buttons_varA[LocalCurrentNumberInSeqState-2].InstrumentIndexOnThisBut[i];
				HAL_GPIO_WritePin(GPIO_INSTRUMENT_ENABLE[k+1], InstrumentEnablePin[k+1], GPIO_PIN_RESET);
			}
		}else{
			for (uint8_t i = 0;i < Buttons_varA[15].NumOfInstruments;i++){
				k = Buttons_varA[15].InstrumentIndexOnThisBut[i];
				HAL_GPIO_WritePin(GPIO_INSTRUMENT_ENABLE[k+1], InstrumentEnablePin[k+1], GPIO_PIN_RESET);
			}
		}

		//__enable_irq();

		//this is more of a feature then a bug :), accent for the current number is used from the first instrument in the array the button holds
		// this function sets the duty cycle in ACCENT level timer
		__HAL_TIM_SET_COMPARE(	ArrayOfTimerPointers2[2][0],// &htim3
								ArrayOfTimerChannels[0][1], // TIM_CHANNLEL_1
								//Instruments[LocalCurrentNumberInSeqState-1].Timer_Accent); <- to ni vredu, samo prvih osem bo ok, nasledjnih 8 bo random
								Buttons_varA[LocalCurrentNumberInSeqState-1].pointersToInstrument[0]->Timer_Accent);
		//turn off all  LEDs
		for(uint8_t i = 1 ; i<17;i++){
			if(LocalCurrentNumberInSeqState != i){
				Tipke[NumberButtonIndex[i-1]].SwitchOnDetection = 1;
				Tipke[NumberButtonIndex[i-1]].SwitchOffDetection = 1;
				Tipke[NumberButtonIndex[i-1]].LEDOnOff = 1;
			}
		}
		//turn on 1 LED
		Tipke[NumberButtonIndex[LocalCurrentNumberInSeqState-1]].SwitchOnDetection = 1;
		Tipke[NumberButtonIndex[LocalCurrentNumberInSeqState-1]].SwitchOffDetection = 0;
		Tipke[NumberButtonIndex[LocalCurrentNumberInSeqState-1]].LEDOnOff = 0;

		//enable instruments GPIOs that are saved under this button
		// go trough all instruments saved under current Button
		for(uint8_t i = 0;i < Buttons_varA[LocalCurrentNumberInSeqState-1].NumOfInstruments;i++){
			k = Buttons_varA[LocalCurrentNumberInSeqState-1].InstrumentIndexOnThisBut[i];
			HAL_GPIO_WritePin(GPIO_INSTRUMENT_ENABLE[k+1], InstrumentEnablePin[k+1], GPIO_PIN_SET);
		}

	}
	return 0;
}

uint8_t CheckStructTipkeSequencerMode(struct SendData_BUT21 * DataFor_IS32,struct Switch *Tipke,uint8_t PanelLOrR){

	uint8_t CurrentLEDBlinky=0;
	uint8_t CurrentLEDOnOff=0;
	uint8_t CurrentLEDSwitchOnDetection=0;
	uint8_t CurrentLEDSwitchOffDetection=0;
	uint8_t LedIndexActionListON[5]={0,0,0,0,0};
	uint8_t LedIndexActionListOFF[10]={0,0,0,0,0,0,0,0,0,0};
	//index for LedIndexActionList
	uint8_t k =0; // this index goes from 0 to 4, the same as number of spaces in LedIndexActionListON/OFF
	uint8_t j =0;
	//return status
	uint8_t ret=0;

	uint8_t IndexSwitch[3]={0,20,40};
	uint8_t IndexSwitchSelectStart =0;
	uint8_t IndexSwitchSelectStop =0;


	// local var for tracking blinky switches , max number of simulatanius blinking LEDs is 5
	if (PanelLOrR == 1){ // right panel
		IndexSwitchSelectStart =1;
		IndexSwitchSelectStop =2;
		}else if(PanelLOrR == 0){// LEFT panel
			IndexSwitchSelectStart =0;
			IndexSwitchSelectStop =1;
		}else{
			while(1);
		}


	for (uint8_t i= IndexSwitch[IndexSwitchSelectStart];i<  IndexSwitch[IndexSwitchSelectStop];i++){

		CurrentLEDBlinky = Tipke[i].LEDBlinky;
		 CurrentLEDOnOff = Tipke[i].LEDOnOff;
		CurrentLEDSwitchOnDetection = Tipke[i].SwitchOnDetection;
		CurrentLEDSwitchOffDetection = Tipke[i].SwitchOffDetection;

		// predpostavka: določena tipka lahko v eneme trenutku samo prižiga ali ugaša LED, ne more to narediti hkrati
		// zato  spidnji if stavek dela eno ali drugo
		// sestavlanje zbirke  actionlist za prižiganje LED
		if(CurrentLEDSwitchOnDetection == 1  && CurrentLEDOnOff ==0 && CurrentLEDBlinky ==0){

			LedIndexActionListON[j] = i;	// na eno od 5-ih mest dam trenutni index switcha, ki je bil prižgan
			// povečamo index j za naslednji element v listi LedIndexActionListON
			j= j+1;
			// zaščita za index j, če gre preko namišljene vrednosti , je to error
			if (j>4){// predpostavim da v enem branju strukture tipk, ne bo več kot 4 pritisnjene tipke
				return 1;
			}
			 Tipke[i].SwitchOnDetection = 0; //resetiramo flag
			 //current LED on off se postavi v funkciji za prižiganje LED

			 // sestavlanje zbirke  actionlist za ugašanje  LED
		} else if (CurrentLEDSwitchOnDetection == 1  && CurrentLEDOnOff ==1 && CurrentLEDSwitchOffDetection == 1 && CurrentLEDBlinky ==0) {

			LedIndexActionListOFF[k] = i;	// na eno od 5-ih mest dam trenutni index switcha, ki je bil prižgan
			// povečamo index j za naslednji element v listi LedIndexActionListON
			k= k+1;
			// zaščita za index j, če gre preko namišljene vrednosti , je to error
			if (k>9){// predpostavim da v enem branju strukture tipk, ne bo več kot 4 pritisnjene tipke
				return 1;
			}
			 Tipke[i].SwitchOnDetection = 0; //resetiramo flag
			 Tipke[i].SwitchOffDetection = 0; //resetiramo flag
			 //current LED on off se postavi v funkciji za prižiganje LED

		}
	}

	// preverjamo če je sploh bil kakšen vnos v LedIndexActionListON, če ni bilo nobenega vnosa
	//potem ni potrebe po pisanju v IS32 čip
	if (j > 0){
		// priziganje  LED
		ret =TurnOnLedn(DataFor_IS32,Tipke,LedIndexActionListON,j,PanelLOrR);
		if (ret != 0){
			while(1);
		}
	}
	// preverjamo če je sploh bil kakšen vnos v LedIndexActionListON, če ni bilo nobenega vnosa
		//potem ni potrebe po pisanju v IS32 čip
	if(k>0){
		//ugasanje LED
		ret = TurnOffLedn(DataFor_IS32,Tipke,LedIndexActionListOFF,k,PanelLOrR);
		if (ret != 0){
				while(1);
		}
	}
	return 0;
}

uint8_t ConvertInstrumentDataToTimers(struct Instrument *Instruments){
	// go trough all instruments
	for(uint8_t i =0;i<8;i++){
		// convert accent values from 0-100 to 0-255
		Instruments[i].Timer_Accent = (255*(uint16_t)(Instruments[i].Accent))/100;
		// convert decay values from 0-100 to 0-255
		Instruments[i].Timer_Decay = (255*(uint16_t)(Instruments[i].Decay))/100;
		// convert level values from 0-100 to 0-255
		Instruments[i].Timer_OutLevel = (255*(uint16_t)(Instruments[i].OutLevel))/100;
	}

	return 0;
}

uint8_t SetInstrumentValToDefault(struct Instrument *Instruments,uint8_t NumOfIterations){
	// go trough all instruments
	for(uint8_t i =0;i<NumOfIterations;i++){
		Instruments[i].Accent = 0;
		Instruments[i].Decay = 0;
		Instruments[i].OutLevel = 0;
		Instruments[i].Timer_Accent = 0;
		Instruments[i].Timer_Decay = 0;
		Instruments[i].Timer_OutLevel = 0;

	}

	return 0;
}

uint8_t SetAndStartTimers(struct Instrument *Instruments,uint8_t ArrayOfTimerChannels[8][2],TIM_HandleTypeDef *ArrayOfTimerPointers2[8][2]){
	//i goes trough all instruments 0 - 9
	//j goes trough level and decay of each insrument 0 -2
	for(uint8_t i = 0;i<9;i++){
		//check if the timer handled pointer is NULL, if it, there is no timer
		for(uint8_t j = 0; j<2;j++){
			if(ArrayOfTimerPointers2[i][j] != NULL){
				//chech if the array has 0 as the channel-> timer does not exist, do not start
				if(ArrayOfTimerChannels[i][j] != 10){
					// start timer
					HAL_TIM_PWM_Start(ArrayOfTimerPointers2[i][j], (uint32_t)ArrayOfTimerChannels[i][j]);
					// set timer duty cycle from Instruments structure array
					if(j == 0){ //set level
						__HAL_TIM_SET_COMPARE(ArrayOfTimerPointers2[i][j], (uint32_t)ArrayOfTimerChannels[i][j], Instruments[i].Timer_OutLevel);
					}else if (j==1) {// set decay
						__HAL_TIM_SET_COMPARE(ArrayOfTimerPointers2[i][j], (uint32_t)ArrayOfTimerChannels[i][j], Instruments[i].Timer_Decay);
					}

				}
			}
		}
	}
	return 0;
}


