/*
 * buttons.c
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#include "buttons.h"

struct ButtonStruct button0 =
{
	{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE},//keyBuffer
	500,//timeOutForPressed = 500 * 20 ms = 10s
	0,//isPressed
	0,//isLongPressed
	BUTTON0_GPIO_Port,
	BUTTON0_Pin
};

struct ButtonStruct button1 =
{
	{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE},// keyBuffer
	500,//timeOutForPressed = 500 * 20 ms = 10s
	0,//isPressed
	0,//isLongPressed
	BUTTON1_GPIO_Port,
	BUTTON1_Pin
};

struct ButtonStruct button2 =
{
	{NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, NORMAL_STATE}, //keyBuffer
	500,//timeOutForPressed = 500 * 20 ms = 10s
	0,//isPressed
	0,//isLongPressed
	BUTTON2_GPIO_Port,
	BUTTON2_Pin
};

void getKeyInput(struct ButtonStruct* button)
{
	button->keyBuffer[2] = button->keyBuffer[1];
	button->keyBuffer[1] = button->keyBuffer[0];

	button->keyBuffer[0] = HAL_GPIO_ReadPin(button->PORT, button->PIN);

	if ((button->keyBuffer[0] == button->keyBuffer[1]) && (button->keyBuffer[1] == button->keyBuffer[2]))
	{
		if (button->keyBuffer[2] != button->keyBuffer[3])
		{
			button->keyBuffer[3] = button->keyBuffer[2];

			if (button->keyBuffer[3] == PRESSED_STATE)
			{
				button->timeOutForPressed = LONG_PRESSED / 20;//read button
				button->isPressed = 1;
			}
		}
		else //button->keyBuffer[2] == button->keyBuffer[3]
		{
			button->timeOutForPressed--;
			if (button->timeOutForPressed <= 0)
			{
				button->timeOutForPressed = LONG_PRESSED / 20;//read button
				if (button->keyBuffer[3] == PRESSED_STATE)
				{
					button->isLongPress = 1;
				}
			}
		}
	}
}

int isButtonPressed(struct ButtonStruct* button)
{
	if (button->isPressed == 1)
	{
		button->isPressed = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(struct ButtonStruct* button)
{
	if (button->isLongPress == 1)
	{
		button->isLongPress = 0;
		return 1;
	}
	return 0;
}

void resetButton(struct ButtonStruct* button)
{
	button->isPressed = 0;
	button->isLongPress = 0;
}

