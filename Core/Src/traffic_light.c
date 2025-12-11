/*
 * traffic_light.c
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#include "traffic_light.h"

enum TrafficLightState TRAFFIC_LIGHT_STATE = INIT;

void fsm_traffic_light()
{
	switch(TRAFFIC_LIGHT_STATE){
		case INIT:
				//change state
			if (1) // -> AUTO_RED_GREEN
			{
				init_auto_red_green();
				TRAFFIC_LIGHT_STATE = AUTO_RED_GREEN;
			}
			break;
		case AUTO_RED_GREEN:
			auto_red_green();
			if (IsTimeExpired(TIMER_TRAFFIC_LIGHT)) // -> AUTO_RED_AMBER
			{
				init_auto_red_amber();
				TRAFFIC_LIGHT_STATE = AUTO_RED_AMBER;
			}
//			else if (isButtonPressed(&button0)) // -> RED_TIME_CONFIG
//			{
//				init_red_time_config();
//				TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
//			}
			break;
		case AUTO_RED_AMBER:
			auto_red_amber();
			if (IsTimeExpired(TIMER_TRAFFIC_LIGHT)) // -> AUTO_GREEN_RED
			{
				init_auto_green_red();
				TRAFFIC_LIGHT_STATE = AUTO_GREEN_RED;
			}
//				else if (isButtonPressed(&button0)) // -> RED_TIME_CONFIG
//				{
//					init_red_time_config();
//					TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
//				}
				break;
			case AUTO_GREEN_RED:
				auto_green_red();

				if (IsTimeExpired(TIMER_TRAFFIC_LIGHT)) // -> AUTO_AMBER_RED
				{
					init_auto_amber_red();
					TRAFFIC_LIGHT_STATE = AUTO_AMBER_RED;
				}
//				else if (isButtonPressed(&button0)) // -> RED_TIME_CONFIG
//				{
//					init_red_time_config();
//					TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
//				}
				break;
			case AUTO_AMBER_RED:
				auto_amber_red();

				if (IsTimeExpired(TIMER_TRAFFIC_LIGHT)) // -> AUTO_RED_GREEN
				{
					init_auto_red_green();
					TRAFFIC_LIGHT_STATE = AUTO_RED_GREEN;
				}
//				else if (isButtonPressed(&button0)) // -> RED_TIME_CONFIG
//				{
//					init_red_time_config();
//					TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
//				}
				break;
			default:
				break;

	}
}

void turn_on_red_green()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

	HAL_GPIO_WritePin(LED3_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED2_Pin, LED_OFF);
}

void turn_on_red_amber()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

	HAL_GPIO_WritePin(LED3_GPIO_Port, LED1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED2_Pin, LED_ON);
}

void turn_on_green_red()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_OFF);

	HAL_GPIO_WritePin(LED3_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED2_Pin, LED_ON);
}

void turn_on_amber_red()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_OFF);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

	HAL_GPIO_WritePin(LED3_GPIO_Port, LED1_Pin, LED_ON);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED2_Pin, LED_ON);
}
//cài đặt trạng thái
void init_auto_red_green() {
    setTimer(TIMER_TRAFFIC_LIGHT, green_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    resetButton(&button2);
    // OTHER PRECONDITIONS
    setTimer(TIMER_7SEG, TIME_7SEG);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = red_time;
    counter_way1 = green_time;
}
//trạng thái
void auto_red_green() {
    if (1) {
        turn_on_red_green();
    }
    if (IsTimeExpired(TIMER_7SEG)) {
        lcd_display(counter_way0, counter_way1);
        setTimer(TIMER_7SEG, TIME_7SEG);
    }
    if (IsTimeExpired(TIMER_1S)) {
        counter_way0--;
        counter_way1--;
        setTimer(TIMER_1S, TIME_1S);
    }
}
//cài đặt trạng thái
void init_auto_red_amber() {
    setTimer(TIMER_TRAFFIC_LIGHT, amber_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    // OTHER PRECONDITIONS
    setTimer(TIMER_7SEG, TIME_7SEG);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = amber_time;
    counter_way1 = amber_time;
}

void auto_red_amber() {
    if (1) {
        turn_on_red_amber();
    }
    if (IsTimeExpired(TIMER_7SEG)) {
    	lcd_display(counter_way0, counter_way1);
        setTimer(TIMER_7SEG, TIME_7SEG);
    }
    if (IsTimeExpired(TIMER_1S)) {
        counter_way0--;
        counter_way1--;
        setTimer(TIMER_1S, TIME_1S);
    }
}
//cài đặt trạng thái
void init_auto_green_red() {
    setTimer(TIMER_TRAFFIC_LIGHT, green_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    resetButton(&button2);
    // OTHER PRECONDITIONS
    setTimer(TIMER_7SEG, TIME_7SEG);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = green_time;
    counter_way1 = red_time;
}

void auto_green_red() {
    if (1) {
        turn_on_green_red();
    }
    if (IsTimeExpired(TIMER_7SEG)) {
    	lcd_display(counter_way0, counter_way1);
        setTimer(TIMER_7SEG, TIME_7SEG);
    }
    if (IsTimeExpired(TIMER_1S)) {
        counter_way0--;
        counter_way1--;
        setTimer(TIMER_1S, TIME_1S);
    }
}
//cài đặt trạng thái
void init_auto_amber_red() {
    setTimer(TIMER_TRAFFIC_LIGHT, amber_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    // OTHER PRECONDITIONS
    setTimer(TIMER_7SEG, TIME_7SEG);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = amber_time;
    counter_way1 = amber_time;
}

void auto_amber_red() {
    if (1) {
        turn_on_amber_red();
    }
    if (IsTimeExpired(TIMER_7SEG)) {
    	lcd_display(counter_way0, counter_way1);
        setTimer(TIMER_7SEG, TIME_7SEG);
    }
    if (IsTimeExpired(TIMER_1S)) {
        counter_way0--;
        counter_way1--;
        setTimer(TIMER_1S, TIME_1S);
    }
}
