/*
 * software_timer.h
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#define MAX_TIMER 10

extern int timer_counter[MAX_TIMER];
extern int timer_flag[MAX_TIMER];

void setTimer(int index, int duration);
void timerRun();
int IsTimeExpired(int index);

#endif /* INC_SOFTWARE_TIMER_H_ */
