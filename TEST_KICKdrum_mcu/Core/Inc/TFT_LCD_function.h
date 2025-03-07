/*
 * TFT_LCD_function.h
 *
 *  Created on: 26 Feb 2025
 *      Author: Klemen
 */

#ifndef INC_TFT_LCD_FUNCTION_H_
#define INC_TFT_LCD_FUNCTION_H_

#include "stm32f4xx_hal.h"

#include <stdlib.h>

#define DISPLAY_ORENTATION 1
// 0 PRIKAŽI ČRKE  NAVPIČNO S EKRANOM
// 1 PRIKAŽI ČRKE  PRAVOKOTNO S EKRANOM

#define BLOCK_4_START_X  10
#define BLOCK_4_STOP_X   50
#define BLOCK_4_START_Y  80
#define BLOCK_4_STOP_Y   120

#define BLOCK_5_START_X  10
#define BLOCK_5_STOP_X   50
#define BLOCK_5_START_Y  40
#define BLOCK_5_STOP_Y    80

#define BLOCK_6_START_X  10
#define BLOCK_6_STOP_X   50
#define BLOCK_6_START_Y  0
#define BLOCK_6_STOP_Y   40




// SPI Handle
extern SPI_HandleTypeDef hspi1;  // Adjust to your SPI instance (e.g., hspi2, hspi3)

// Screen dimensions
#define ST7735_WIDTH  79
#define ST7735_HEIGHT 159

//number of pixels
# define NUM_OF_PIX ((ST7735_WIDTH+1) * (ST7735_HEIGHT+1))

//Screnn offsets
#define OFFSET_X 26
#define OFFSET_Y 1

//screen colors
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0xF800
#define	ST7735_RED     0x001F
#define	ST7735_GREEN   0x07E0
#define ST7735_WHITE   0xFFFF


#define NUM_OF_LETTERS_NUM 18

#define NUM_OF_LINES_O 8

#define NUM_OF_LINES_1 2
#define NUM_OF_LINES_2 6
#define NUM_OF_LINES_3 12
#define NUM_OF_LINES_4 4
#define NUM_OF_LINES_5 7
#define NUM_OF_LINES_6 10
#define NUM_OF_LINES_7 5
#define NUM_OF_LINES_8 16
#define NUM_OF_LINES_9 10

#define NUM_OF_LINES_ARRAY { NUM_OF_LINES_O, \
    NUM_OF_LINES_1, NUM_OF_LINES_2, NUM_OF_LINES_3, NUM_OF_LINES_4, NUM_OF_LINES_5, \
    NUM_OF_LINES_6, NUM_OF_LINES_7, NUM_OF_LINES_8, NUM_OF_LINES_9 \
}



#define ST7735_SWRRESET 0X01
#define ST7735_SLPOUT  0x11






void ST7735S_WriteData(uint8_t Data);
void ST7735S_WriteCommand(uint8_t Data);
void ST7735S_HW_RESET();
uint8_t ST7735_DrawPixel(uint16_t x, uint16_t y,  uint16_t Color);
void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void ST7735S_Init();
uint8_t ST7735_DrawLine(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1, uint16_t Color, uint16_t BackColor);
 float CalcLinFunCoef ( uint8_t * Coordiantes);
float CalcStartVal (float k, uint8_t * Coordinates);
uint8_t PosPointOneVsPonintTwo(uint8_t* Coordinates);
uint8_t ST7735_DrawThickLine(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1, uint16_t LineColor, uint16_t BackColor,uint8_t Thikness);
uint8_t ST7735_DrawLetterOrNumber(uint8_t * pLetterOrNumberPointData_,uint8_t NumberOfLines, uint8_t (* pWindowSizePosition)[2][2], uint16_t * Colors);
uint8_t IsWindowSizePositionInRange( uint8_t (* pWindowSizePosition) [2][2]);
uint8_t ST7735_DeleteLetterOrNumber( uint8_t (* pWindowSizePosition)[2][2], uint16_t * Colors);

//uint8_t  ConvertCharDataToPointsArr(struct LetterOrNumber *LetOrNum,uint8_t WhichCahr, uint8_t StartPointX,uint8_t StartPointY);


void ST7735S_SetScreenColor( uint16_t Color);

extern uint8_t ReceivedData[3][5];

//#endif /* INC_TFT_FUNCTIONS_H_ */







#endif /* TFT_LCD_FUNCTION_H_ */
