/*
 * Convert_slider_val_to_LCD.c
 *
 *  Created on: 26 Feb 2025
 *      Author: Klemen
 */

#include "Convert_slider_val_to_LCD.h"

uint8_t DisplaySliderDataOnLCD (uint8_t SliderVal,uint8_t WindowSizePositions[3][2][2],uint16_t Colors[2],uint8_t **AllFrames[3],uint8_t NumOfLines[10] ){
	//definiramo prostor za sharnjevanje enic, desetic, stotic
	uint8_t Enice = 0;
	uint8_t Desetice = 0;
	uint8_t Stotice = 0;
	uint8_t Ostanek = 0;
	//return vrednost funkcije za izris
	uint8_t Ret;



	Ostanek = SliderVal%1000;

	if (Ostanek == 100){
		Stotice = 1;
	}else{
		Ostanek = SliderVal%100;
		if(Ostanek < 10){
			Enice = Ostanek;
		} else if (Ostanek >=10) {
			Enice = Ostanek%10;
			Desetice = (Ostanek-Enice)/10;
		}
	}

	//izpis enice
	 Ret=ST7735_DrawLetterOrNumber(AllFrames[0][Enice], NumOfLines[Enice],&WindowSizePositions[0] , Colors);
	   if(Ret==1){
		   while(1);
	   }
   //izpis desetic
	 Ret=ST7735_DrawLetterOrNumber(AllFrames[1][Desetice], NumOfLines[Desetice],&WindowSizePositions[1] , Colors);
	   if(Ret==1){
		   while(1);
	   }
	//izpis stotic
		 Ret=ST7735_DrawLetterOrNumber(AllFrames[2][Stotice], NumOfLines[Stotice],&WindowSizePositions[2] , Colors);
		   if(Ret==1){
			   while(1);
		   }

	return 0;
}

