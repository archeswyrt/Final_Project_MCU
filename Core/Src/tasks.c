/*
 * tasks.c
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */
#include "tasks.h"

void BlinkyLed()
{
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}
//void msg1()
//{
//	//HAL_UART_Transmit(&huart2, (void*) str, sprintf(str, "!Hello world#"), 500);
//	lcd_goto_XY(1, 0);
//	lcd_send_string("Anh nho Tuyet");
//	lcd_goto_XY(2, 0);
//	lcd_send_string("nhieu lam");
//}
void turn_red()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);
}

void turn_amber()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);
}

void turn_green()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_OFF);
}

void getButtons()
{
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);
}
void testbutton0()
{
	if(isButtonPressed(&button0)){
		turn_red();
	}else if(isButtonLongPressed(&button0)){
		turn_green();
	}
}
void testbutton1()
{
	if(isButtonPressed(&button1)){
		turn_amber();
	}
}
void testbutton2()
{
	if(isButtonPressed(&button2)){
		turn_green();
	}
}

void fsm()
{
	fsm_traffic_light();
}

