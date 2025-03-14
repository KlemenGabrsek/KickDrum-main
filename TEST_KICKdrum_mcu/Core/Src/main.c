/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim11;
TIM_HandleTypeDef htim12;
TIM_HandleTypeDef htim13;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM11_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM10_Init(void);
static void MX_TIM12_Init(void);
static void MX_TIM13_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
I2C_HandleTypeDef * phi2c1 = &hi2c1;
I2C_HandleTypeDef * phi2c3 = &hi2c2;

//flag za BUT21 interrupt
	uint8_t BUT21CallBack = 0;
	uint8_t BUT21CallBack_R = 0;
	uint8_t o=0;

	uint8_t LedControlRegAll_[2][3]={{0,0,0},{0,0,0}};

    uint8_t PwmControlReg1_18_[2][4][5] = {
        {
            {0, 0, 0, 0, 0},  // First row of first 2D array
            {0, 0, 0, 0, 0},  // Second row of first 2D array
            {0, 0, 0, 0, 0},  // Third row of first 2D array
            {0, 0, 0, 0, 0}   // Fourth row of first 2D array
        },
        {
            {0, 0, 0, 0, 0},  // First row of second 2D array
            {0, 0, 0, 0, 0},  // Second row of second 2D array
            {0, 0, 0, 0, 0},  // Third row of second 2D array
            {0, 0, 0, 0, 0}   // Fourth row of second 2D array
        }
    };

		uint8_t gVarBlinky =2;
		uint8_t CurrentBlinkySwitchIndex[5]={100,100,100,100,100};

//global var for checking if Tempo slider value changed
uint16_t PreviousTempoVal =0;

//current picked instrument
uint8_t CurrentPickedInstrument = 0;

