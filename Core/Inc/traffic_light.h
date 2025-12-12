/*
 * traffic_light.h
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"

enum TrafficLightState
{
	INIT,
	AUTO_RED_GREEN,
	AUTO_RED_AMBER,
	AUTO_GREEN_RED,
	AUTO_AMBER_RED,
	RED_TIME_CONFIG,
	AMBER_TIME_CONFIG,
	GREEN_TIME_CONFIG,
	MANUAL_RED_GREEN,
	MANUAL_RED_AMBER,
	MANUAL_GREEN_RED,
	MANUAL_AMBER_RED
};

void fsm_traffic_light();

void turn_on_red_green();
void turn_on_red_amber();
void turn_on_green_red();
void turn_on_amber_red();

void init_auto_red_green();
void auto_red_green();

void init_auto_red_amber();
void auto_red_amber();

void init_auto_green_red();
void auto_green_red();

void init_auto_amber_red();
void auto_amber_red();

void init_red_time_config();
void red_time_config();

void init_amber_time_config();
void amber_time_config();

void init_green_time_config();
void green_time_config();

void init_manual_red_green();
void manual_red_green();

void init_manual_red_amber();
void manual_red_amber();

void init_manual_green_red();
void manual_green_red();

void init_manual_amber_red();
void manual_amber_red();

#endif /* INC_TRAFFIC_LIGHT_H_ */
