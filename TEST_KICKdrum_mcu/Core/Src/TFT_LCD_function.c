/*
 * TFT_LCD_function.c
 *
 *  Created on: 26 Feb 2025
 *      Author: Klemen
 */

/*
 * TFT_functions.c
 *
 *  Created on: Dec 27, 2024
 *      Author: Klemen
 */

#include "TFT_LCD_function.h"


void ST7735S_WriteData(uint8_t Data) {
	HAL_StatusTypeDef ret;
	//set chip select to low -> enabling the tft
		//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
	// set pin D/CX high -> write data
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
    ret = HAL_SPI_Transmit(&hspi1, &Data, 1, 20);  // Send via SPI
    //set chip select tohigh-> disabling the tft
   // HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
    if(ret != HAL_OK){
        	while(1);
        }
}

void ST7735S_WriteCommand(uint8_t Data) {
	HAL_StatusTypeDef ret;
	//set chip select to low -> enabling the tft
	//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
	// set pin D/CX low -> write command
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    ret = HAL_SPI_Transmit(&hspi1, &Data, 1,20);  // Send via SPI
    //set chip select tohigh-> disabling the tft
       // HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
    if(ret != HAL_OK){
    	while(1);
    }
}

void ST7735S_SetScreenColor( uint16_t Color){
	uint8_t data[2];

	ST7735S_WriteCommand(0x2a);			//  2: Row addr set
	ST7735S_WriteData(0x00);							//     YSTART = 0
	ST7735S_WriteData(OFFSET_X);
	ST7735S_WriteData(0x00);							//     YEND = 79
	ST7735S_WriteData(ST7735_WIDTH+OFFSET_X);

	ST7735S_WriteCommand(0x2b);			//  2: Row addr set
	ST7735S_WriteData(0x00);							//     YSTART = 0
	ST7735S_WriteData(OFFSET_Y);
	ST7735S_WriteData(0x00);							//     YEND =159
	ST7735S_WriteData(ST7735_HEIGHT+OFFSET_X);

	ST7735S_WriteCommand(0x2c); // start writing to RAM


	data [1]= (uint8_t )(Color &0xFF);
	data [0]= (uint8_t ) (Color >> 8);

	for (uint16_t i = 0; i< NUM_OF_PIX ;i++){
		ST7735S_WriteData(data[0]);
		ST7735S_WriteData(data[1]);
	}
}

void ST7735S_Init(){
	  HAL_Delay(500);
	  ST7735S_HW_RESET();
	  //HAL_Delay(500);
	  //set chip select to low -> enabling the tft...LCD chip select is always set to low, soldered to GND
		//HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_Delay(500);
	  ST7735S_WriteCommand(0x01); // sw RESET
	  HAL_Delay(500);
	  ST7735S_WriteCommand(0x11); // out of sleep mode
	  HAL_Delay(500);
	  ST7735S_WriteCommand(0x3A); //colormode command
	  ST7735S_WriteData(0x05); // 16 BIT COLOR MODE
	   ST7735S_WriteCommand(0x13); // partial mode off
	   ST7735S_WriteCommand(0x21);// RGB inversion on
}


void ST7735S_HW_RESET(){

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);

}



uint8_t ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t Color) {
	/*
	 * check if data  is out of display range
	 */
	if((x >= (ST7735_WIDTH+OFFSET_X) ) || (y >= (ST7735_HEIGHT+OFFSET_Y))){
		return 1;
	}
	if((x <0 ) || (y < 0)){
		return 1;
	}
	uint8_t data[2];
	uint8_t Coordiantes[4];
	Coordiantes[0]=x + OFFSET_X;
	Coordiantes[1]=y+OFFSET_Y;
	Coordiantes[2]=x + OFFSET_X +1;
	Coordiantes[3]=y+OFFSET_Y+1;

	ST7735_SetAddressWindow(Coordiantes[0], Coordiantes[1], Coordiantes[2], Coordiantes[3]);

	data [1]= (uint8_t )(Color &0xFF);
	data [0]= (uint8_t ) (Color >> 8);

	ST7735S_WriteData(data[0]);
	ST7735S_WriteData(data[1]);
	return 0;
}

