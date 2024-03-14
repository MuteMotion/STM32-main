/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "ultraSonic.h"
#include "motorDriver.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Echo5_Pin GPIO_PIN_0
#define Echo5_GPIO_Port GPIOA
#define Trig5_Pin GPIO_PIN_1
#define Trig5_GPIO_Port GPIOA
#define Echo6_Pin GPIO_PIN_2
#define Echo6_GPIO_Port GPIOA
#define Trig6_Pin GPIO_PIN_3
#define Trig6_GPIO_Port GPIOA
#define Trig2_Pin GPIO_PIN_4
#define Trig2_GPIO_Port GPIOA
#define Echo2_Pin GPIO_PIN_5
#define Echo2_GPIO_Port GPIOA
#define Echo3_Pin GPIO_PIN_6
#define Echo3_GPIO_Port GPIOA
#define Trig3_Pin GPIO_PIN_7
#define Trig3_GPIO_Port GPIOA
#define led_Pin GPIO_PIN_1
#define led_GPIO_Port GPIOB
#define Echo1_Pin GPIO_PIN_8
#define Echo1_GPIO_Port GPIOA
#define Trig1_Pin GPIO_PIN_9
#define Trig1_GPIO_Port GPIOA
#define Trig4_Pin GPIO_PIN_5
#define Trig4_GPIO_Port GPIOB
#define Echo4_Pin GPIO_PIN_6
#define Echo4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
