/*
 * app.c
 *
 *  Created on: Mar 16, 2024
 *      Author: abosa
 */

#include "app.h"

uint16_t frontFlag, front_rightFlag, front_leftFlag,back_rightFlag, back_leftFlag ,backFlag ,motorSpeed;
UART_HandleTypeDef huart6;
uint8_t speed =200;

void app_init(void){
	HAL_Init();
	motor_init(MOTOR_A);
	motor_init(MOTOR_B);
	ultraSonic_Init();
	MX_USART6_UART_Init();
}
 void MX_USART6_UART_Init(void)
{

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

}


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

uint32_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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

void ACC(void){
// Read distances from ultrasonic sensors
	int frontDistance 	  = ultraSonic_readDistance(TRIG_1_PORT, TRIG_1_PIN, Echo1_GPIO_Port,Echo1_Pin, &htim1);

  // Constrain filtered distance within a valid range
  frontDistance = constrain(frontDistance, 0, 100);

  printf("front Distance: %d\n\r", frontDistance );

  // Check if obstacles are too close in front
  if (frontDistance < MIN_WARNING_DISTANCE) {
    // Stop the motors if obstacles are too close
    motor_stop();
    printf("Stop\n\r");
  } else {
    // Adjust motor speeds based on filtered distance
    adjustMotors(frontDistance);
  }
}

void adjustMotors(uint16_t distance){
	uint16_t motorSpeed=0;
	// Function to adjust motor speeds based on distances
	  motorSpeed = map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, 255);
	  motorSpeed = motorSpeed * 2;
	  motorSpeed = constrain(motorSpeed, 0, 255);  // Adjust motor speed scale
	  printf("motor Speed: %d \n \r ", motorSpeed);

	  motor_forward(motorSpeed);
	  printf("Forward\n \r");
}
void app_start(void){
	//	  	  int frontDistance 	 = ultraSonic_readDistance(TRIG_2_PORT, TRIG_2_PIN, Echo2_GPIO_Port,Echo2_Pin, &htim2);
	//
	//	  	  printf("Distance: %d \n\r",frontDistance);
	//	  	  HAL_Delay(500);
	//	  if (flag ==0){
	//	  motor_set_direction(MOTOR_A, 1);
	//	  motor_set_direction(MOTOR_B, 1);
	//	  motor_set_speed(MOTOR_A, speed);
	//	  motor_set_speed(MOTOR_B, speed);
	////	  TIM2->CCR2=speed;
	//	  speed+=20;
	//	  HAL_Delay(1000);
	//	  if (speed>255){
	//		  speed =0;
	//		  flag =1;
	//	  }
	//	  }
	//	  else {
	//		  motor_set_direction(MOTOR_A, 0);
	//		  	  motor_set_direction(MOTOR_B, 0);
	//		  	  motor_set_speed(MOTOR_A, speed);
	//		  	  motor_set_speed(MOTOR_B, speed);
	//		  //	  TIM2->CCR2=speed;
	//		  	  speed+=20;
	//		  	  HAL_Delay(1000);
	//		  	  if (speed>255){
	//		  		  speed =0;
	//		  		  flag =0;
	//		  	  }
	//	  }
	//	  TIM2->CCR2=100;
	//	  speed+=20;
	//	  HAL_Delay(1000);

		  motor_forward(speed);
		  printf("forward\n\r");
		  HAL_Delay(3000);
		  motor_stop();
		  printf("stop \n\r");
		  HAL_Delay(1000);
		  motor_reverse(speed);
		  printf("reverse \n\r");
		  HAL_Delay(3000);
		  motor_stop();
		  printf("stop \n\r");
		  HAL_Delay(1000);
		  motor_left(speed);
		  printf("left \n\r");
		  HAL_Delay(3000);
		  motor_stop();
		  printf("stop \n\r");
		  HAL_Delay(1000);
		  motor_right(speed);
		  printf("right \n\r");
		  HAL_Delay(3000);
		  motor_stop();
		  printf("stop \n\r");
		  HAL_Delay(1000);





}
