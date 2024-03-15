/*
 * motorDriver.h
 *
 *  Created on: Mar 13, 2024
 *      Author: abosa
 */

#ifndef INC_MOTORDRIVER_H_
#define INC_MOTORDRIVER_H_

#include "stm32f4xx_hal.h"


typedef enum {
    MOTOR_DIRECTION_FORWARD,
    MOTOR_DIRECTION_BACKWARD
} MotorDirection;

typedef enum {
    MOTOR_A,
	MOTOR_B
} Motor;

#define MOTOR_A_TIM &htim2
#define MOTOR_B_TIM &htim2

#define MOTOR_A_CHANNEL TIM_CHANNEL_2  //PB3
#define MOTOR_B_CHANNEL TIM_CHANNEL_3  //PB10

#define MOTOR_A_IN1_PORT GPIOB
#define MOTOR_A_IN2_PORT GPIOB
#define MOTOR_A_IN1_PIN GPIO_PIN_12
#define MOTOR_A_IN2_PIN GPIO_PIN_13

#define MOTOR_B_IN1_PORT GPIOB
#define MOTOR_B_IN2_PORT GPIOB
#define MOTOR_B_IN1_PIN GPIO_PIN_14
#define MOTOR_B_IN2_PIN GPIO_PIN_15


void Init_PWM_Timer(TIM_HandleTypeDef *htim,TIM_TypeDef *timerInstance, uint32_t Prescaler, uint32_t Period, uint32_t pwm_channel_init);
void motor_init(Motor motor);
void motor_set_speed(Motor motor ,uint16_t speed );
void motor_set_direction(Motor motor,MotorDirection direction);


#endif /* INC_MOTORDRIVER_H_ */