uint8_t ST7735_DrawLine(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1, uint16_t LineColor, uint16_t BackColor) {
	/*
	 * check if data  is out of display range
	 */
	if((x0 >= (ST7735_WIDTH+OFFSET_X) ) || (y0 >= (ST7735_HEIGHT+OFFSET_Y))){
		return 1;
	}
	if((x0 <0 ) || (y0 < 0)){
		return 1;
	}

	if((x1 >= (ST7735_WIDTH+OFFSET_X) ) || (y1 >= (ST7735_HEIGHT+OFFSET_Y))){
			return 1;
		}
		if((x1 <0 ) || (y1 < 0)){
			return 1;
		}

	// array for storing data to be send to RAM
	uint8_t Colordata [4];
	// array for storing coordinates with offset
	uint8_t Coordinates[4];
	// counter for rectangle array
	uint16_t z=0;
	// variables for linear function
	float k,n,y;
	// determinate difference between points
	uint8_t dx = abs(x0-x1);
	uint8_t dy = abs(y0-y1);
	//calculate number of pixels in the rectangle, that given points create
	uint16_t NumOfPixForRec = dx*dy;
	// number of pixsels to display line
	uint8_t NumOfPixForLine=dx;

	// from given points and offests of the sreen calculate coordiantes
	Coordinates[0]=x0 + OFFSET_X;
	Coordinates[1]=y0+OFFSET_Y;
	Coordinates[2]=x1 + OFFSET_X ;
	Coordinates[3]=y1+OFFSET_Y;

	if ((dx ==0)&&(dy ==0)){ // check if points are overlaping
		return 1;
	}else if(dy ==0){// check if line is vertical
		NumOfPixForRec = dx;
	} else if (dx ==0){ // check if line is horizontal
		NumOfPixForRec = dy;
		NumOfPixForLine =dy;
	}else{// if line in not horizontal or vertical
		//calculate linear function parameters
		k = CalcLinFunCoef ( Coordinates);
		n = CalcStartVal (k, Coordinates);
	}
	// data of the whole rectangle that is determinated by start and end dots of the line,
	// in TFT RAM eack pixel is presented by 16 bits-> each pixel is represented by 2 bytes
	uint8_t DataArrRec [NumOfPixForRec][2];
	//storage for all xy combinations, that represent the line
	uint8_t DataArr [NumOfPixForLine][2];
	// variable for determinating where given points are to each other
	uint8_t PosPointOneVsPonintTwoFlag=0;
	// variables to store coordiantes of first point of the line to be displayed
	uint8_t CounterIndexX=0;
	uint8_t CounterIndexY=0;
	//determinate how are two points positioned one to the other
	PosPointOneVsPonintTwoFlag = PosPointOneVsPonintTwo(Coordinates);
	//set line color
	Colordata [1]= (uint8_t )(LineColor &0xFF);
	Colordata [0]= (uint8_t ) (LineColor >> 8);
	//set line backround color
	Colordata [3]= (uint8_t )(BackColor &0xFF);
	Colordata [2]= (uint8_t ) (BackColor >> 8);

	// select first X coordiante of the line to be displayed and store it in  CounterIndexX
	if ((PosPointOneVsPonintTwoFlag  >=  1 ) && (PosPointOneVsPonintTwoFlag<=3)){
	 CounterIndexX = Coordinates[2];
	}else if ((PosPointOneVsPonintTwoFlag  >=  4 ) && (PosPointOneVsPonintTwoFlag<=6)){
	 CounterIndexX = Coordinates[0];
	} else if ((PosPointOneVsPonintTwoFlag  >=  7 ) && (PosPointOneVsPonintTwoFlag<=9)){
		CounterIndexX = Coordinates[0];
	}else{
		return 1;
	}
	// select first Y coordiante of the line to be displayed and store it in  CounterIndexY
	if ((PosPointOneVsPonintTwoFlag  ==  1 ) || (PosPointOneVsPonintTwoFlag==4)|| (PosPointOneVsPonintTwoFlag==7)){
	 CounterIndexY = Coordinates[3];
	}else if ((PosPointOneVsPonintTwoFlag  ==  2 ) || (PosPointOneVsPonintTwoFlag==5)|| (PosPointOneVsPonintTwoFlag==8)){
	 CounterIndexY = Coordinates[1];
	} else if ((PosPointOneVsPonintTwoFlag  ==  3 ) || (PosPointOneVsPonintTwoFlag==6)|| (PosPointOneVsPonintTwoFlag==9)){
		CounterIndexY = Coordinates[1];
	}else{
		return 1;
	}

	// selection for y coordiantes of line
	// if the line is horizontal or vertical, there is no need to calulate lin function
	if (dx !=0 && dy != 0){
		// this for loop goest trough all pixels in the rectange, that was determinated by two points
		for(uint8_t i=CounterIndexX;i<(NumOfPixForLine+CounterIndexX);i++){
			  //for eack pixel the for loop checks if this point belongs to the line
			y = k*(float)i+n;
			// save xy coordinates to DataArr
			DataArr[i-CounterIndexX][0] = i;
			DataArr[i-CounterIndexX][1] = y;
		}
	}

	// writing all data to an array to be send to RAM
	if (dx !=0 && dy != 0){// line is diaognal
		for (uint8_t j = CounterIndexY; j<(dy+CounterIndexY); j++ ){
			for (uint8_t i=CounterIndexX;i<(dx+CounterIndexX);i++){
				for (uint8_t m = 0; m<NumOfPixForLine; m++ ){
					if ((DataArr[m][0] == i )&&(DataArr[m][1] == j)){
						//set pixel z as one of line pixels, line colors
						DataArrRec[z][0] =Colordata [0];
						DataArrRec[z][1] =Colordata [1];
						break;
					}else{
						//set pixel z as background pixel
						DataArrRec[z][0] =Colordata [2];
						DataArrRec[z][1] =Colordata [3];
					}
				}
				// increase index z
				z++;
			}
		}

	}else if( (dx==0 )||(dy==0)){ // line is horizontal or vertical
		for (uint8_t m = 0; m<NumOfPixForLine; m++ ){
			DataArrRec[m][0] =Colordata [0];
			DataArrRec[m][1] =Colordata [1];
		}
	}else{
		return 1;
	}

// depending on points position one of the 3 AddressWindows is set
if (dx !=0 && dy != 0){
	ST7735_SetAddressWindow(CounterIndexX, CounterIndexY,CounterIndexX+dx-1, CounterIndexY+dy);
}else if (dx==0 ){
	ST7735_SetAddressWindow(CounterIndexX, CounterIndexY,CounterIndexX, CounterIndexY+dy);
} else if (dy==0 ){
	ST7735_SetAddressWindow(CounterIndexX, CounterIndexY,CounterIndexX+dx, CounterIndexY);
}else{
	return 1;
}
// write data to RAM
	for (uint16_t i = 0; i<NumOfPixForRec;i++){
		// spodnje zaporednje doo
		ST7735S_WriteData(DataArrRec[i][0]);
		ST7735S_WriteData(DataArrRec[i][1]);
	}

	return 0;
}

