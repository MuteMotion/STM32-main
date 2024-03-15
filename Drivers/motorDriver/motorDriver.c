#include "motorDriver.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;

void Init_PWM_Timer(TIM_HandleTypeDef *htim, TIM_TypeDef *timerInstance, uint32_t Prescaler, uint32_t Period, uint32_t pwm_channel_init) {
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim->Instance = timerInstance; // Adjust the timer instance as per your requirement
    htim->Init.Prescaler = Prescaler;
    htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim->Init.Period = Period;
    htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(htim);
    HAL_TIM_PWM_Init(htim);
    HAL_TIM_PWM_Start(htim, pwm_channel_init);

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, pwm_channel_init);
    HAL_TIM_MspPostInit(htim);
}


void motor_init(Motor motor){

	GPIO_InitTypeDef GPIO_InitStruct = {0};
switch(motor)
{
case MOTOR_A:
	Init_PWM_Timer(MOTOR_A_TIM,TIM2, 4, 255, MOTOR_A_CHANNEL);

    // Configure direction control pins
	GPIO_InitStruct.Pin = MOTOR_A_IN1_PIN| MOTOR_A_IN2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(MOTOR_A_IN1_PORT, &GPIO_InitStruct);
	HAL_GPIO_Init(MOTOR_A_IN2_PORT, &GPIO_InitStruct);



    HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_RESET);
    break;
case MOTOR_B:
	Init_PWM_Timer(MOTOR_B_TIM,TIM2, 4, 255, MOTOR_B_CHANNEL);
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// Configure direction control pins
	GPIO_InitStruct.Pin = MOTOR_B_IN1_PIN| MOTOR_B_IN2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(MOTOR_B_IN1_PORT, &GPIO_InitStruct);
	HAL_GPIO_Init(MOTOR_B_IN2_PORT, &GPIO_InitStruct);



	HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_RESET);


}
}

void motor_set_speed(Motor motor,uint8_t speed) {
    switch (motor)
    {
            case MOTOR_A:
            	__HAL_TIM_SET_COMPARE(MOTOR_A_TIM, MOTOR_A_CHANNEL, speed);
            	break;
            case MOTOR_B:
            	 __HAL_TIM_SET_COMPARE(MOTOR_B_TIM, MOTOR_B_CHANNEL, speed);
            	 break;

    }
}

void motor_set_direction(Motor motor,MotorDirection direction) {
    if (motor == MOTOR_A){
	switch (direction)
		{
        case MOTOR_DIRECTION_FORWARD:
            HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_SET);
            break;
        case MOTOR_DIRECTION_BACKWARD:
            HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_RESET);
            break;
		}
    }
    if (motor == MOTOR_B)
    {
    	switch (direction)
    		{
            case MOTOR_DIRECTION_FORWARD:
                HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_SET);
                break;
            case MOTOR_DIRECTION_BACKWARD:
                HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_SET);
                HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_RESET);
                break;
    		}
    }

}

void motor_stop(void){
	HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(MOTOR_A_TIM, MOTOR_A_CHANNEL, 0);
	HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(MOTOR_B_TIM, MOTOR_B_CHANNEL, 0);
}
void motor_forward(uint8_t speed){

	HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(MOTOR_A_TIM, MOTOR_A_CHANNEL, speed);
	HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(MOTOR_B_TIM, MOTOR_B_CHANNEL, speed);
}
void motor_reverse(uint8_t speed){
	HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(MOTOR_A_TIM, MOTOR_A_CHANNEL, speed);
	HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(MOTOR_B_TIM, MOTOR_B_CHANNEL, speed);

}
void motor_right(uint8_t speed){
	HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(MOTOR_A_TIM, MOTOR_A_CHANNEL, speed);
	HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(MOTOR_B_TIM, MOTOR_B_CHANNEL, speed);

}
void motor_left(uint8_t speed){
	HAL_GPIO_WritePin(MOTOR_A_IN1_PORT, MOTOR_A_IN1_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTOR_A_IN2_PORT, MOTOR_A_IN2_PIN, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(MOTOR_A_TIM, MOTOR_A_CHANNEL, speed);
	HAL_GPIO_WritePin(MOTOR_B_IN1_PORT, MOTOR_B_IN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTOR_B_IN2_PORT, MOTOR_B_IN2_PIN, GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(MOTOR_B_TIM, MOTOR_B_CHANNEL, speed);


}