// current number in sequencer mode
uint8_t CurrentNumberInSeqState = 1;



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	// array for storing enable GPIOs of each instrument
	uint16_t InstrumentEnablePin[] = GPIO_PIN_INSTRUMENT_ENABLE;
	GPIO_TypeDef* GPIO_INSTRUMENT_ENABLE[] = {
	    GPIOB,
	    GPIOB,
		GPIOA,
	    GPIOC,
	    GPIOB,
	    GPIOB,
	    GPIOC,
	    GPIOC,
	    GPIOB
	};


	 /*variables for determinating KickDrum State
	       * ____________________________________________________________________________________
	       */
	      	  uint8_t KickDrumState = 0;
	      	  // 0 -> SELECT/PROGRAM INSTRUMENT
	      	  // 1 -> SEQUENCER

	      /*
	       * ____________________________________________________________________________________
	       */

	  //WHAT INDEX (TIPKA 0-39) DOES EACH INSTRUMENT HAVE
	  uint8_t InstrumentIndix[] = INSTRUMENTINDEX;

	  //each number button has its own number/index in Tipke array
	  uint8_t NumberButtonIndex[]=NUMBUT_ARRAY;

	//zbirka instrumentov, trenutno bo stevilo instrumentov enako stevilu vseh instruemntov, vsak
	//instrument bo imel samo eno vrednost -> zaenkrat
	/*
	 *  0 -BaseDrum				Instruments[0]
	 *  1 -SnareDrum			Instruments[1]
	 * 2 -Claves						Instruments[2]
	 *3-Claves						Instruments[3]
	 *4-Conga						Instruments[4]
	 *5-Cowbell					Instruments[5]
	 *6-Tom							Instruments[6]
	 *7-RimShot					Instruments[7]
	 */
	struct Instrument Instruments[8];
	struct Instrument InstrumentDummyZero;
	struct Instrument *pInstrumentDummyZero = &InstrumentDummyZero;


	//set all instrument values to defaul
	SetInstrumentValToDefault(Instruments,8);
	//set one instrumet as a dummy with all zeros
	SetInstrumentValToDefault(pInstrumentDummyZero,1);

	//zbirka struktur za tipke, vsaka tipka ima 6 pointerjev, tako da lahko nosi

	/*
	 *  1 - Button[0]
	 *  2 - Button[1]
	 *  3 - Button[2]
	 *  4 - Button[3]
	 *  5 - Button[4]
	 *  6 - Button[5]
	 *  7 - Button[6]
	 *  8 - Button[7]
	 *  9 - Button[8]
	 * 10 - Button[9]
	 * 11 - Button[10]
	 * 12 - Button[11]
	 * 13 - Button[12]
	 * 14 - Button[13]
	 * 15 - Button[14]
	 */

	struct Button Buttons_varA[16];
	struct Button Buttons_varB[16];


	for (uint8_t i =0;i<16;i++){
		Buttons_varA[i].NumOfInstruments=0;
		Buttons_varA[i].pointersToInstrument[0]=pInstrumentDummyZero;
		for(uint8_t l = 0;l<NUM_OF_INSTRUMENTS_PER_NUMBER_BUT;l++){
			Buttons_varA[i].InstrumentIndexOnThisBut[l]=0;
		}
	}

	for (uint8_t i =0;i<16;i++){
			Buttons_varB[i].NumOfInstruments=0;
			Buttons_varB[i].pointersToInstrument[0]=pInstrumentDummyZero;
			for(uint8_t l = 0;l<NUM_OF_INSTRUMENTS_PER_NUMBER_BUT;l++){
				Buttons_varB[i].InstrumentIndexOnThisBut[l]=0;
			}
		}

	// struct for holding generic information
	struct SetUpAtStart GenericInfo;
	struct SetUpAtStart *pGenericInfo=&GenericInfo;

	pGenericInfo->Prescale_Status = 0;	//normal speed
	pGenericInfo->Tempo = 100;			// generic tempo in BPM
	pGenericInfo->varA_B_Status = 0; // no prescale

	struct SendData_BUT21 DataFor_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING];
	struct SendData_BUT21 DataFor_IS32_R[NUM_OF_IS32_STRUCT_FOR_SENDING];
	 //uint8_t I2cReturnBUT21 = 0;

	 // ZBIRKA ZA VSE TIMERJE, za lažje podajanje v funkcije
	 //ArrayOfTimerPointers[1] SE uporablja za blinky funkcijo

	 TIM_HandleTypeDef *ArrayOfTimerPointers1[] = {&htim1,&htim10,&htim8}; // array for accent timer start and for blinky


	 TIM_HandleTypeDef *ArrayOfTimerPointers2[][2] = {{&htim1,&htim1}, //timers for basedrum
	 												 {&htim2,&htim5}, // timer for snare drum
	 												 {&htim3,&htim12}, // timer for cymbal
	 												 {&htim2,NULL},// timer for Claves
	 												 {&htim13,NULL}, // timer for conga
	 												 {&htim12,NULL},	// timer for cowbell
	 												 {&htim3,NULL}, // timer for tom
	 												 {&htim2,NULL}}; // timer for rimshot
	 uint8_t ArrayOfTimerChannels[][2] = {	{TIM_CHANNEL_2,TIM_CHANNEL_1 }, // base drum
											 {TIM_CHANNEL_2,TIM_CHANNEL_1 },	//snare drum
											 {TIM_CHANNEL_4,TIM_CHANNEL_2 },	//cymbal
											 {TIM_CHANNEL_3,10 },	//claves
											 {TIM_CHANNEL_1,10 },	//conga
											 {TIM_CHANNEL_1,10 },	//cowbell
											 {TIM_CHANNEL_3,10 },	//tom
											 {TIM_CHANNEL_4,10 }};	//rimshot

	 //define I2C address for BUT21
	 	uint16_t AddrBUT21_I2C =0xB8;
	 	//Dummy Interrupt factor pointer, to je pointer do registra v katerega se prepiše Interrupt Factor iz BUT21

	 	//define instances of Switch structure, each instance represents a Capacitive sensor
	 	struct Switch Tipke[NUM_OF_SWITCHES];
	 	//Assign data to each instance
	 	InitSwitchesTipke(Tipke);
	 	// define instances of Send and Receive Data sturctures for ease of passing them as a argument in functions
	 	//DATA structures for LEFT BUT21
	 	struct ReceiveData_BUT21 DataFrom_BUT21[12];
	 	struct SendData_BUT21 DataFor_BUT21[14];
	 	//DATA structures for RIGHT BUT21
	 	struct ReceiveData_BUT21 DataFrom_BUT21_R[12];
	 	struct SendData_BUT21 DataFor_BUT21_R[14];
	 	//struct SendData_BUT21 DataFor_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING];
	 	//define instance of struct Slider
	 	struct Slider Sliders[NUMBER_OF_SLIDERS];
	 	//return variable for ChangeIndexVal
	 	uint8_t ChangeIndexVal_ret =0;
	 	/*
	 	 * adding GENERAL info to Sliders(NAMES, DEFAUL VALUES)
	 	 */
	 	SliderSetUp(Sliders);

	 	//Data from Tipke has to be converted to register form, which can be written to BUT21 registers
	 		//_________________________________________________________________________________________________________________________________________
	 		//_________________________________________________________________________________________________________________________________________
	 		//SETTING THE CONFIGURATION for BUT21 left - only writting to DataFor_BUT21[0]
	 		//creation of registers to be written
	 		uint8_t	RegDataForSensroFun[SIZE_SENSOR_FUNCTION]={0x00,0x00,0x00,0x00,0x00};
	 		uint8_t	RegDataForSENSITIVITY[SIZE_SENSITIVITY]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	 		uint8_t	RegDataForONOFFTreshold[SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	 		//this register updates the configuration registers and starts measurements
	 		uint8_t RegSensorControl[SIZE_SENSOR_CONTROL] = SENSOR_CONTROL;
	 		uint8_t RegLDOControl[SIZE_AVDD_LDO_CONTROL] =AVDD_LDO_CONTROL;

	 		//functions that convert
	 		PrepDataForSensorFunctionReg(RegDataForSensroFun, Tipke,0);
	 		PrepDataForSensitivityReg(RegDataForSENSITIVITY, Tipke);
	 		PrepDataForONOFFTresholdReg(RegDataForONOFFTreshold, Tipke,0);


	 		//array of registers, ready to be written to IC, everytime a new register for a new BUT21 feature is implemented,the following 3 arrays need to be updated, a new register is added to the end
	 		uint8_t NumOfRegForIC=5;//number of registers to be written to in IC_BUT21
	 		uint8_t *RegistersForIC_BUT21[5]={RegDataForSensroFun,RegDataForSENSITIVITY,RegDataForONOFFTreshold,RegLDOControl,RegSensorControl};// RegSensorControll mora vedno biti zadnji, saj
	 		//v podatkovnem listu piše da preko bita STR_CFG updejtamo vse spremembe v konfiguracijskih registrih
	 		//size of array of registers, this info is needed when writing to register via I2C, length of data is needed
	 		uint16_t RegistersSizeForIC_BUT21[5]={SIZE_SENSOR_FUNCTION,SIZE_SENSITIVITY,SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD,SIZE_AVDD_LDO_CONTROL,SIZE_SENSOR_CONTROL};
	 		uint16_t RegistersAddrForIC_BUT21[5]={ADDR_SENSOR_FUNCTION,ADDR_SENSITIVITY,ADDR_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD,ADDR_AVDD_LDO_CONTROL,ADDR_SENSOR_CONTROL};

	 		//writing data to stucture for easy passing to function
	 		DataFor_BUT21[0].NumOfRegForSendData_BUT21 = 5;
	 		DataFor_BUT21[0].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		DataFor_BUT21[0].I2CHandlerForBUT21 =phi2c1;
	 		DataFor_BUT21[0].SizeOfDataBlockInIC = 1;

	 	for (uint8_t i =0; i<NumOfRegForIC; i++){
	 			DataFor_BUT21[0].RegisterNameForSendData_BUT21[i] = RegistersForIC_BUT21[i];
	 			DataFor_BUT21[0].RegistersAddrForSendData_BUT21[i] = RegistersAddrForIC_BUT21[i];
	 			DataFor_BUT21[0].RegistersSizeForSendData_BUT21[i] =  RegistersSizeForIC_BUT21[i];
	 	}
	 	//_________________________________________________________________________________________________________________________________________
	 	//_________________________________________________________________________________________________________________________________________
	 	// //SETTING THE CONFIGURATION for BUT21 RIGHT- only writting to DataFor_BUT21_R[0]

	 	uint8_t	RegDataForSensroFun_R[SIZE_SENSOR_FUNCTION]={0x00,0x00,0x00,0x00,0x00};
	 		uint8_t	RegDataForSENSITIVITY_R[SIZE_SENSITIVITY]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	 		uint8_t	RegDataForONOFFTreshold_R[SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	 		//this register updates the configuration registers and starts measurements
	 		uint8_t RegSensorControl_R[SIZE_SENSOR_CONTROL] = SENSOR_CONTROL;
	 		uint8_t RegLDOControl_R[SIZE_AVDD_LDO_CONTROL] =AVDD_LDO_CONTROL;

	 		//functions that convert
	 		PrepDataForSensorFunctionReg(RegDataForSensroFun_R, Tipke,1);
	 		PrepDataForSensitivityReg(RegDataForSENSITIVITY_R, Tipke);
	 		PrepDataForONOFFTresholdReg(RegDataForONOFFTreshold_R, Tipke,1);


	 		//array of registers, ready to be written to IC, everytime a new register for a new BUT21 feature is implemented,the following 3 arrays need to be updated, a new register is added to the end
	 		//uint8_t NumOfRegForIC=5;//number of registers to be written to in IC_BUT21 this variable is defined and set before
	 		uint8_t *RegistersForIC_BUT21_R[5]={RegDataForSensroFun_R,\
	 																		RegDataForSENSITIVITY_R,\
	 																		RegDataForONOFFTreshold_R,\
	 																		RegLDOControl_R,\
	 																		RegSensorControl_R};// RegSensorControll mora vedno biti zadnji, saj
	 		//v podatkovnem listu piše da preko bita STR_CFG updejtamo vse spremembe v konfiguracijskih registrih
	 		//size of array of registers, this info is needed when writing to register via I2C, length of data is needed
	 		//spidnje dva registra sta lahko enaka prejšnim, saj se ne sprememnita
	 		//uint16_t RegistersSizeForIC_BUT21[5]={SIZE_SENSOR_FUNCTION,SIZE_SENSITIVITY,SIZE_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD,SIZE_AVDD_LDO_CONTROL,SIZE_SENSOR_CONTROL};
	 		//uint16_t RegistersAddrForIC_BUT21[5]={ADDR_SENSOR_FUNCTION,ADDR_SENSITIVITY,ADDR_SWITCH_ON_TRESHOLD_SWITCH_OFF_TRESHOLD,ADDR_AVDD_LDO_CONTROL,ADDR_SENSOR_CONTROL};

	 		//writing data to stucture for easy passing to function
	 		DataFor_BUT21_R[0].NumOfRegForSendData_BUT21 = 5;
	 		DataFor_BUT21_R[0].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		DataFor_BUT21_R[0].I2CHandlerForBUT21 =phi2c3;
	 		DataFor_BUT21_R[0].SizeOfDataBlockInIC = 1;

	 	for (uint8_t i =0; i<NumOfRegForIC; i++){
	 			DataFor_BUT21_R[0].RegisterNameForSendData_BUT21[i] = RegistersForIC_BUT21_R[i];
	 			DataFor_BUT21_R[0].RegistersAddrForSendData_BUT21[i] = RegistersAddrForIC_BUT21[i];
	 			DataFor_BUT21_R[0].RegistersSizeForSendData_BUT21[i] =  RegistersSizeForIC_BUT21[i];
	 	}

	 	//_________________________________________________________________________________________________________________________________________
	 	//_________________________________________________________________________________________________________________________________________
	 		//REGISTERS for sending data to  BUT21 to set the sliders for multipattern detection
	 		//register RegDataForMultiplePatternSwitchesAssignment is separate for left and right panel
	 		uint8_t RegDataForMultiplePatternSwitchesAssignment[SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT] = MULTIPLE_PATTERN_SWITCH_ASSIGNMENT_L;
	 		//register RegSwitchDetectionTime is the saem for left and right panel
	 		uint8_t RegSwitchDetectionTime = SWITCH_DETECTION_TIME;
	 		//register RegControlMode is the same for left and right panel
	 		uint8_t RegContolMode = CONTROL_MODE;
	 		//writing data to stucture for easy passing to function, for Left panel
	 		DataFor_BUT21[13].NumOfRegForSendData_BUT21 = 3;
	 		DataFor_BUT21[13].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		DataFor_BUT21[13].I2CHandlerForBUT21 =phi2c1;
	 		DataFor_BUT21[13].SizeOfDataBlockInIC = 1;
	 		DataFor_BUT21[13].RegisterNameForSendData_BUT21[0] = RegDataForMultiplePatternSwitchesAssignment;
	 		DataFor_BUT21[13].RegistersAddrForSendData_BUT21[0] = ADDR_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT;
	 		DataFor_BUT21[13].RegistersSizeForSendData_BUT21[0] =  SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT;

	 		DataFor_BUT21[13].RegisterNameForSendData_BUT21[1] = &RegSwitchDetectionTime;
	 		DataFor_BUT21[13].RegistersAddrForSendData_BUT21[1] = ADDR_SWITCH_DETECTION_TIME;
	 		DataFor_BUT21[13].RegistersSizeForSendData_BUT21[1] =  SIZE_SWITCH_DETECTION_TIME;
	 		/*
	 		 * with this command we are changing the bit "MLT_SW_EN: Multiple Switches Control" from 1 to 0, this
	 		 * enables multiple pattern switch detection
	 		 */

	 		DataFor_BUT21[13].RegisterNameForSendData_BUT21[2] = &RegContolMode;
	 		DataFor_BUT21[13].RegistersAddrForSendData_BUT21[2] = ADDR_CONTROL_MODE;
	 		DataFor_BUT21[13].RegistersSizeForSendData_BUT21[2] =  SIZE_CONTROL_MODE;
	 		//_________________________________________________________________________________________________________________________________________

	 		uint8_t RegDataForMultiplePatternSwitchesAssignment_R[SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT] = MULTIPLE_PATTERN_SWITCH_ASSIGNMENT_R;
	 		//writing data to stucture for easy passing to function, for right panel
	 		DataFor_BUT21_R[13].NumOfRegForSendData_BUT21 = 3;
	 		DataFor_BUT21_R[13].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		DataFor_BUT21_R[13].I2CHandlerForBUT21 =phi2c3;
	 		DataFor_BUT21_R[13].SizeOfDataBlockInIC = 1;
	 		DataFor_BUT21_R[13].RegisterNameForSendData_BUT21[0] = RegDataForMultiplePatternSwitchesAssignment_R;
	 		DataFor_BUT21_R[13].RegistersAddrForSendData_BUT21[0] = ADDR_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT;
	 		DataFor_BUT21_R[13].RegistersSizeForSendData_BUT21[0] =  SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT;

	 		DataFor_BUT21_R[13].RegisterNameForSendData_BUT21[1] = &RegSwitchDetectionTime;
	 		DataFor_BUT21_R[13].RegistersAddrForSendData_BUT21[1] = ADDR_SWITCH_DETECTION_TIME;
	 		DataFor_BUT21_R[13].RegistersSizeForSendData_BUT21[1] =  SIZE_SWITCH_DETECTION_TIME;
	 		/*
	 		 * with this command we are changing the bit "MLT_SW_EN: Multiple Switches Control" from 1 to 0, this
	 		 * enables multiple pattern switch detection
	 		 */

	 		DataFor_BUT21_R[13].RegisterNameForSendData_BUT21[2] = &RegContolMode;
	 		DataFor_BUT21_R[13].RegistersAddrForSendData_BUT21[2] = ADDR_CONTROL_MODE;
	 		DataFor_BUT21_R[13].RegistersSizeForSendData_BUT21[2] =  SIZE_CONTROL_MODE;



	 	//_________________________________________________________________________________________________________________________________________
	 	//_________________________________________________________________________________________________________________________________________
	 		//REGISTERS for received data from BUT21 LEFT PANEL
	 		//initialize registers
	 	/*
	 	This creates first element in DataFrom_BUT21, DataFrom_BUT21[0] -> InterruptFactor, SensorControl, DataForSensorFunRead
	 	Tu lahko dodaš še ve�? registrov, ki jih bi želel brati za diagnostiko in testiranje

	 	*/
	 		uint8_t InterruptFactor[SIZE_INTERRUPT_FACTOR]={0x00,0x00,0x00};
	 		uint8_t RegSensorControlRead[SIZE_SENSOR_CONTROL] = {0x00};  // in this register all switches are set as sensors or HIgh Z or low..
	 		uint8_t RegDataForSensroFunRead[SIZE_SENSOR_FUNCTION]={0x00,0x00,0x00,0x00,0x00};// this register must be read to determinate the correctness of configuration

	 	//These registers will each be a separate instance of DataFromBUT21, because not all are needed to be read... depending on the interrupt factor just some have to be read.
	 		uint8_t RegSwitchOnDetection[SIZE_SWITCH_ON_DETECTION]={0x00,0x00,0x00};
	 		uint8_t RegSwitchOffDetection[SIZE_SWITCH_OFF_DETECTION]={0x00,0x00,0x00};
	 		uint8_t RegSwitchLongPressDetection[SIZE_SWITCH_LONG_PRESS_DETECTION]={0x00,0x00,0x00};
	 		uint8_t RegSwitchRepeatedLongPressDetection[SIZE_SWITCH_REPEATED_LONG_PRESS_DETECTION]={0x00,0x00,0x00};
	 		uint8_t RegMultiPatternSwitchesOnDetection[SIZE_MULTIPLE_PATTERN_SWITCH_ON_DETECTION]={0x00};
	 		uint8_t RegMultiPatternSwitchesOffDetection[SIZE_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION]={0x00};
	 		uint8_t RegUnexpectedLongPressDetection[SIZE_UNEXPECTED_LONG_PRESS_DETECTION]={0x00,0x00,0x00};
	 		uint8_t RegSwitchOnOffState[SIZE_SWITCH_ON_OFF_STATE]={0x00,0x00,0x00};
	 		uint8_t RegStateOfIC[SIZE_STATE_OF_IC]={0x00};
	 		uint8_t RegMultiplePatternSwitchesAssignment[SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
	 				0x00,0x00,0x00,0x00};
	 		uint8_t RegSwitchDetectionTimeRead[SIZE_SWITCH_DETECTION_TIME] = {0x00};


	 	////////////////////////////////////PrEPARING DATA FOR  DataFrom_BUT21[0]
	 		// determinate number of registers
	 		uint8_t NumOfRegReadFromIC=3;
	 		//pointer to arrays where data will be be stored
	 		uint8_t *DataFromIC_BUT21[3] = {InterruptFactor,RegSensorControlRead,RegDataForSensroFunRead};
	 	//size of registers and address of registers
	 		uint16_t AddrDataFromIC_BUT21_1[3] = {ADDR_INTERRUPT_FACTOR,ADDR_SENSOR_CONTROL,ADDR_SENSOR_FUNCTION};
	 		uint16_t SizeDataFromIC_BUT21_1[3] = {SIZE_INTERRUPT_FACTOR,SIZE_SENSOR_CONTROL,SIZE_SENSOR_FUNCTION};
	 		////////////////////////////////////
	 		////////////////////////////////////PrEPARING DATA FOR  DataFrom_BUT21[1],DataFrom_BUT21[2].....DataFrom_BUT21[10]
	 		uint8_t* RegToBeReadDepIntFac[11] = {RegSwitchOnDetection,       RegSwitchOffDetection,		RegSwitchLongPressDetection,		RegSwitchRepeatedLongPressDetection,		RegMultiPatternSwitchesOnDetection,		RegMultiPatternSwitchesOffDetection,		RegUnexpectedLongPressDetection,		RegSwitchOnOffState,		RegStateOfIC,RegMultiplePatternSwitchesAssignment,RegSwitchDetectionTimeRead};
	 			uint16_t AddrDataFromIC_BUT21_2[11] = {ADDR_SWITCH_ON_DETECTION,  	ADDR_SWITCH_OFF_DETECTION,		ADDR_SWITCH_LONG_PRESS_DETECTION, ADDR_SWITCH_REPEATED_LONG_PRESS_DETECTION, ADDR_MULTIPLE_PATTERN_SWITCH_ON_DETECTION,ADDR_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION, ADDR_UNEXPECTED_LONG_PRESS_DETECTION, ADDR_SWITCH_ON_OFF_STATE,ADDR_STATE_OF_IC, ADDR_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT,ADDR_SWITCH_DETECTION_TIME};
	 			uint16_t SizeDataFromIC_BUT21_2[11] ={SIZE_SWITCH_ON_DETECTION, SIZE_SWITCH_OFF_DETECTION, SIZE_SWITCH_LONG_PRESS_DETECTION, SIZE_SWITCH_REPEATED_LONG_PRESS_DETECTION, SIZE_MULTIPLE_PATTERN_SWITCH_ON_DETECTION, SIZE_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION, SIZE_UNEXPECTED_LONG_PRESS_DETECTION, SIZE_SWITCH_ON_OFF_STATE, SIZE_STATE_OF_IC,SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT,SIZE_SWITCH_DETECTION_TIME};
	 			////////////////////////////////////
	 			///////////////////////////////////	 writing data to DataFrom_BUT21[0]
	 		DataFrom_BUT21[0].NumOfRegForReceivedData_BUT21 = NumOfRegReadFromIC;
	 		DataFrom_BUT21[0].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 			DataFrom_BUT21[0].I2CHandlerForBUT21 =phi2c1;
	 			  DataFrom_BUT21[0].SizeOfDataBlockInIC = 1;

	 	for (uint8_t i =0; i<NumOfRegReadFromIC; i++){
	 			DataFrom_BUT21[0].RegisterNameForReceivedData_BUT21 = DataFromIC_BUT21;
	 			DataFrom_BUT21[0].RegistersAddrForReceivedData_BUT21[i] = AddrDataFromIC_BUT21_1[i];
	 			DataFrom_BUT21[0].RegistersSizeForReceivedData_BUT21[i] =  SizeDataFromIC_BUT21_1[i];
	 	}
	 	///////////////////////////////////	writing data to  DataFrom_BUT21[1],DataFrom_BUT21[2].....DataFrom_BUT21[10]
	 	for (uint8_t i =0; i<11; i++)	{
	 		DataFrom_BUT21[i+1].NumOfRegForReceivedData_BUT21 = 1;
	 		DataFrom_BUT21[i+1].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		DataFrom_BUT21[i+1].I2CHandlerForBUT21 =phi2c1;
	 		DataFrom_BUT21[i+1].SizeOfDataBlockInIC = 1;
	 		DataFrom_BUT21[i+1].RegisterNameForReceivedData_BUT21 =&(*(RegToBeReadDepIntFac+i));
	 		DataFrom_BUT21[i+1].RegistersAddrForReceivedData_BUT21[0] = AddrDataFromIC_BUT21_2[i];
	 		DataFrom_BUT21[i+1].RegistersSizeForReceivedData_BUT21[0] =  SizeDataFromIC_BUT21_2[i];
	 	}
	 	//_________________________________________________________________________________________________________________________________________

	 		//REGISTERS for received data from BUT21 RIGHT PANEL
	 		//initialize registers
	 	/*
	 	This creates first element in DataFrom_BUT21, DataFrom_BUT21[0] -> InterruptFactor, SensorControl, DataForSensorFunRead
	 	Tu lahko dodaš še ve�? registrov, ki jih bi želel brati za diagnostiko in testiranje

	 	*/
	 		uint8_t InterruptFactor_R[SIZE_INTERRUPT_FACTOR]={0x00,0x00,0x00};
	 		uint8_t RegSensorControlRead_R[SIZE_SENSOR_CONTROL] = {0x00};  // in this register all switches are set as sensors or HIgh Z or low..
	 		uint8_t RegDataForSensroFunRead_R[SIZE_SENSOR_FUNCTION]={0x00,0x00,0x00,0x00,0x00};// this register must be read to determinate the correctness of configuration

	 	//These registers will each be a separate instance of DataFromBUT21, because not all are needed to be read... depending on the interrupt factor just some have to be read.
	 		uint8_t RegSwitchOnDetection_R[SIZE_SWITCH_ON_DETECTION] = {0x00, 0x00, 0x00};
	 		uint8_t RegSwitchOffDetection_R[SIZE_SWITCH_OFF_DETECTION] = {0x00, 0x00, 0x00};
	 		uint8_t RegSwitchLongPressDetection_R[SIZE_SWITCH_LONG_PRESS_DETECTION] = {0x00, 0x00, 0x00};
	 		uint8_t RegSwitchRepeatedLongPressDetection_R[SIZE_SWITCH_REPEATED_LONG_PRESS_DETECTION] = {0x00, 0x00, 0x00};
	 		uint8_t RegMultiPatternSwitchesOnDetection_R[SIZE_MULTIPLE_PATTERN_SWITCH_ON_DETECTION] = {0x00};
	 		uint8_t RegMultiPatternSwitchesOffDetection_R[SIZE_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION] = {0x00};
	 		uint8_t RegUnexpectedLongPressDetection_R[SIZE_UNEXPECTED_LONG_PRESS_DETECTION] = {0x00, 0x00, 0x00};
	 		uint8_t RegSwitchOnOffState_R[SIZE_SWITCH_ON_OFF_STATE] = {0x00, 0x00, 0x00};
	 		uint8_t RegStateOfIC_R[SIZE_STATE_OF_IC] = {0x00};
	 		uint8_t RegMultiplePatternSwitchesAssignment_R[SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT] = {\
	 		    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
	 		    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
	 		    0x00, 0x00, 0x00, 0x00\
	 		};
	 		uint8_t RegSwitchDetectionTimeRead_R[SIZE_SWITCH_DETECTION_TIME] = {0x00};



	 	////////////////////////////////////PrEPARING DATA FOR  DataFrom_BUT21[0]
	 		// determinate number of registers
	 		//ni potrebe po tej spr, saj je definirana in inicializirana že zgoraj
	 	//	uint8_t NumOfRegReadFromIC=3;
	 		//pointer to arrays where data will be be stored
	 		uint8_t *DataFromIC_BUT21_R[3] = {InterruptFactor_R,RegSensorControlRead_R,RegDataForSensroFunRead_R};
	 	//size of registers and address of registers
	 		//the following two regs can be used from the left panel
	 		//uint16_t AddrDataFromIC_BUT21_1[3] = {ADDR_INTERRUPT_FACTOR,ADDR_SENSOR_CONTROL,ADDR_SENSOR_FUNCTION};
	 		//uint16_t SizeDataFromIC_BUT21_1[3] = {SIZE_INTERRUPT_FACTOR,SIZE_SENSOR_CONTROL,SIZE_SENSOR_FUNCTION};
	 		////////////////////////////////////
	 		////////////////////////////////////PrEPARING DATA FOR  DataFrom_BUT21[1],DataFrom_BUT21[2].....DataFrom_BUT21[10]
	 		uint8_t* RegToBeReadDepIntFac_R[11] = {
	 		    RegSwitchOnDetection_R,\
	 		    RegSwitchOffDetection_R,\
	 		    RegSwitchLongPressDetection_R,\
	 		    RegSwitchRepeatedLongPressDetection_R,\
	 		    RegMultiPatternSwitchesOnDetection_R,\
	 		    RegMultiPatternSwitchesOffDetection_R,\
	 		    RegUnexpectedLongPressDetection_R,\
	 		    RegSwitchOnOffState_R,\
	 		    RegStateOfIC_R,\
	 		    RegMultiplePatternSwitchesAssignment_R,\
	 		    RegSwitchDetectionTimeRead_R\
	 		};
	 			// spidnje dva registra se lahko uporabita od left panel
	 			//uint16_t AddrDataFromIC_BUT21_2[11] = {ADDR_SWITCH_ON_DETECTION,  	ADDR_SWITCH_OFF_DETECTION,		ADDR_SWITCH_LONG_PRESS_DETECTION, ADDR_SWITCH_REPEATED_LONG_PRESS_DETECTION, ADDR_MULTIPLE_PATTERN_SWITCH_ON_DETECTION,ADDR_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION, ADDR_UNEXPECTED_LONG_PRESS_DETECTION, ADDR_SWITCH_ON_OFF_STATE,ADDR_STATE_OF_IC, ADDR_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT,ADDR_SWITCH_DETECTION_TIME};
	 			//uint16_t SizeDataFromIC_BUT21_2[11] ={SIZE_SWITCH_ON_DETECTION, SIZE_SWITCH_OFF_DETECTION, SIZE_SWITCH_LONG_PRESS_DETECTION, SIZE_SWITCH_REPEATED_LONG_PRESS_DETECTION, SIZE_MULTIPLE_PATTERN_SWITCH_ON_DETECTION, SIZE_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION, SIZE_UNEXPECTED_LONG_PRESS_DETECTION, SIZE_SWITCH_ON_OFF_STATE, SIZE_STATE_OF_IC,SIZE_MULTIPLE_PATTERN_SWITCH_ASSIGNMENT,SIZE_SWITCH_DETECTION_TIME};
	 			////////////////////////////////////
	 			///////////////////////////////////	 writing data to DataFrom_BUT21[0]
	 		DataFrom_BUT21_R[0].NumOfRegForReceivedData_BUT21 = NumOfRegReadFromIC;
	 		// naslov je enka za levi in za desni BUT21
	 		DataFrom_BUT21_R[0].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		//uporablja se I2C 3 za desni front panel
	 			DataFrom_BUT21_R[0].I2CHandlerForBUT21 =phi2c3;
	 			  DataFrom_BUT21_R[0].SizeOfDataBlockInIC = 1;

	 	for (uint8_t i =0; i<NumOfRegReadFromIC; i++){
	 			DataFrom_BUT21_R[0].RegisterNameForReceivedData_BUT21 = DataFromIC_BUT21_R;
	 			DataFrom_BUT21_R[0].RegistersAddrForReceivedData_BUT21[i] = AddrDataFromIC_BUT21_1[i];
	 			DataFrom_BUT21_R[0].RegistersSizeForReceivedData_BUT21[i] =  SizeDataFromIC_BUT21_1[i];
	 	}
	 	///////////////////////////////////	writing data to  DataFrom_BUT21[1],DataFrom_BUT21[2].....DataFrom_BUT21[10]
	 	for (uint8_t i =0; i<11; i++)	{
	 		DataFrom_BUT21_R[i+1].NumOfRegForReceivedData_BUT21 = 1;
	 		DataFrom_BUT21_R[i+1].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 		DataFrom_BUT21_R[i+1].I2CHandlerForBUT21 =phi2c3;
	 		DataFrom_BUT21_R[i+1].SizeOfDataBlockInIC = 1;
	 		DataFrom_BUT21_R[i+1].RegisterNameForReceivedData_BUT21 =&(*(RegToBeReadDepIntFac_R+i));
	 		DataFrom_BUT21_R[i+1].RegistersAddrForReceivedData_BUT21[0] = AddrDataFromIC_BUT21_2[i];
	 		DataFrom_BUT21_R[i+1].RegistersSizeForReceivedData_BUT21[0] =  SizeDataFromIC_BUT21_2[i];
	 	}

	 	//_________________________________________________________________________________________________________________________________________
	 	//_________________________________________________________________________________________________________________________________________
	 		//REGISTERS for writing to BUT21 for clearing flags, s pisanjem teh registtov resetiramo specifi�?en flag za vse tipke
	 	// this registers can be used for both left and right front panel
	 	uint8_t RegClearInterruptFactor[SIZE_CLEAR_INTERRUPT_FACTOR] = CLEAR_INTERRUPT_FACTOR;
	 	uint8_t RegClearSwitchOnDetection[SIZE_SWITCH_ON_DETECTION]={0x00,0x00,0x00};
	 	uint8_t RegClearSwitchOffDetection[SIZE_SWITCH_OFF_DETECTION]={0x00,0x00,0x00};
	 	uint8_t RegClearSwitchLongPressDetection[SIZE_SWITCH_LONG_PRESS_DETECTION]={0x00,0x00,0x00};
	 	uint8_t RegClearSwitchRepeatedLongPressDetection[SIZE_SWITCH_REPEATED_LONG_PRESS_DETECTION]={0x00,0x00,0x00};
	 	uint8_t RegClearMultiPatternSwitchesOnDetection[SIZE_MULTIPLE_PATTERN_SWITCH_ON_DETECTION]={0x00};
	 	uint8_t RegClearMultiPatternSwitchesOffDetection[SIZE_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION]={0x00};
	 	uint8_t RegClearUnexpectedLongPressDetection[SIZE_UNEXPECTED_LONG_PRESS_DETECTION]={0x00,0x00,0x00};

	 	uint8_t *DataForClearing[8] = {RegClearInterruptFactor, RegClearSwitchOnDetection, RegClearSwitchOffDetection, RegClearSwitchLongPressDetection, RegClearSwitchRepeatedLongPressDetection, RegClearMultiPatternSwitchesOnDetection, RegClearMultiPatternSwitchesOffDetection, RegClearUnexpectedLongPressDetection};
	 	uint16_t AddrDataForClearingIC_BUT21[8] = {ADDR_CLEAR_INTERRUPT_FACTOR, ADDR_CLEAR_SWITCH_ON_DETECTION, ADDR_CLEAR_SWITCH_OFF_DETECTION, ADDR_CLEAR_SWITCH_LONG_PRESS_DETECTION, ADDR_CLEAR_SWITCH_REPEATED_LONG_PRESS_DETECTION, 		ADDR_CLEAR_MULTIPLE_PATTERN_SWITCHES_ON_DETECTION, ADDR_CLEAR_MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION, ADDR_CLEAR_UNEXPECTED_LONG_PRESS_DETECTION};
	 	uint16_t SizeDataForClearingIC_BUT21[8] = {SIZE_CLEAR_INTERRUPT_FACTOR, SIZE_CLEAR_SWITCH_ON_DETECTION, SIZE_CLEAR_SWITCH_OFF_DETECTION, SIZE_CLEAR_SWITCH_LONG_PRESS_DETECTION, SIZE_CLEAR_SWITCH_REPEATED_LONG_PRESS_DETECTION, 					SIZE_CLEAR_MULTIPLE_PATTERN_SWITCHES_ON_DETECTION, SIZE_CLEAR_MULTIPLE_PATTERN_SWITCHES_OFF_DETECTION, SIZE_CLEAR_UNEXPECTED_LONG_PRESS_DETECTION};

	 	  for (uint8_t i =0; i<8; i++){

	 		  //data for BUT21 left
	 			DataFor_BUT21[1+i].NumOfRegForSendData_BUT21 = 1;
	 			DataFor_BUT21[1+i].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 			DataFor_BUT21[1+i].I2CHandlerForBUT21 =phi2c1;
	 			DataFor_BUT21[1+i].SizeOfDataBlockInIC = 1;
	 			DataFor_BUT21[1+i].RegisterNameForSendData_BUT21[0] = DataForClearing[i];
	 			DataFor_BUT21[1+i].RegistersAddrForSendData_BUT21[0] = AddrDataForClearingIC_BUT21[i];
	 			DataFor_BUT21[1+i].RegistersSizeForSendData_BUT21[0] =  SizeDataForClearingIC_BUT21[i];
	 			//data for BUT21 right
	 			DataFor_BUT21_R[1+i].NumOfRegForSendData_BUT21 = 1;
	 			DataFor_BUT21_R[1+i].Addr_I2C_BUT21 = AddrBUT21_I2C ;
	 			DataFor_BUT21_R[1+i].I2CHandlerForBUT21 =phi2c3;
	 			DataFor_BUT21_R[1+i].SizeOfDataBlockInIC = 1;
	 			DataFor_BUT21_R[1+i].RegisterNameForSendData_BUT21[0] = DataForClearing[i];
	 			DataFor_BUT21_R[1+i].RegistersAddrForSendData_BUT21[0] = AddrDataForClearingIC_BUT21[i];
	 			DataFor_BUT21_R[1+i].RegistersSizeForSendData_BUT21[0] =  SizeDataForClearingIC_BUT21[i];


	 	  }




	 	  /* tablea za lažje dostopanje do registrov znotraj DataFor_BUT21
	 	 1-2 SIZE_CLEAR_INTERRUPT_FACTOR
	 	2-3 SIZE_CLEAR_SWITCH_ON_DETECTION
	 	3-4 SIZE_CLEAR_SWITCH_OFF_DETECTION
	 	4-5 SIZE_CLEAR_SWITCH_LONG_PRESS_DETECTION
	 	5-6 SIZE_CLEAR_SWITCH_REPEATED_LONG_PRESS_DETECTION
	 	6-7 SIZE_CLEAR_MULTIPLE_PATTERN_SWITCH_ON_DETECTION
	 	7-8 SIZE_CLEAR_MULTIPLE_PATTERN_SWITCH_OFF_DETECTION
	 	8-9 SIZE_CLEAR_UNEXPECTED_LONG_PRESS_DETECTION
	 	   *
	 	   */

	 	  /* tablea za lažje dostopanje do registrov znotraj DataFrom_BUT21
	 	0-1 RegInterruptFactor,RegSensorControlRead,RegDataForSensroFunRead
	 	1-2 RegSwitchOnDetection,
	 	2-3 RegSwitchOffDetection,
	 	3-4 RegSwitchLongPressDetection,
	 	4-5 RegSwitchRepeatedLongPressDetection,
	 	5-6 RegMultiPatternSwitchesOnDetection,
	 	6-7 RegMultiPatternSwitchesOffDetection,
	 	7-8 RegUnexpectedLongPressDetection,
	 	8-9 RegSwitchOnOffState,
	 	9-10 RegStateOfIC

	 	     *
	 	     */

	 	  //_________________________________________________________________________________________________________________________________________
	 	  //__________________________________________________________INIT IS32 LEFT PANEL_______________________________________________________________________________
	 	  //_________________________________________________________________________________________________________________________________________
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

	 		 //_________________________________________________________________________________________________________________________________________
	 		  //__________________________________________________________INIT IS32 RIGHT PANEL_______________________________________________________________________________
	 		  //_________________________________________________________________________________________________________________________________________
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

	 			/*
	 			 * celoten spodnji blok uporabimo od left panel, saj se ne spremeni za right panel
	 			 */
	 			//uint8_t NumOfRegForSendData_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING] = NUM_OF_REG_REGISTER_COUNTS;
	 		// uporabimo od left panel
	 			//uint16_t AddrOfRegForSendData_IS32[NUM_OF_IS32_STRUCT_FOR_SENDING][5] =ADDR_OF_ALL_REG_FOR_IS32 ;
	 			//uint8_t AllRegForIS32[NUM_OF_IS32_STRUCT_FOR_SENDING][5] = ALL_REGISTERS_FOR_IS32;
	 			//uint8_t DataForIS32_Reg_0[1]={0x01};	//1 register
	 			// uint8_t DataForIS32_Reg_1[1]={UPDATE_REGISTER};	//1 register
	 			//uint8_t DataForIS32_Reg_2[1]={RESET_REGISTER};//1 register

	 		/*
	 		 * spodnji registri imajo enako vrednost kot za left panel
	 		 */
	 			uint8_t LedControlRegAll_R[3] = LED_CONTROL_REGISTER_ALL;
	 			uint8_t PwmControlReg1_5_R[5]=PWM_CHANNELS_1_TO_5_VALUES;
	 			uint8_t PwmControlReg6_10_R[5]=PWM_CHANNELS_6_TO_10_VALUES;
	 			uint8_t PwmControlReg11_15_R[5]=PWM_CHANNELS_11_TO_15_VALUES;
	 			uint8_t PwmControlReg16_18_R[3]=PWM_CHANNELS_16_TO_18_VALUES;

	 			uint8_t *pLedControlRegAll_R[3] = {&(LedControlRegAll_R[0]), &(LedControlRegAll_R[1]), &(LedControlRegAll_R[2])};
	 			uint8_t *pPwmControlReg1_5_R[5] = {
	 			    &(PwmControlReg1_5_R[0]),
	 			    &(PwmControlReg1_5_R[1]),
	 			    &(PwmControlReg1_5_R[2]),
	 			    &(PwmControlReg1_5_R[3]),
	 			    &(PwmControlReg1_5_R[4]),
	 			};
	 			uint8_t *pPwmControlReg6_10_R[5] = {
	 			    &(PwmControlReg6_10_R[0]),
	 			    &(PwmControlReg6_10_R[1]),
	 			    &(PwmControlReg6_10_R[2]),
	 			    &(PwmControlReg6_10_R[3]),
	 			    &(PwmControlReg6_10_R[4]),
	 			};
	 			uint8_t *pPwmControlReg11_15_R[5] = {
	 			    &(PwmControlReg11_15_R[0]),
	 			    &(PwmControlReg11_15_R[1]),
	 			    &(PwmControlReg11_15_R[2]),
	 			    &(PwmControlReg11_15_R[3]),
	 			    &(PwmControlReg11_15_R[4]),
	 			};
	 			uint8_t *pPwmControlReg16_18_R[3] = {
	 			    &(PwmControlReg16_18_R[0]),
	 			    &(PwmControlReg16_18_R[1]),
	 			    &(PwmControlReg16_18_R[2])
	 			};

	 			// to je zbirka kazalcev na zgornje arraye, v zgornjih zbirkah imamo nekje 1, nekje 3 in nekje 5 registrov pod istim kazalcem
	 			uint8_t *DataForIS32_Type1_R[3] = {DataForIS32_Reg_0, DataForIS32_Reg_1, DataForIS32_Reg_2};

	 			uint8_t **DataForIS32_Type2_R[5] = {pLedControlRegAll_R, pPwmControlReg1_5_R, pPwmControlReg6_10_R, pPwmControlReg11_15_R, pPwmControlReg16_18_R};

	 			// IndexCorrection
	 			 a=0;

	 			for(uint8_t i=0;i<NUM_OF_IS32_STRUCT_FOR_SENDING;i++ ){

	 				DataFor_IS32_R[i].Addr_I2C_BUT21 = I2C_ADDR_IS31FL3218;
	 				DataFor_IS32_R[i].I2CHandlerForBUT21 = phi2c3;
	 				DataFor_IS32_R[i].SizeOfDataBlockInIC = SIZE_OF_REG_IN_LED_DRIVER;
	 				DataFor_IS32_R[i].NumOfRegForSendData_BUT21 =NumOfRegForSendData_IS32[i];
	 				for (uint8_t j=0;j<NumOfRegForSendData_IS32[i];j++ ){
	 				DataFor_IS32_R[i].RegistersAddrForSendData_BUT21[j] =AddrOfRegForSendData_IS32[i][j];
	 				DataFor_IS32_R[i].RegistersSizeForSendData_BUT21[j] = 1;
	 				if(i<3){
	 			DataFor_IS32_R[i].RegisterNameForSendData_BUT21[j]=DataForIS32_Type1_R[i];
	 				}else if (i>=3) {
	 					a=i-3;
	 					DataFor_IS32_R[i].RegisterNameForSendData_BUT21[j]=*(DataForIS32_Type2_R[a]+j);
	 				}
	 				}
	 			}
	 		 //_________________________________________________________________________________________________________________________________________
	 		  //_________________________________________________________________________________________________________________________________________
	 		  //_________________________________________________________________________________________________________________________________________

	 	//TFT LCD variables setup
	#include "TFT_LCD_CHAR_POINTS.c"
  	 	 //uint8_t WindowSizePosition4[2][2]={{BLOCK_4_START_X,BLOCK_4_START_Y},{BLOCK_4_STOP_X,BLOCK_4_STOP_Y}};
  	 	 //uint8_t WindowSizePosition5[2][2]={{BLOCK_5_START_X,BLOCK_5_START_Y},{BLOCK_5_STOP_X,BLOCK_5_STOP_Y}};
  	 	 //uint8_t WindowSizePosition6[2][2]={{BLOCK_6_START_X,BLOCK_6_START_Y},{BLOCK_6_STOP_X,BLOCK_6_STOP_Y}};

  	 	uint8_t WindowSizePositions[3][2][2] = {
  	 	    {{BLOCK_6_START_X, BLOCK_6_START_Y}, {BLOCK_6_STOP_X, BLOCK_6_STOP_Y}},
  	 	    {{BLOCK_5_START_X, BLOCK_5_START_Y}, {BLOCK_5_STOP_X, BLOCK_5_STOP_Y}},
  	 	    {{BLOCK_4_START_X, BLOCK_4_START_Y}, {BLOCK_4_STOP_X, BLOCK_4_STOP_Y}}
  	 	};

  	 	 uint16_t Colors[2] = {ST7735_RED,ST7735_BLACK};
  	 	uint8_t NumOfLines[]=NUM_OF_LINES_ARRAY;
  	 	  	//uint8_t Ret;



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM11_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_TIM10_Init();
  MX_TIM12_Init();
  MX_TIM13_Init();
  /* USER CODE BEGIN 2 */

  /*
  	 	  *   //_________________________________________________________________________________________________________________________________________
  	 	  *     //_________________________________________________________________________________________________________________________________________
  	 	 * init tft LCD  screen
  	 	 */

  	 	 ST7735S_Init();
  	 	ST7735S_SetScreenColor( ST7735_WHITE);
  	 	ST7735S_WriteCommand(0x29); // display on
/* this is how we can display one number
  	   Ret=ST7735_DrawLetterOrNumber(Frame4Points[9], NumOfLines[9],&WindowSizePositions[2] , Colors);
  	   if(Ret==1){
  		   while(1);

  		   with this function we can delete the number from the screen
  		   ST7735_DeleteLetterOrNumber( uint8_t (* pWindowSizePosition)[2][2], uint16_t * Colors){
  	   }
*/

 /*
 * END init tft LCD  screen
  *   //_________________________________________________________________________________________________________________________________________
  *     //_________________________________________________________________________________________________________________________________________
 */



  // Set GPIOD pin 6 high -> BUT21_left_board  not in reset state
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    // Set GPIOA pin 14 high -> BUT21_right_board  not in reset state
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);


    //set PC7 to high, to enable IS32_left
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    //set PA14 to high, to enable IS32_right
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);

    //write data to IS32_left
    WriteDataI2C_Wrapper(DataFor_IS32, 2, 3);//reset
    //WriteDataI2C_Wrapper(DataFor_IS32, 2, 3);
    WriteDataI2C_Wrapper(DataFor_IS32, 0, 1); //out of sleep mode
    //WriteDataI2C_Wrapper(DataFor_IS32, 0, 1);
    WriteDataI2C_Wrapper(DataFor_IS32, 3, 8);//write all PWMs and LED controll
    WriteDataI2C_Wrapper(DataFor_IS32, 1, 2);//update registers

    //write data to IS32_right-
    WriteDataI2C_Wrapper(DataFor_IS32_R, 2, 3);//reset
      //WriteDataI2C_Wrapper(DataFor_IS32, 2, 3);
      WriteDataI2C_Wrapper(DataFor_IS32_R, 0, 1); //out of sleep mode
      //WriteDataI2C_Wrapper(DataFor_IS32, 0, 1);
      WriteDataI2C_Wrapper(DataFor_IS32_R, 3, 8);//write all PWMs and LED controll
      WriteDataI2C_Wrapper(DataFor_IS32_R, 1, 2);//update registers





    //write multipattern assigments to BUT21, and switch on detection time for BUT21_left
    WriteDataI2C_Wrapper(DataFor_BUT21, 13, 14);
    //write Switch data to BUT21_left
    WriteDataI2C_Wrapper(DataFor_BUT21, 0, 1);
    //write multipattern assigments to BUT21, and switch on detection time for BUT21_right
    WriteDataI2C_Wrapper(DataFor_BUT21_R, 13, 14);
    //write Switch data to BUT21_RIGHT
      WriteDataI2C_Wrapper(DataFor_BUT21_R, 0, 1);


      // flag for timer accent timer start
      uint8_t AccentTimerStartFlag=0;

      // set ENABLE ACCENT
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(KickDrumState == 0){ // kick drum is in programming mode

		  if (BUT21CallBack_R == 1 ){ // right panel interrupt
				  ReceiveDataI2C_Wrapper(DataFrom_BUT21_R, 0, 1);
				  // 0 - left panel
				  // 1 - right panel
				  ParseDataFromInterruptFactor(Sliders,DataFrom_BUT21_R,Tipke,DataFor_BUT21_R,2);
				  BUT21CallBack_R = 0;
			  }

			  if (BUT21CallBack == 1 ){// left panel interrupt

				   ReceiveDataI2C_Wrapper(DataFrom_BUT21, 0, 1);

				  ParseDataFromInterruptFactor(Sliders,DataFrom_BUT21,Tipke,DataFor_BUT21,1);

				  //flag for processor to work on CAPsen data
				  BUT21CallBack = 0;


			  }
			  // calculating Slider increase/decrease from Tipke structure for all 3 sliders,
			  //write slider data to LCD
			 ChangeIndexVal_ret = ChangeIndexVal(Sliders,WindowSizePositions,Colors,AllFrames,NumOfLines );
			 if (ChangeIndexVal_ret != 0){
				  while(1);
			  }



			 // funkcija za prepisovanje podatkov iz sliderja v generic info  structure
			 CopyDataFromSliderToGenericInfoStruct(Tipke,Sliders,pGenericInfo);
			 // funkcija za prepisovanje podatkov iz sliderjev in Tipk v Instruments strukture
			 CopyDataFromSliderToInstrument(Instruments,Tipke,Sliders,InstrumentIndix);
			 //funkcija za določanje kateri inštruemnt se mora špilat na kateri tipki
			 //MapButtonStepsToInstruments(Buttons_varA,Instruments,Tipke,Sliders,InstrumentIndix,NumberButtonIndex);
			 MapButtonStepsToInstrumentsAndCheckVar(Buttons_varA,Buttons_varB,Instruments,Tipke,Sliders,InstrumentIndix,NumberButtonIndex);
			 // turn on/off LEDs from Tipke structure, Timer is used for LED blinking
			 CheckStructTipke(DataFor_IS32, Tipke,ArrayOfTimerPointers1,0); //LEFT PANEL
			 CheckStructTipke(DataFor_IS32_R, Tipke,ArrayOfTimerPointers1,1); //right PANEL

			 //CHECK start/stop button for state
			 if(Tipke[6].LEDOnOff == 1 ){
				 KickDrumState =1;
			 }


	  } else if (KickDrumState == 1) { // kick drum is in sequencer mode

		  if (BUT21CallBack == 1 ){// left panel interrupt
			   ReceiveDataI2C_Wrapper(DataFrom_BUT21, 0, 1);
			  ParseDataFromInterruptFactor(Sliders,DataFrom_BUT21,Tipke,DataFor_BUT21,1);
			  //flag for processor to work on CAPsen data
			  BUT21CallBack = 0;
		  }
		  //CheckStructTipke(DataFor_IS32, Tipke,ArrayOfTimerPointers,0); //LEFT PANEL

		  if( AccentTimerStartFlag == 0){
			  //convert instrument data to data that can be passed to timers-> this has to be done ony once
			  ConvertInstrumentDataToTimers(Instruments);
			  //set and start timers that define VCR
			  SetAndStartTimers(Instruments,ArrayOfTimerChannels,ArrayOfTimerPointers2);
			  //start ACCENT level timer
			  HAL_TIM_PWM_Start(		&htim3,//&htim3
			  							TIM_CHANNEL_1);//channel 1

			  //convert instrument data to data that can be passed to timers-> this has to be done ony once
			  //ConvertInstrumentDataToTimers(Instruments);
			  //start ACCENT timer
			  StartAccentTimer(ArrayOfTimerPointers1, 15,  ConvertBPM_ToTimerTicks(pGenericInfo->Tempo));
			  // 3-> 1ms
			  //15-> 5ms
			  //StartAccentTimer(ArrayOfTimerPointers, 3,  (uint16_t)ConvertBPM_ToTimerTicks(200));
			  AccentTimerStartFlag =1;
		  }

		  //check global variable CurrentNumberInSeqState and turn on that LED
		  TurnOnSequencer(Tipke,
					  	  NumberButtonIndex,
						  Buttons_varA,
						  Buttons_varB,
						  ArrayOfTimerChannels,
						  ArrayOfTimerPointers2,
						  InstrumentEnablePin,
						  GPIO_INSTRUMENT_ENABLE,
						  Instruments);


		  // turn on/off LEDs from Tipke structure, Timer is used for LED blinking
		  CheckStructTipkeSequencerMode(DataFor_IS32, Tipke,0); //LEFT PANEL
		  CheckStructTipkeSequencerMode(DataFor_IS32_R, Tipke,1); //right PANE
		 //CheckStructTipke(DataFor_IS32, Tipke,ArrayOfTimerPointers,0); //LEFT PANEL
		 //CheckStructTipke(DataFor_IS32_R, Tipke,ArrayOfTimerPointers,1); //right PANE

		  //CHECK start/stop button for state
		 if(Tipke[6].LEDOnOff == 0 ){
			 // return back to programming state
			 KickDrumState =0;
			 //stop ACCENT timer
			 StopAccentTimer(ArrayOfTimerPointers1);
			 AccentTimerStartFlag =0;
			 CurrentNumberInSeqState = 1;
			 TurnOFFAllNumberLED(Tipke, NumberButtonIndex);
			 // turn on/off LEDs from Tipke structure, when machine is going to sequencer mode all number leds must turn off
			  CheckStructTipkeSequencerMode(DataFor_IS32, Tipke,0); //LEFT PANEL
			  CheckStructTipkeSequencerMode(DataFor_IS32_R, Tipke,1); //right PANE
		 }
	  }else {
		  while(1);
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 32;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 256;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 16;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 256;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 16;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 256;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 16;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 256;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
  HAL_TIM_MspPostInit(&htim5);

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 56000;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 9000;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM2;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 422;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 65535;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 0;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 65535;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 16;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 256;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim12, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */
  HAL_TIM_MspPostInit(&htim12);

}

