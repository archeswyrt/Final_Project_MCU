/*
 * tasks.c
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */
#include "tasks.h"

void blinkyLED()
{
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

void getButtons()
{
	getKeyInput(&button0);
	getKeyInput(&button1);
	getKeyInput(&button2);
}

void fsm()
{
	fsm_traffic_light();
}
