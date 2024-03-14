/*
 * ultraSonic.c
 *
 *  Created on: Mar 1, 2024
 *      Author: abosa
 */
#include "ultraSonic.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim9;



void ultraSonic_Init(void){
		Init_Timer(&htim1,TIM1);
	    Init_Timer(&htim2,TIM2);
	    Init_Timer(&htim3,TIM3);
	    Init_Timer(&htim4,TIM4);
	    Init_Timer(&htim5,TIM5);
	    Init_Timer(&htim9,TIM9);

	    Init_GPIO(TRIG_1_PORT, TRIG_1_PIN);
	    Init_GPIO(TRIG_2_PORT, TRIG_2_PIN);
	    Init_GPIO(TRIG_3_PORT, TRIG_3_PIN);
	    Init_GPIO(TRIG_4_PORT, TRIG_4_PIN);
	    Init_GPIO(TRIG_5_PORT, TRIG_5_PIN);
	    Init_GPIO(TRIG_6_PORT, TRIG_6_PIN);
}




void Init_Timer(TIM_HandleTypeDef *htim,TIM_TypeDef *timerInstance) {
    htim->Instance = timerInstance; // Adjust the timer instance as per your requirement
    htim->Init.Prescaler = prescaler;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = period;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_Base_Init(htim);
    HAL_TIM_Base_Start(htim);

}


void Init_GPIO(GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (TRIG_Port == GPIOA)
	{__HAL_RCC_GPIOA_CLK_ENABLE();}
	else if(TRIG_Port == GPIOB)
	{__HAL_RCC_GPIOB_CLK_ENABLE();}
	else if (TRIG_Port == GPIOC)
	{__HAL_RCC_GPIOC_CLK_ENABLE();}

	HAL_GPIO_WritePin(TRIG_Port, TRIG_Pin, GPIO_PIN_RESET);

		  /*Configure GPIO pins */
		GPIO_InitStruct.Pin = TRIG_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(TRIG_Port, &GPIO_InitStruct);



}


float ultraSonic_readDistance(GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin, GPIO_TypeDef *ECHO_Port, uint16_t ECHO_Pin, TIM_HandleTypeDef *htim) {
    uint32_t pMillis;
    uint32_t Value1 = 0;
    uint32_t Value2 = 0;
    uint16_t Distance  = 0;  // cm

    HAL_GPIO_WritePin(TRIG_Port, TRIG_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
    __HAL_TIM_SET_COUNTER(htim, 0);
    while (__HAL_TIM_GET_COUNTER(htim) < 10);  // wait for 10 us
    HAL_GPIO_WritePin(TRIG_Port, TRIG_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

    pMillis = HAL_GetTick(); // used this to avoid infinite while loop  (for timeout)
    // wait for the echo pin to go high
    while (!(HAL_GPIO_ReadPin(ECHO_Port, ECHO_Pin)) && pMillis + 10 >  HAL_GetTick());
    Value1 = __HAL_TIM_GET_COUNTER(htim);

    pMillis = HAL_GetTick(); // used this to avoid infinite while loop (for timeout)
    // wait for the echo pin to go low
    while ((HAL_GPIO_ReadPin(ECHO_Port, ECHO_Pin)) && pMillis + 50 > HAL_GetTick());
    Value2 = __HAL_TIM_GET_COUNTER(htim);

    Distance = (Value2 - Value1) * 0.034 / 2;

    return Distance;
}