/**
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 16;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 256;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim13, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */

  /* USER CODE END TIM13_Init 2 */
  HAL_TIM_MspPostInit(&htim13);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, CymbalEnable_Pin|CowbellEnable_Pin|TomEnable_Pin|Touch_RESET2_Pin
                          |TFTScreen_RS_Pin|TFTScreen_Reset_Pin|LedDriver_SDB2_Pin|LedDriver_SDB1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BassDrumEnable_GPIO_Port, BassDrumEnable_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ClavesEnable_Pin|RimShotEnable_Pin|CongaEnable_Pin|SnareDrumEnable_Pin
                          |Accent_DEFAULT_Pin|Touch_RESET1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CymbalEnable_Pin CowbellEnable_Pin TomEnable_Pin Touch_RESET2_Pin
                           TFTScreen_RS_Pin TFTScreen_Reset_Pin LedDriver_SDB2_Pin LedDriver_SDB1_Pin */
  GPIO_InitStruct.Pin = CymbalEnable_Pin|CowbellEnable_Pin|TomEnable_Pin|Touch_RESET2_Pin
                          |TFTScreen_RS_Pin|TFTScreen_Reset_Pin|LedDriver_SDB2_Pin|LedDriver_SDB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : BassDrumEnable_Pin */
  GPIO_InitStruct.Pin = BassDrumEnable_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BassDrumEnable_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ClavesEnable_Pin RimShotEnable_Pin CongaEnable_Pin SnareDrumEnable_Pin
                           Accent_DEFAULT_Pin Touch_RESET1_Pin */
  GPIO_InitStruct.Pin = ClavesEnable_Pin|RimShotEnable_Pin|CongaEnable_Pin|SnareDrumEnable_Pin
                          |Accent_DEFAULT_Pin|Touch_RESET1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : INTB1_Pin INTB2_Pin */
  GPIO_InitStruct.Pin = INTB1_Pin|INTB2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin ){

	if (GPIO_Pin ==INTB2_Pin ) {
		BUT21CallBack_R = 1; // right panel interrupt
	}
if (GPIO_Pin ==INTB1_Pin ){
	BUT21CallBack = 1; // left panel interrupt
}


}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM10){
		if (gVarBlinky ==2){
			gVarBlinky =1;
		} else if (gVarBlinky == 1) {
			gVarBlinky = 0;
		}else if (gVarBlinky ==0){
			gVarBlinky = 1;
		}
	}

	}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance==TIM8){
			CurrentNumberInSeqState++;
			if(CurrentNumberInSeqState > 16){
				CurrentNumberInSeqState=1;
			}
		}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