uint8_t ST7735_DrawThickLine(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1, uint16_t LineColor, uint16_t BackColor,uint8_t Thikness) {
	/*
	 * check if data  is out of display range
	 */
	if((x0 >= (ST7735_WIDTH+OFFSET_X) ) || (y0 >= (ST7735_HEIGHT+OFFSET_Y))){
		return 1;
	}
	if((x0 <0 ) || (y0 < 0)){
		return 1;
	}

	if((x1 >= (ST7735_WIDTH+OFFSET_X) ) || (y1 >= (ST7735_HEIGHT+OFFSET_Y))){
			return 1;
		}
		if((x1 <0 ) || (y1 < 0)){
			return 1;
		}

	// array for storing data to be send to RAM
	uint8_t Colordata [4];
	// array for storing coordinates with offset
	uint8_t Coordinates[4];
	// counter for rectangle array
	uint16_t z=0;
	// variables for linear function
	float k,n,y;
	// determinate difference between points
	uint8_t dx = abs(x0-x1);
	uint8_t dy = abs(y0-y1);
	//calculate number of pixels in the rectangle, that given points create
	uint16_t NumOfPixForRec = dx*dy;
	// number of pixsels to display line
	uint8_t NumOfPixForLine=dx;

	// from given points and offests of the sreen calculate coordiantes
	Coordinates[0]=x0 + OFFSET_X;
	Coordinates[1]=y0+OFFSET_Y;
	Coordinates[2]=x1 + OFFSET_X ;
	Coordinates[3]=y1+OFFSET_Y;

	if ((dx ==0)&&(dy ==0)){ // check if points are overlaping
		return 1;
	}else if(dy ==0){// check if line is vertical
		NumOfPixForRec = dx*(2*Thikness+1);
	} else if (dx ==0){ // check if line is horizontal
		NumOfPixForRec = dy*(2*Thikness+1);
		NumOfPixForLine =dy*(2*Thikness+1);
	}else{// if line in not horizontal or vertical
		//calculate linear function parameters
		k = CalcLinFunCoef ( Coordinates);
		n = CalcStartVal (k, Coordinates);
	}
	// data of the whole rectangle that is determinated by start and end dots of the line,
	// in TFT RAM eack pixel is presented by 16 bits-> each pixel is represented by 2 bytes
	uint8_t DataArrRec [NumOfPixForRec][2];
	//storage for all xy combinations, that represent the line
	uint8_t DataArr [NumOfPixForLine][2];
	// variable for determinating where given points are to each other
	uint8_t PosPointOneVsPonintTwoFlag=0;
	// variables to store coordiantes of first point of the line to be displayed
	uint8_t CounterIndexX=0;
	uint8_t CounterIndexY=0;
	//determinate how are two points positioned one to the other
	PosPointOneVsPonintTwoFlag = PosPointOneVsPonintTwo(Coordinates);
	//set line color
	Colordata [1]= (uint8_t )(LineColor &0xFF);
	Colordata [0]= (uint8_t ) (LineColor >> 8);
	//set line backround color
	Colordata [3]= (uint8_t )(BackColor &0xFF);
	Colordata [2]= (uint8_t ) (BackColor >> 8);

	// select first X coordiante of the line to be displayed and store it in  CounterIndexX
	if ((PosPointOneVsPonintTwoFlag  >=  1 ) && (PosPointOneVsPonintTwoFlag<=3)){
	 CounterIndexX = Coordinates[2];
	}else if ((PosPointOneVsPonintTwoFlag  >=  4 ) && (PosPointOneVsPonintTwoFlag<=6)){
	 CounterIndexX = Coordinates[0];
	} else if ((PosPointOneVsPonintTwoFlag  >=  7 ) && (PosPointOneVsPonintTwoFlag<=9)){
		CounterIndexX = Coordinates[0];
	}else{
		return 1;
	}
	// select first Y coordiante of the line to be displayed and store it in  CounterIndexY
	if ((PosPointOneVsPonintTwoFlag  ==  1 ) || (PosPointOneVsPonintTwoFlag==4)|| (PosPointOneVsPonintTwoFlag==7)){
	 CounterIndexY = Coordinates[3];
	}else if ((PosPointOneVsPonintTwoFlag  ==  2 ) || (PosPointOneVsPonintTwoFlag==5)|| (PosPointOneVsPonintTwoFlag==8)){
	 CounterIndexY = Coordinates[1];
	} else if ((PosPointOneVsPonintTwoFlag  ==  3 ) || (PosPointOneVsPonintTwoFlag==6)|| (PosPointOneVsPonintTwoFlag==9)){
		CounterIndexY = Coordinates[1];
	}else{
		return 1;
	}

	// selection for y coordiantes of line
	// if the line is horizontal or vertical, there is no need to calulate lin function
	if (dx !=0 && dy != 0){
		// this for loop goest trough all pixels in the rectange, that was determinated by two points
		for(uint8_t i=CounterIndexX;i<(NumOfPixForLine+CounterIndexX);i++){
			  //for eack pixel the for loop checks if this point belongs to the line
			y = k*(float)i+n;
			// save xy coordinates to DataArr
			DataArr[i-CounterIndexX][0] = i;
			DataArr[i-CounterIndexX][1] = y;
		}
	}
	// writing all data to an array to be send to RAM
	if (dx !=0 && dy != 0){// line is diaognal
		// set background color
		for (uint16_t q = 0; q<NumOfPixForRec; q++ ){
			DataArrRec[q][0] =Colordata [2];
			DataArrRec[q][1] =Colordata [3];
		}

		for (uint8_t j = CounterIndexY; j<(dy+CounterIndexY); j++ ){
			for (uint8_t i=CounterIndexX;i<(dx+CounterIndexX);i++){
				for (uint8_t m = 0; m<NumOfPixForLine; m++ ){
					if ((DataArr[m][0] == i )&&(DataArr[m][1] == j)){
						//set pixel z as one of line pixels, line colors
						DataArrRec[z][0] =Colordata [0];
						DataArrRec[z][1] =Colordata [1];
						if (   (Thikness > 0)   &&   (Thikness < 10)){ // make sure the thikness is not out of range
							for (uint8_t l=1; l <= Thikness ;l ++){
								// add pixels of color left and right of z
								// check that pixel is at least one Thikness away from left vertical border
								if (i <(dx+CounterIndexX-l)){
									DataArrRec[z+l][0] =Colordata [0];
									DataArrRec[z+l][1] =Colordata [1];
								}
								// check that pixel is at least one Thikness away from right vertical border
								if(i > (CounterIndexX+l-1)){
									DataArrRec[z-l][0] =Colordata [0];
									DataArrRec[z-l][1] =Colordata [1];
								}
								// add pixels top and bottom of z
								// check that pixel is at least one Thikness away from top horizontal order
								if (j <(dy+CounterIndexY-l)){
									DataArrRec[z+dx][0] =Colordata [0];
									DataArrRec[z+dx][1] =Colordata [1];
									// check that pixel is at least one Thikness away from left vertical border
									if (i <(dx+CounterIndexX-l)){
										DataArrRec[z+l+dx][0] =Colordata [0];
										DataArrRec[z+l+dx][1] =Colordata [1];
									}
									// check that pixel is at least one Thikness away from right vertical border
									if(i > (CounterIndexX+l-1)){
										DataArrRec[z-l+dx][0] =Colordata [0];
										DataArrRec[z-l+dx][1] =Colordata [1];
									}

								}
								// check that pixel is at least one Thikness away from bottom horizontal order
								if(j > (CounterIndexY+l)){
									DataArrRec[z-dx][0] =Colordata [0];
									DataArrRec[z-dx][1] =Colordata [1];
									// check that pixel is at least one Thikness away from left vertical border
									if (i <(dx+CounterIndexX-l)){
										DataArrRec[z+l-dx][0] =Colordata [0];
										DataArrRec[z+l-dx][1] =Colordata [1];
									}
									// check that pixel is at least one Thikness away from right vertical border
									if(i > (CounterIndexX+l-1)){
										DataArrRec[z-l-dx][0] =Colordata [0];
										DataArrRec[z-l-dx][1] =Colordata [1];
									}
								}
							}
						}
						break;
					}else{
						//set pixel z as background pixel
						//check if this pixel has already been written to by setting line color pixels
						if(  (DataArrRec[z][0] != Colordata [0] )  &&  (DataArrRec[z][1] != Colordata [1])   ){
							DataArrRec[z][0] =Colordata [2];
							DataArrRec[z][1] =Colordata [3];
						}
					}
				}
				// increase index z
				z++;
			}
		}

	}else if( (dx==0 )||(dy==0)){ // line is horizontal or vertical
		for (uint16_t m = 0; m<NumOfPixForRec; m++ ){
			DataArrRec[m][0] =Colordata [0];
			DataArrRec[m][1] =Colordata [1];
		}
	}else{
		return 1;
	}

// depending on points position one of the 3 AddressWindows is set
if (dx !=0 && dy != 0){
	ST7735_SetAddressWindow(CounterIndexX, CounterIndexY,CounterIndexX+dx-1, CounterIndexY+dy);
}else if (dx==0 ){
	ST7735_SetAddressWindow(CounterIndexX-Thikness, CounterIndexY,CounterIndexX+Thikness, CounterIndexY+dy);
} else if (dy==0 ){
	ST7735_SetAddressWindow(CounterIndexX, CounterIndexY-Thikness,CounterIndexX+dx-1, CounterIndexY+Thikness);
}else{
	return 1;
}
// write data to RAM
	for (uint16_t i = 0; i<NumOfPixForRec;i++){
		// spodnje zaporednje doo
		ST7735S_WriteData(DataArrRec[i][0]);
		ST7735S_WriteData(DataArrRec[i][1]);
	}

	return 0;
}


