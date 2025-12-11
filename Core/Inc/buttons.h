/*
 * buttons.h
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include "main.h"

struct ButtonStruct
{
	int keyBuffer[4]; // New data in [0], old data in [2]
	int timeOutForPressed; //ms
	int isPressed;
	int isLongPress;
	GPIO_TypeDef *PORT;
	uint16_t PIN;
};

extern struct ButtonStruct button0;
extern struct ButtonStruct button1;
extern struct ButtonStruct button2;

void getKeyInput(struct ButtonStruct* button);
int isButtonPressed(struct ButtonStruct* button);
int isButtonLongPressed(struct ButtonStruct* button);
void resetButton(struct ButtonStruct* button);

#endif /* INC_BUTTONS_H_ */
