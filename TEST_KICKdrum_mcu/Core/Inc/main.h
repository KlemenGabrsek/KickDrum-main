/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "macros.h"
#include "structures.h"
#include "SwitchesInit.h"
#include "functions.h"
#include "TFT_LCD_function.h"
#include "Convert_slider_val_to_LCD.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CymbalEnable_Pin GPIO_PIN_13
#define CymbalEnable_GPIO_Port GPIOC
#define CowbellEnable_Pin GPIO_PIN_14
#define CowbellEnable_GPIO_Port GPIOC
#define TomEnable_Pin GPIO_PIN_15
#define TomEnable_GPIO_Port GPIOC
#define Touch_RESET2_Pin GPIO_PIN_0
#define Touch_RESET2_GPIO_Port GPIOC
#define TFTScreen_RS_Pin GPIO_PIN_1
#define TFTScreen_RS_GPIO_Port GPIOC
#define TFTScreen_Reset_Pin GPIO_PIN_2
#define TFTScreen_Reset_GPIO_Port GPIOC
#define LedDriver_SDB2_Pin GPIO_PIN_3
#define LedDriver_SDB2_GPIO_Port GPIOC
#define BassDrum_VRC_LEVEL_PWM_Pin GPIO_PIN_0
#define BassDrum_VRC_LEVEL_PWM_GPIO_Port GPIOA
#define BassDrum_VCR_DELAY_PWM_Pin GPIO_PIN_1
#define BassDrum_VCR_DELAY_PWM_GPIO_Port GPIOA
#define Claves_VRC_LEVEL_PWM_Pin GPIO_PIN_2
#define Claves_VRC_LEVEL_PWM_GPIO_Port GPIOA
#define RimShot_VCR_LEVEL_PWM_Pin GPIO_PIN_3
#define RimShot_VCR_LEVEL_PWM_GPIO_Port GPIOA
#define BassDrumEnable_Pin GPIO_PIN_4
#define BassDrumEnable_GPIO_Port GPIOA
#define Conga_VCR_LEVEL_PWM_Pin GPIO_PIN_6
#define Conga_VCR_LEVEL_PWM_GPIO_Port GPIOA
#define LedDriver_SDB1_Pin GPIO_PIN_4
#define LedDriver_SDB1_GPIO_Port GPIOC
#define Tom_VCR_LEVEL_PWM_Pin GPIO_PIN_0
#define Tom_VCR_LEVEL_PWM_GPIO_Port GPIOB
#define ClavesEnable_Pin GPIO_PIN_1
#define ClavesEnable_GPIO_Port GPIOB
#define RimShotEnable_Pin GPIO_PIN_2
#define RimShotEnable_GPIO_Port GPIOB
#define CongaEnable_Pin GPIO_PIN_12
#define CongaEnable_GPIO_Port GPIOB
#define SnareDrumEnable_Pin GPIO_PIN_13
#define SnareDrumEnable_GPIO_Port GPIOB
#define Cymbal_VRC_LEVEL_PWM_Pin GPIO_PIN_14
#define Cymbal_VRC_LEVEL_PWM_GPIO_Port GPIOB
#define Cymbal_VRC_DECAY_PWM_Pin GPIO_PIN_15
#define Cymbal_VRC_DECAY_PWM_GPIO_Port GPIOB
#define Accent_TRIG_LEVEL_PWM_Pin GPIO_PIN_6
#define Accent_TRIG_LEVEL_PWM_GPIO_Port GPIOC
#define ACCENT_TRIGGER_Pin GPIO_PIN_7
#define ACCENT_TRIGGER_GPIO_Port GPIOC
#define Cowbel_VRC_LEVEL_PWM_Pin GPIO_PIN_9
#define Cowbel_VRC_LEVEL_PWM_GPIO_Port GPIOC
#define SnareDrum_VCR_SNAPPY_PWM_Pin GPIO_PIN_8
#define SnareDrum_VCR_SNAPPY_PWM_GPIO_Port GPIOA
#define SnareDrum_VCR_LEVEL_PWM_Pin GPIO_PIN_9
#define SnareDrum_VCR_LEVEL_PWM_GPIO_Port GPIOA
#define Accent_DEFAULT_Pin GPIO_PIN_4
#define Accent_DEFAULT_GPIO_Port GPIOB
#define Touch_RESET1_Pin GPIO_PIN_5
#define Touch_RESET1_GPIO_Port GPIOB
#define INTB1_Pin GPIO_PIN_8
#define INTB1_GPIO_Port GPIOB
#define INTB1_EXTI_IRQn EXTI9_5_IRQn
#define INTB2_Pin GPIO_PIN_9
#define INTB2_GPIO_Port GPIOB
#define INTB2_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
