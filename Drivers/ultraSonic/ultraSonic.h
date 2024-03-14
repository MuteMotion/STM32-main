/*
 * ultraSonic.h
 *
 *  Created on: Mar 1, 2024
 *      Author: abosa
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_


#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"



extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;

#define prescaler 4
#define period 255

#define TRIG_1_PORT GPIOA
#define TRIG_1_PIN	GPIO_PIN_9
#define TRIG_2_PORT GPIOA
#define TRIG_2_PIN	GPIO_PIN_4
#define TRIG_3_PORT GPIOA
#define TRIG_3_PIN	GPIO_PIN_7
#define TRIG_4_PORT GPIOB
#define TRIG_4_PIN	GPIO_PIN_5
#define TRIG_5_PORT GPIOA
#define TRIG_5_PIN	GPIO_PIN_1
#define TRIG_6_PORT GPIOA
#define TRIG_6_PIN	GPIO_PIN_3


void Init_Timer(TIM_HandleTypeDef *htim,TIM_TypeDef *timerInstance);
void Init_GPIO(GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin);

void  ultraSonic_Init(void);
float ultraSonic_readDistance(GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin, GPIO_TypeDef *ECHO_Port, uint16_t ECHO_Pin, TIM_HandleTypeDef *htim);

#endif /* INC_ULTRASONIC_H_ */
