#include "motorDriver.h"

TIM_HandleTypeDef *htim_pwm;
GPIO_TypeDef *port_dir1, *port_dir2;
uint16_t pin_dir1, pin_dir2;
uint32_t pwm_channel;

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


void motor_init(TIM_HandleTypeDef *htim_pwm_init,TIM_TypeDef *timerInstance, uint32_t pwm_channel_init, GPIO_TypeDef *port_dir1_init, uint16_t pin_dir1_init, GPIO_TypeDef *port_dir2_init, uint16_t pin_dir2_init) {
    htim_pwm = htim_pwm_init;
    port_dir1 = port_dir1_init;
    pin_dir1 = pin_dir1_init;
    port_dir2 = port_dir2_init;
    pin_dir2 = pin_dir2_init;
    pwm_channel =pwm_channel_init;

    Init_PWM_Timer(htim_pwm,timerInstance, 4, 255, pwm_channel);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // Configure direction control pins
	GPIO_InitStruct.Pin = pin_dir1_init | pin_dir2_init;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(port_dir1_init, &GPIO_InitStruct);
	HAL_GPIO_Init(port_dir2_init, &GPIO_InitStruct);



    HAL_GPIO_WritePin(port_dir1, pin_dir1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port_dir2, pin_dir2, GPIO_PIN_RESET);
}

void motor_set_speed(uint16_t speed) {
    __HAL_TIM_SET_COMPARE(htim_pwm, pwm_channel, speed);
//	TIM2->CCR2=speed;
}

void motor_set_direction(MotorDirection direction) {
    switch (direction) {
        case MOTOR_DIRECTION_FORWARD:
            HAL_GPIO_WritePin(port_dir1, pin_dir1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(port_dir2, pin_dir2, GPIO_PIN_SET);
            break;
        case MOTOR_DIRECTION_BACKWARD:
            HAL_GPIO_WritePin(port_dir1, pin_dir1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(port_dir2, pin_dir2, GPIO_PIN_RESET);
            break;
    }
}
