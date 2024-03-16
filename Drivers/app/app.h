/*
 * app.h
 *
 *  Created on: Mar 16, 2024
 *      Author: abosa
 */

#ifndef APP_H_
#define APP_H_

#include "ultraSonic.h"
#include "motorDriver.h"
#include "stdio.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;

extern UART_HandleTypeDef huart6;
//TIM_HandleTypeDef htim2;
/* USER CODE BEGIN PV */
#define MAX_DISTANCE 100
#define MIN_DISTANCE 15
#define MAX_WARNING_DISTANCE 300  // Adjust as needed
#define MIN_WARNING_DISTANCE 100
/* USER CODE END PV */



#define Echo5_Pin 			GPIO_PIN_0
#define Echo5_GPIO_Port 	GPIOA
#define Trig5_Pin 			GPIO_PIN_1
#define Trig5_GPIO_Port 	GPIOA
#define Echo6_Pin 			GPIO_PIN_2
#define Echo6_GPIO_Port 	GPIOA
#define Trig6_Pin			GPIO_PIN_3
#define Trig6_GPIO_Port 	GPIOA
#define Trig2_Pin 			GPIO_PIN_4
#define Trig2_GPIO_Port 	GPIOA
#define Echo2_Pin 			GPIO_PIN_5
#define Echo2_GPIO_Port 	GPIOA
#define Echo3_Pin 			GPIO_PIN_6
#define Echo3_GPIO_Port 	GPIOA
#define Trig3_Pin 			GPIO_PIN_7
#define Trig3_GPIO_Port 	GPIOA
#define led_Pin 			GPIO_PIN_1
#define led_GPIO_Port 		GPIOB
#define Echo1_Pin 			GPIO_PIN_8
#define Echo1_GPIO_Port 	GPIOA
#define Trig1_Pin 			GPIO_PIN_9
#define Trig1_GPIO_Port 	GPIOA
#define Trig4_Pin 			GPIO_PIN_5
#define Trig4_GPIO_Port 	GPIOB
#define Echo4_Pin 			GPIO_PIN_6
#define Echo4_GPIO_Port 	GPIOB



void app_init(void);
void app_start(void);
void MX_USART6_UART_Init(void);

void adjustMotors(uint16_t distance);
void ACC(void);
void collisionWarning(void);
uint32_t constrain(uint32_t value, uint32_t min, uint32_t max);
uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);

#endif /* APP_H_ */