uint8_t ST7735_DrawLetterOrNumber(uint8_t * pLetterOrNumberPointData_,uint8_t NumberOfLines, uint8_t (* pWindowSizePosition)[2][2], uint16_t * Colors){
	//recast pointer typte
	uint8_t (*pLetterOrNumberPointData)[NumberOfLines][5] = (uint8_t (*) [NumberOfLines][5]) pLetterOrNumberPointData_;
	// check if window SizePosition is in range
	if (IsWindowSizePositionInRange( pWindowSizePosition) != 0){
			return 1;
		}
	//determinate width and length of rectangel that is made with  pWindowSizePosition
	uint8_t dx = abs((*pWindowSizePosition)[0][0] - (*pWindowSizePosition)[1][0]  );
	uint8_t dy = abs((*pWindowSizePosition)[0][1] - (*pWindowSizePosition)[1][1]  );
	// calculate number of pixels
	//uint16_t NumOfPixForRec = dx*dy;
	// to pWindowSizePosition add offsets and save them to  AddressWindowCoordinates array
	uint8_t AddressWindowCoordinates[4];
	AddressWindowCoordinates[0] = (*pWindowSizePosition)[0][0]  + OFFSET_X ;
	AddressWindowCoordinates[1] = (*pWindowSizePosition)[0][1]  + OFFSET_Y;
	AddressWindowCoordinates[2] = (*pWindowSizePosition)[1][0]  + OFFSET_X;
	AddressWindowCoordinates[3] = (*pWindowSizePosition)[1][1]  + OFFSET_Y;

	//check if one of the cooridnates is out of screen range
	if ((AddressWindowCoordinates[0] >(ST7735_WIDTH+OFFSET_X )) ||(AddressWindowCoordinates[2] > (ST7735_WIDTH+ OFFSET_X ))){
		return 1;
	}
	if ((AddressWindowCoordinates[1] >(ST7735_HEIGHT+ OFFSET_Y) ) ||(AddressWindowCoordinates[3] >(ST7735_HEIGHT + OFFSET_Y) )){
			return 1;
		}
	// check how are two points that define adress window positioned one to another, this will determinate
	// which coordinate will start first, save those coordinates to YStart and XStart
	uint8_t retPosPointOneVsPonintTwo;
	uint8_t YStartRec,XStartRec;
	retPosPointOneVsPonintTwo = PosPointOneVsPonintTwo( AddressWindowCoordinates);
	// select first X coordiante of the line to be displayed and store it in  CounterIndexX
	if ((retPosPointOneVsPonintTwo  >=  1 ) && (retPosPointOneVsPonintTwo<=3)){
		XStartRec = AddressWindowCoordinates[2];
	}else if ((retPosPointOneVsPonintTwo >=  4 ) && (retPosPointOneVsPonintTwo<=6)){
		XStartRec = AddressWindowCoordinates[0];
	} else if ((retPosPointOneVsPonintTwo  >=  7 ) && (retPosPointOneVsPonintTwo<=9)){
		XStartRec = AddressWindowCoordinates[0];
	}else{
		return 1;
	}

	// select first Y coordiante of the line to be displayed and store it in  CounterIndexY
	if ((retPosPointOneVsPonintTwo ==  1 ) || (retPosPointOneVsPonintTwo==4)|| (retPosPointOneVsPonintTwo==7)){
		YStartRec = AddressWindowCoordinates[3];
	}else if ((retPosPointOneVsPonintTwo  ==  2 ) || (retPosPointOneVsPonintTwo==5)|| (retPosPointOneVsPonintTwo==8)){
		YStartRec = AddressWindowCoordinates[1];
	} else if ((retPosPointOneVsPonintTwo  ==  3 ) || (retPosPointOneVsPonintTwo==6)|| (retPosPointOneVsPonintTwo==9)){
		YStartRec = AddressWindowCoordinates[1];
	}else{
		return 1;
	}

	//set color
	uint8_t Colordata [4];
	//set line color
		Colordata [1]= (uint8_t )(Colors[0] &0xFF);
		Colordata [0]= (uint8_t ) (Colors[0] >> 8);
		//set line backround color
		Colordata [3]= (uint8_t )(Colors[1] &0xFF);
		Colordata [2]= (uint8_t ) (Colors[1] >> 8);

	//create variable that stores all pixels inside rectange that is created by pWindowSizePosition
	uint8_t PixelArray[dx][dy][2];
	//set rectangle background color
	for (uint8_t j =0; j< dy ;j++ ){ // y coordinates
		for (uint8_t i =0; i< dx;i++ ){ // y coordinates
			//write data to RAM
			PixelArray[i][j][0] = Colordata [2];
			PixelArray[i][j][1] = Colordata [3];
		}
	}

	// create arrays to store values for each linear function
	float Arrayk [NumberOfLines];
	float Arrayn [NumberOfLines];
	// in this array staring end ending points of lines are stored, lines together construct a letter or number
	 uint8_t ArrayPointsOfLInes[NumberOfLines][4];
	 //uint8_t CurrentStoreOfPointData;
	 //uint8_t Counter=0;

	/*points that present starting and ending of lines must be modified with offsets and stored in a separate array
	 *all points should be written back to ArrayPointsOfLInes in the right order, not to have another array
	 */

	 uint8_t VerticalLinesFlag[NumberOfLines];
	 	// set all values of VerticalLinesFlag to 0
	 	for(uint8_t k =0; k< NumberOfLines;k++){
	 		VerticalLinesFlag[k]=0;
	 	}
	 	for(uint8_t i =0; i<NumberOfLines;i++){
			for (uint8_t j =0; j<4;j++){
				ArrayPointsOfLInes[i][j] = (* pLetterOrNumberPointData)[i][j];
			}
	 	}
		//go trough all lines
	for(uint8_t i =0; i<NumberOfLines;i++){
		//Counter = 3;
		//arange points in ArrayPointsOfLInes, so the smaler x from x0 and x1 is put first,
		if(ArrayPointsOfLInes[i][0] > ArrayPointsOfLInes[i][2] ){// coordinate x0 is larger then x1, coordinates must be exchanges
			// copy coordiantes from input array (includes all lines) to local array


				ArrayPointsOfLInes[i][0] = (* pLetterOrNumberPointData)[i][2];
				ArrayPointsOfLInes[i][1] = (* pLetterOrNumberPointData)[i][3];
				ArrayPointsOfLInes[i][2] = (* pLetterOrNumberPointData)[i][0];
				ArrayPointsOfLInes[i][3] = (* pLetterOrNumberPointData)[i][1];

		}else if(ArrayPointsOfLInes[i][0] < ArrayPointsOfLInes[i][2]){// coordinate x0 is smaller then x1, coordinates do not need to be exchanged
			//for (uint8_t j =0; j<4;j++){
				//ArrayPointsOfLInes[i][j] = (* pLetterOrNumberPointData)[i][j];
		//	}
		}else if (ArrayPointsOfLInes[i][0] == ArrayPointsOfLInes[i][2]){ // we have a straight up line
			VerticalLinesFlag[i]=1;

		}else{
			return 1; // something is wrong
		}
		// add offsets, they need to be added before k and n calculation
		ArrayPointsOfLInes[i][0] = ArrayPointsOfLInes[i][0] + OFFSET_X;
		ArrayPointsOfLInes[i][1] = ArrayPointsOfLInes[i][1] +OFFSET_Y;
		ArrayPointsOfLInes[i][2] = ArrayPointsOfLInes[i][2] + OFFSET_X;
		ArrayPointsOfLInes[i][3] = ArrayPointsOfLInes[i][3] +OFFSET_Y;

		if (VerticalLinesFlag[i]==0){
		//calculate k and n parameters for each line
		Arrayk[i] = CalcLinFunCoef (ArrayPointsOfLInes[i]);
		Arrayn[i] =CalcStartVal (Arrayk[i],ArrayPointsOfLInes[i]);
		}
	}

	uint8_t YVertical[2]={0,0};
	uint8_t Y_CalculationFlag[NumberOfLines];
	uint8_t YVal;
	uint8_t XEND=XStartRec+dx-1;
	//int8_t ScalingMatrix[2]={0,0};
	// set all values of Y_CalculationFlag to 0
	for(uint8_t k =0; k< NumberOfLines;k++){
  		Y_CalculationFlag[k]=0;
	}
	// for loop goes trough all x coordinates form the window definition
	for(uint8_t i=XStartRec;i<XEND;i++){
		//check if multiple lines hava start in one x coordinate

		for(uint8_t k =0; k< NumberOfLines;k++){
		// check if  x coordinates are the same as starting x coordinates writen in  current ArrayPointsOfLInes
			if ((i == ArrayPointsOfLInes[k][0]) && (VerticalLinesFlag[k] == 0) ){
			// set Y_caluculationFlag for k-th line
				Y_CalculationFlag[k]=1; //  y values of the line will be calculated and writen to Pixel Array
			}
			// check if  x coordinates are the same as ending x coordinates writen in  current ArrayPointsOfLInes
			if((i == ArrayPointsOfLInes[k][2])&& (VerticalLinesFlag[k] == 0) ){
				// reset Y_caluculationFlag for k-th line
					Y_CalculationFlag[k]=0; //  y values of the line will not be calculated
				}
		}


		for(uint8_t k =0; k< NumberOfLines;k++){
			if (Y_CalculationFlag[k] == 1){
				YVal = Arrayk[k]*i+ Arrayn[k];

				if( (* pLetterOrNumberPointData)[k][4]>0){
					// make line thick
					for (int8_t p =-(* pLetterOrNumberPointData)[k][4];p<=(* pLetterOrNumberPointData)[k][4];p++){
						for (int8_t r =-(* pLetterOrNumberPointData)[k][4];r<=(* pLetterOrNumberPointData)[k][4];r++){
							PixelArray[i-OFFSET_X+r][YVal-OFFSET_Y+p][0] = Colordata [0];
							PixelArray[i-OFFSET_X+r][YVal-OFFSET_Y+p][1] = Colordata [1];
						}
					}
					//
				}else{
					PixelArray[i-OFFSET_X][YVal-OFFSET_Y][0] = Colordata [0];
					PixelArray[i-OFFSET_X][YVal-OFFSET_Y][1] = Colordata [1];
				}

			}
			if ((VerticalLinesFlag[k] == 1)&&(i == ArrayPointsOfLInes[k][0])){
				if (ArrayPointsOfLInes[k][1]<ArrayPointsOfLInes[k][3]){
					YVertical[0]=ArrayPointsOfLInes[k][1];
					YVertical[1]=ArrayPointsOfLInes[k][3];
				}else if (ArrayPointsOfLInes[k][1] > ArrayPointsOfLInes[k][3]){
					YVertical[0]=ArrayPointsOfLInes[k][3];
					YVertical[1]=ArrayPointsOfLInes[k][1];
			}
				for(uint8_t l = YVertical[0] ; l< YVertical[1];l++){
					if( (* pLetterOrNumberPointData)[k][4]>0){
						for (int8_t p =-(* pLetterOrNumberPointData)[k][4];p<=(* pLetterOrNumberPointData)[k][4];p++){
							for (int8_t r =-(* pLetterOrNumberPointData)[k][4];r<=(* pLetterOrNumberPointData)[k][4];r++){


								PixelArray[i-OFFSET_X+r][l-OFFSET_Y+p][0] = Colordata [0];
								PixelArray[i-OFFSET_X+r][l-OFFSET_Y+p][1] = Colordata [1];
							}
						}
					}else{

						PixelArray[i-OFFSET_X][l-OFFSET_Y][0] = Colordata [0];
						PixelArray[i-OFFSET_X][l-OFFSET_Y][1] = Colordata [1];
					}

				}
				VerticalLinesFlag[k] =0;
		}
		}

	}

	ST7735_SetAddressWindow(XStartRec, YStartRec,XStartRec+dx-1, YStartRec+dy);

	// write data to RAM
		for (uint16_t i = 0; i<dx;i++){
			for (uint16_t j = 0; j<dy;j++){
				ST7735S_WriteData(PixelArray[j][i][0]);
				ST7735S_WriteData(PixelArray[j][i][1]);
			}
		}
	return 0;
}

