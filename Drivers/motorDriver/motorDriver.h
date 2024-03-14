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

#define MOTOR_1_TIM &htim2
#define MOTOR_2_TIM &htim2

#define MOTOR_1_CHANNEL TIM_CHANNEL_2
#define MOTOR_2_CHANNEL TIM_CHANNEL_3

#define MOTOR_1_PORT GPIOB
#define MOTOR_2_PORT GPIOB
#define MOTOR_1_PIN GPIO_PIN_3
#define MOTOR_2_PIN GPIO_PIN_10


void Init_PWM_Timer(TIM_HandleTypeDef *htim,TIM_TypeDef *timerInstance, uint32_t Prescaler, uint32_t Period, uint32_t pwm_channel_init);
void motor_init(TIM_HandleTypeDef *htim_pwm_init,TIM_TypeDef *timerInstance, uint32_t pwm_channel_init, GPIO_TypeDef *port_dir1_init, uint16_t pin_dir1_init, GPIO_TypeDef *port_dir2_init, uint16_t pin_dir2_init);
void motor_set_speed(uint16_t speed);
void motor_set_direction(MotorDirection direction);


#endif /* INC_MOTORDRIVER_H_ */
