/*
 * Convert_slider_val_to_LCD.h
 *
 *  Created on: 26 Feb 2025
 *      Author: Klemen
 */

#ifndef INC_CONVERT_SLIDER_VAL_TO_LCD_H_
#define INC_CONVERT_SLIDER_VAL_TO_LCD_H_

#include <stdio.h>
#include "TFT_LCD_function.h"
uint8_t DisplaySliderDataOnLCD (uint8_t SliderVal,uint8_t WindowSizePositions[3][2][2],uint16_t Colors[2],uint8_t **AllFrames[3],uint8_t NumOfLines[10] );




#endif /* INC_CONVERT_SLIDER_VAL_TO_LCD_H_ */