uint8_t IsWindowSizePositionInRange( uint8_t (* pWindowSizePosition) [2][2]){
	if(            ((* pWindowSizePosition)[0][0] >= 0 )   &&  ((* pWindowSizePosition)[0][0] <= ST7735_WIDTH )  &&  // check x of fist point
					((* pWindowSizePosition)[1][0] >= 0 )   &&  ((* pWindowSizePosition)[1][0] <= ST7735_WIDTH )  &&  // check y of first point
					((* pWindowSizePosition)[0][1] >= 0 )   &&  ((* pWindowSizePosition)[0][1] <= ST7735_HEIGHT )  &&  // check x of second point
					((* pWindowSizePosition)[1][1] >= 0 )   &&  ((* pWindowSizePosition)[1][1] <= ST7735_HEIGHT ) ){ // check y of second point

	return 0;
	}else{
		return 1;
	}
}

float CalcLinFunCoef ( uint8_t * Coordinates){
	 float dx = (float)Coordinates[2] - (float)Coordinates[0];
	 float dy = (float)Coordinates[3] - (float)Coordinates[1];
	    if (dx == 0.0f)
	    {
	        // vertical line or error handling
	        return 0.0f;
	    }
	    return dy / dx;
	}
float CalcStartVal (float k, uint8_t * Coordinates){
	float n1 = (float)Coordinates[3] - k*(float)Coordinates[2];
	float n0 = (float)Coordinates[1] - k*(float)Coordinates[0];

	if ((int16_t)n0 == (int16_t)n1){
		return n1;
	}else {
		while(1);
	}
}
void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	ST7735S_WriteCommand(0x2a); // Column addr set
		ST7735S_WriteData(0x00);            // XS15 ~ XS8
		ST7735S_WriteData(x0+0);     // XSTART       XS7 ~ XS0
		ST7735S_WriteData(0x00);            // XE15 ~ XE8
		ST7735S_WriteData(x1+0);     // XEND         XE7 ~ XE0

		ST7735S_WriteCommand(0x2b); // Row addr set
		ST7735S_WriteData(0x00);
		ST7735S_WriteData(y0+0);     // YSTART
		ST7735S_WriteData(0x00);
		ST7735S_WriteData(y1+0);     // YEND

		ST7735S_WriteCommand(0x2c);
}
uint8_t PosPointOneVsPonintTwo(uint8_t* Coordinates){
//figure out how are start and end point of the line positioned in the coordinate system
	/*
	* CoordinateXValFlag = 1; // x0 > x1, y0 > y1
	* CoordinateXValFlag = 2; // x0 > x1, y0 < y1
	* CoordinateXValFlag = 3; // x0 > x1, y0 == y1
	* CoordinateXValFlag = 4; // x0 < x1, y0 > y1
	* CoordinateXValFlag = 5; // x0 < x1, y0 < y1
	* CoordinateXValFlag = 6; // x0 < x1, y0 == y1
	* CoordinateXValFlag = 7; // x0 == x1, y0 > y1
	* CoordinateXValFlag = 8; // x0 == x1, y0 < y1
	* CoordinateXValFlag = 9; // x0 == x1, y0 == y1
	*/


uint8_t CoordinateXValFlag =0;
if (Coordinates[0] > Coordinates[2]) { // x0 > x1
    if (Coordinates[1] > Coordinates[3]) { // y0 > y1
        ST7735_SetAddressWindow(Coordinates[2], Coordinates[0], Coordinates[3], Coordinates[2]);
        CoordinateXValFlag=1;// x0 > x1 // y0 > y1
    } else if (Coordinates[1] < Coordinates[3]) { // y0 < y1
        ST7735_SetAddressWindow(Coordinates[2], Coordinates[0], Coordinates[2], Coordinates[3]);
        CoordinateXValFlag=2;// x0 > x1 // y0 < y1
    }else if (Coordinates[1] == Coordinates[3]) { // y0 < y1
    	ST7735_SetAddressWindow(Coordinates[2], Coordinates[0], Coordinates[2], Coordinates[3]);
    	CoordinateXValFlag=3;// x0 > x1 // y0 == y1
    }
} else if (Coordinates[0] < Coordinates[2]) { // x0 < x1
    if (Coordinates[1] > Coordinates[3]) { // y0 > y1
        ST7735_SetAddressWindow(Coordinates[0], Coordinates[2], Coordinates[3], Coordinates[2]);
        CoordinateXValFlag=4;// x0< x1 // y0 > y1
    } else if (Coordinates[1] < Coordinates[3]) { // y0 < y1
        ST7735_SetAddressWindow(Coordinates[0], Coordinates[2], Coordinates[2], Coordinates[3]);
        CoordinateXValFlag=5;// x0< x1 // y0 > y1
    }else if (Coordinates[1] == Coordinates[3]) { // y0 < y1)
    	CoordinateXValFlag=6;// x0 > x1 // y0 == y1
    	}
}else if(Coordinates[0] == Coordinates[2]) { // x0==x1
	  if (Coordinates[1] > Coordinates[3]) { // y0 > y1
			ST7735_SetAddressWindow(Coordinates[0], Coordinates[2], Coordinates[3], Coordinates[2]);
			CoordinateXValFlag=7;// x0== x1 // y0 > y1
		} else if (Coordinates[1] < Coordinates[3]) { // y0 < y1
			ST7735_SetAddressWindow(Coordinates[0], Coordinates[2], Coordinates[2], Coordinates[3]);
			CoordinateXValFlag=8;// x0== x1 // y0 < y1
		}else if (Coordinates[1] == Coordinates[3]) { // y0 < y1)
			CoordinateXValFlag=9;// x0 == x1 // y0 == y1
		}
}
return CoordinateXValFlag;
}

