/*
 * global.h
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

//LED SETTING
#define LED_ON 1
#define LED_OFF 0

//BUTTON SETTING
#define NORMAL_STATE 1
#define PRESSED_STATE 0
#define LONG_PRESSED 500 //ms

//TRAFFIC SETTING
#define MIN_COUNTER 1
#define MAX_COUNTER 99

extern int counter_way0;
extern int counter_way1;

extern int red_time;
extern int amber_time;
extern int green_time;

extern int red_temp_time;
extern int amber_temp_time;
extern int green_temp_time;

//Timer
#define TIMER_7SEG 2
#define TIME_7SEG 2
#define TIMER_1S 3
#define TIME_1S 100
#define TIMER_7SEG_STATUS 4
#define TIME_7SEG_STATUS 250
#define TIMER_250MS 5
#define TIME_250MS 250
#define TIMER_TRAFFIC_LIGHT 6

#endif /* INC_GLOBAL_H_ */
