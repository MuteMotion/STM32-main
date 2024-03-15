/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  *************
**/
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart6;
//TIM_HandleTypeDef htim2;
/* USER CODE BEGIN PV */
#define MAX_WARNING_DISTANCE 300  // Adjust as needed
#define MIN_WARNING_DISTANCE 100
int frontFlag, front_rightFlag, front_leftFlag,back_rightFlag, back_leftFlag ,backFlag ,motorSpeed;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_USART6_UART_Init(void);

/* USER CODE BEGIN PFP */
void collisionWarning(void);
uint32_t constrain(uint32_t value, uint32_t min, uint32_t max);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
//  MX_GPIO_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
//  ultraSonic_Init();
//  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  motor_init(MOTOR_A);
  motor_init(MOTOR_B);

  ultraSonic_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
int speed=0,flag=0;
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
//  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  	  int frontDistance 	 = ultraSonic_readDistance(TRIG_2_PORT, TRIG_2_PIN, Echo2_GPIO_Port,Echo2_Pin, &htim2);
//
//	  	  printf("Distance: %d \n\r",frontDistance);
//	  	  HAL_Delay(500);
	  if (flag ==0){
	  motor_set_direction(MOTOR_A, 1);
	  motor_set_direction(MOTOR_B, 1);
	  motor_set_speed(MOTOR_A, speed);
	  motor_set_speed(MOTOR_B, speed);
//	  TIM2->CCR2=speed;
	  speed+=20;
	  HAL_Delay(1000);
	  if (speed>255){
		  speed =0;
		  flag =1;
	  }
	  }
	  else {
		  motor_set_direction(MOTOR_A, 0);
		  	  motor_set_direction(MOTOR_B, 0);
		  	  motor_set_speed(MOTOR_A, speed);
		  	  motor_set_speed(MOTOR_B, speed);
		  //	  TIM2->CCR2=speed;
		  	  speed+=20;
		  	  HAL_Delay(1000);
		  	  if (speed>255){
		  		  speed =0;
		  		  flag =0;
		  	  }
	  }
//	  TIM2->CCR2=100;
//	  speed+=20;
//	  HAL_Delay(1000);

  }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

/* USER CODE BEGIN 4 */
int __io_putchar(int ch){

	  /* Place your implementation of fputc here */
	  /* e.g. write a character to the USART1 and Loop until the end of transmission */
	  HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, 0xFFFF);
	  return ch;
}
uint32_t constrain(uint32_t value, uint32_t min, uint32_t max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

void collisionWarning(void){

	  int frontDistance 	  = ultraSonic_readDistance(TRIG_1_PORT, TRIG_1_PIN, Echo1_GPIO_Port,Echo1_Pin, &htim1);
	  int front_leftDistance  = ultraSonic_readDistance(TRIG_2_PORT, TRIG_2_PIN, Echo2_GPIO_Port,Echo2_Pin, &htim2);
	  int front_rightDistance = ultraSonic_readDistance(TRIG_3_PORT, TRIG_3_PIN, Echo3_GPIO_Port,Echo3_Pin, &htim3);
	  int backDistance 	  	  = ultraSonic_readDistance(TRIG_4_PORT, TRIG_4_PIN, Echo4_GPIO_Port,Echo4_Pin, &htim4);
	  int back_leftDistance   = ultraSonic_readDistance(TRIG_5_PORT, TRIG_5_PIN, Echo5_GPIO_Port,Echo5_Pin, &htim5);
	  int back_rightDistance  = ultraSonic_readDistance(TRIG_6_PORT, TRIG_6_PIN, Echo6_GPIO_Port,Echo6_Pin, &htim9);

	  frontDistance = constrain(frontDistance, 0, 100);
	  front_leftDistance = constrain(front_leftDistance, 0, 100);
	  front_rightDistance = constrain(front_rightDistance, 0, 100);
	  backDistance = constrain(backDistance, 0, 100);
	  back_leftDistance = constrain(back_leftDistance, 0, 100);
	  back_rightDistance = constrain(back_rightDistance, 0, 100);

	  if (frontDistance <= MIN_WARNING_DISTANCE) {
	    printf("frontFlag= 2 \n\r");

	    frontFlag = 2;
	  } else if (frontDistance <= MAX_WARNING_DISTANCE) {
		printf("frontFlag=1\n\r");

	    frontFlag = 1;
	  } else {
		printf("frontFlag=0\n\r");

	    frontFlag = 0;
	  }
	  // Add code here to trigger warning (e.g., activate a buzzer, LED, etc.)


	  if (front_leftDistance <= MIN_WARNING_DISTANCE) {
		printf("leftFlag=2 \n\r");

	    front_leftFlag = 2;
	  } else if (front_leftDistance <= MAX_WARNING_DISTANCE) {
		printf("front_leftFlag= 1 \n\r ");

	    front_leftFlag = 1;
	  } else {
		printf("front_leftFlag=0\n\r");

		front_leftFlag = 0;
	  }
	  // Add code here to trigger warning (e.g., activate a buzzer, LED, etc.)

	  if (front_rightDistance <= MIN_WARNING_DISTANCE) {
		printf("front_rightFlag=2\n\r");

		front_rightFlag = 2;
	  } else if (front_rightDistance <= MAX_WARNING_DISTANCE) {
		printf("front_rightFlag=1\n\r");

		front_rightFlag = 1;
	  } else {
		printf("front_rightFlag=0\n\r");

		front_rightFlag = 0;
	  }
	  if (backDistance <= MIN_WARNING_DISTANCE) {
	    printf("backFlag= 2 \n\r");

	    backFlag = 2;
	  } else if (backDistance <= MAX_WARNING_DISTANCE) {
		printf("backFlag=1\n\r");

		backFlag = 1;
	  } else {
		printf("backFlag=0\n\r");

		backFlag = 0;
	  }
	  // Add code here to trigger warning (e.g., activate a buzzer, LED, etc.)


	  if (back_leftDistance <= MIN_WARNING_DISTANCE) {
		printf("back_leftFlag=2 \n\r");

		back_leftFlag = 2;
	  } else if (back_leftDistance <= MAX_WARNING_DISTANCE) {
		printf("back_leftFlag= 1 \n\r ");

		back_leftFlag = 1;
	  } else {
		printf("back_leftFlag=0\n\r");

		back_leftFlag = 0;
	  }
	  // Add code here to trigger warning (e.g., activate a buzzer, LED, etc.)

	  if (back_rightDistance <= MIN_WARNING_DISTANCE) {
		printf("back_rightFlag=2\n\r");

		back_rightFlag = 2;
	  } else if (back_rightDistance <= MAX_WARNING_DISTANCE) {
		printf("back_rightFlag=1\n\r");

		back_rightFlag = 1;
	  } else {
		printf("back_rightFlag=0\n\r");

		back_rightFlag = 0;
	  }


}




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