uint8_t ST7735_DeleteLetterOrNumber( uint8_t (* pWindowSizePosition)[2][2], uint16_t * Colors){


	// check if window SizePosition is in range
	if (IsWindowSizePositionInRange( pWindowSizePosition) != 0){
			return 1;
		}
	//determinate width and length of rectangel that is made with  pWindowSizePosition
	uint8_t dx = abs((*pWindowSizePosition)[0][0] - (*pWindowSizePosition)[1][0]  );
	uint8_t dy = abs((*pWindowSizePosition)[0][1] - (*pWindowSizePosition)[1][1]  );
	// calculate number of pixels
	//uint16_t NumOfPixForRec = dx*dy;
	// to pWindowSizePosition add offsets and save them to  AddressWindowCoordinates array
	uint8_t AddressWindowCoordinates[4];
	AddressWindowCoordinates[0] = (*pWindowSizePosition)[0][0]  + OFFSET_X ;
	AddressWindowCoordinates[1] = (*pWindowSizePosition)[0][1]  + OFFSET_Y;
	AddressWindowCoordinates[2] = (*pWindowSizePosition)[1][0]  + OFFSET_X;
	AddressWindowCoordinates[3] = (*pWindowSizePosition)[1][1]  + OFFSET_Y;

	//check if one of the cooridnates is out of screen range
	if ((AddressWindowCoordinates[0] >(ST7735_WIDTH+OFFSET_X )) ||(AddressWindowCoordinates[2] > (ST7735_WIDTH+ OFFSET_X ))){
		return 1;
	}
	if ((AddressWindowCoordinates[1] >(ST7735_HEIGHT+ OFFSET_Y) ) ||(AddressWindowCoordinates[3] >(ST7735_HEIGHT + OFFSET_Y) )){
			return 1;
		}
	// check how are two points that define adress window positioned one to another, this will determinate
	// which coordinate will start first, save those coordinates to YStart and XStart
	uint8_t retPosPointOneVsPonintTwo;
	uint8_t YStartRec,XStartRec;
	retPosPointOneVsPonintTwo = PosPointOneVsPonintTwo( AddressWindowCoordinates);
	// select first X coordiante of the line to be displayed and store it in  CounterIndexX
	if ((retPosPointOneVsPonintTwo  >=  1 ) && (retPosPointOneVsPonintTwo<=3)){
		XStartRec = AddressWindowCoordinates[2];
	}else if ((retPosPointOneVsPonintTwo >=  4 ) && (retPosPointOneVsPonintTwo<=6)){
		XStartRec = AddressWindowCoordinates[0];
	} else if ((retPosPointOneVsPonintTwo  >=  7 ) && (retPosPointOneVsPonintTwo<=9)){
		XStartRec = AddressWindowCoordinates[0];
	}else{
		return 1;
	}

	// select first Y coordiante of the line to be displayed and store it in  CounterIndexY
	if ((retPosPointOneVsPonintTwo ==  1 ) || (retPosPointOneVsPonintTwo==4)|| (retPosPointOneVsPonintTwo==7)){
		YStartRec = AddressWindowCoordinates[3];
	}else if ((retPosPointOneVsPonintTwo  ==  2 ) || (retPosPointOneVsPonintTwo==5)|| (retPosPointOneVsPonintTwo==8)){
		YStartRec = AddressWindowCoordinates[1];
	} else if ((retPosPointOneVsPonintTwo  ==  3 ) || (retPosPointOneVsPonintTwo==6)|| (retPosPointOneVsPonintTwo==9)){
		YStartRec = AddressWindowCoordinates[1];
	}else{
		return 1;
	}

	//set color
	uint8_t Colordata [4];
	//set line color
		Colordata [1]= (uint8_t )(Colors[0] &0xFF);
		Colordata [0]= (uint8_t ) (Colors[0] >> 8);
		//set line backround color
		Colordata [3]= (uint8_t )(Colors[1] &0xFF);
		Colordata [2]= (uint8_t ) (Colors[1] >> 8);

	//create variable that stores all pixels inside rectange that is created by pWindowSizePosition
	uint8_t PixelArray[dx][dy][2];
	//set rectangle background color
	for (uint8_t j =0; j< dy ;j++ ){ // y coordinates
		for (uint8_t i =0; i< dx;i++ ){ // y coordinates
			//write data to RAM
			PixelArray[i][j][0] = Colordata [2];
			PixelArray[i][j][1] = Colordata [3];
		}
	}

	ST7735_SetAddressWindow(XStartRec, YStartRec,XStartRec+dx-1, YStartRec+dy);

	// write data to RAM
		for (uint16_t i = 0; i<dx;i++){
			for (uint16_t j = 0; j<dy;j++){
				ST7735S_WriteData(PixelArray[j][i][0]);
				ST7735S_WriteData(PixelArray[j][i][1]);
			}
		}
	return 0;
}
