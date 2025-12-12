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
    switch (TRAFFIC_LIGHT_STATE)
    {
    case INIT:
        if (1)
        {
            init_auto_red_green();
            TRAFFIC_LIGHT_STATE = AUTO_RED_GREEN;
        }
        break;
    case AUTO_RED_GREEN:
        auto_red_green();
        if (IsTimeExpired(TIMER_TRAFFIC_LIGHT))
        {
            init_auto_red_amber();
            TRAFFIC_LIGHT_STATE = AUTO_RED_AMBER;
        }
		else if (isButtonPressed(&button0))
		{
			init_red_time_config();
			TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
		}
		else if (isButtonPressed(&button1))
		{
			TRAFFIC_LIGHT_STATE = MANUAL_RED_GREEN;
			init_manual_red_green();
		}
        break;
    case AUTO_RED_AMBER:
        auto_red_amber();
        if (IsTimeExpired(TIMER_TRAFFIC_LIGHT))
        {
            init_auto_green_red();
            TRAFFIC_LIGHT_STATE = AUTO_GREEN_RED;
        }
		else if (isButtonPressed(&button0))
		{
			init_red_time_config();
			TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
		}
		else if (isButtonPressed(&button1))
		{
			TRAFFIC_LIGHT_STATE = MANUAL_RED_GREEN;
			init_manual_red_green();
		}
        break;
    case AUTO_GREEN_RED:
        auto_green_red();

        if (IsTimeExpired(TIMER_TRAFFIC_LIGHT))
        {
            init_auto_amber_red();
            TRAFFIC_LIGHT_STATE = AUTO_AMBER_RED;
        }
		else if (isButtonPressed(&button0))
		{
			init_red_time_config();
			TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
		}
		else if (isButtonPressed(&button1))
		{
			TRAFFIC_LIGHT_STATE = MANUAL_RED_GREEN;
			init_manual_red_green();
		}
        break;
    case AUTO_AMBER_RED:
        auto_amber_red();

        if (IsTimeExpired(TIMER_TRAFFIC_LIGHT))
        {
            init_auto_red_green();
            TRAFFIC_LIGHT_STATE = AUTO_RED_GREEN;
        }
		else if (isButtonPressed(&button0))
		{
			init_red_time_config();
			TRAFFIC_LIGHT_STATE = RED_TIME_CONFIG;
		}
		else if (isButtonPressed(&button1))
		{
			TRAFFIC_LIGHT_STATE = MANUAL_RED_GREEN;
			init_manual_red_green();
		}
        break;
	case RED_TIME_CONFIG:
		red_time_config();
		if (isButtonPressed(&button0))
		{
			init_amber_time_config();
			TRAFFIC_LIGHT_STATE = AMBER_TIME_CONFIG;
		}
		break;
	case AMBER_TIME_CONFIG:
		amber_time_config();
		if (isButtonPressed(&button0))
		{
			init_green_time_config();
			TRAFFIC_LIGHT_STATE = GREEN_TIME_CONFIG;
		}
		break;
	case GREEN_TIME_CONFIG:
		green_time_config();
		if (isButtonPressed(&button0))
		{
			init_auto_red_green();
			TRAFFIC_LIGHT_STATE = AUTO_RED_GREEN;
		}
		break;
	case MANUAL_RED_GREEN:
		manual_red_green();
		if (isButtonPressed(&button0))
		{
			TRAFFIC_LIGHT_STATE = AUTO_RED_GREEN;
			init_auto_red_green();
		}
		break;
	case MANUAL_RED_AMBER:
		manual_red_amber();
		if (isButtonPressed(&button0))
		{
			TRAFFIC_LIGHT_STATE = AUTO_RED_AMBER;
			init_auto_red_amber();
		}
		break;
	case MANUAL_GREEN_RED:
		manual_green_red();
		if (isButtonPressed(&button0))
		{
			TRAFFIC_LIGHT_STATE = AUTO_GREEN_RED;
			init_auto_green_red();
		}
		break;
	case MANUAL_AMBER_RED:
		manual_amber_red();
		if (isButtonPressed(&button0))
		{
			TRAFFIC_LIGHT_STATE = AUTO_AMBER_RED;
			init_auto_amber_red();
		}
		break;
	default:
        break;
    }
}

void turn_on_red()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_ON);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_ON);
}

void turn_on_amber()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_ON);
}

void turn_on_green()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_OFF);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_ON);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_OFF);
}

void turn_on_red_green()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_ON);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_OFF);
}

void turn_on_red_amber()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_ON);
}

void turn_on_green_red()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_OFF);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_ON);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_ON);
}

void turn_on_amber_red()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_OFF);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);

    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_ON);
    HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_ON);
}

void init_auto_red_green()
{
    setTimer(TIMER_TRAFFIC_LIGHT, green_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    resetButton(&button2);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = red_time;
    counter_way1 = green_time;
    lcd_auto_mode("RED  ", counter_way0, "GREEN", counter_way1);
}

void auto_red_green()
{
    if (1)
    {
        turn_on_red_green();
    }

    if (IsTimeExpired(TIMER_1S))
    {
        counter_way0--;
        counter_way1--;
        lcd_auto_mode("RED  ", counter_way0, "GREEN", counter_way1);
        setTimer(TIMER_1S, TIME_1S);
    }
}

void init_auto_red_amber()
{
    setTimer(TIMER_TRAFFIC_LIGHT, amber_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    resetButton(&button2);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = amber_time;
    counter_way1 = amber_time;
    lcd_auto_mode("RED  ", counter_way0, "AMBER", counter_way1);
}

void auto_red_amber()
{
    if (1)
    {
        turn_on_red_amber();
    }

    if (IsTimeExpired(TIMER_1S))
    {
        counter_way0--;
        counter_way1--;
        lcd_auto_mode("RED  ", counter_way0, "AMBER", counter_way1);
        setTimer(TIMER_1S, TIME_1S);
    }
}

void init_auto_green_red()
{
    setTimer(TIMER_TRAFFIC_LIGHT, green_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    resetButton(&button2);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = green_time;
    counter_way1 = red_time;
    lcd_auto_mode("GREEN", counter_way0, "RED  ", counter_way1);
}

void auto_green_red()
{
    if (1)
    {
        turn_on_green_red();
    }

    if (IsTimeExpired(TIMER_1S))
    {
        counter_way0--;
        counter_way1--;
        lcd_auto_mode("GREEN", counter_way0, "RED  ", counter_way1);
        setTimer(TIMER_1S, TIME_1S);
    }
}

void init_auto_amber_red()
{
    setTimer(TIMER_TRAFFIC_LIGHT, amber_time * 100);
    resetButton(&button0);
    resetButton(&button1);
    resetButton(&button2);
    setTimer(TIMER_1S, TIME_1S);
    counter_way0 = amber_time;
    counter_way1 = amber_time;
    lcd_auto_mode("AMBER", counter_way0, "RED  ", counter_way1);
}

void auto_amber_red()
{
    if (1)
    {
        turn_on_amber_red();
    }

    if (IsTimeExpired(TIMER_1S))
    {
        counter_way0--;
        counter_way1--;
        lcd_auto_mode("AMBER", counter_way0, "RED  ", counter_way1);
        setTimer(TIMER_1S, TIME_1S);
    }
}

void init_red_time_config()
{
	red_temp_time = red_time;
	turn_on_red();
	lcd_config_mode("RED  ", red_temp_time);
}

void red_time_config()
{
	int isChanged = 0;

	if (isButtonPressed(&button1))
	{
		red_temp_time++;
		if (red_temp_time > 99)
		{
			red_temp_time = 1;
		}
		isChanged = 1;
	}

	if (isButtonLongPressed(&button1))
	{
		red_temp_time += 5;
		if (red_temp_time > 99)
		{
			red_temp_time = 1;
		}
		isChanged = 1;
	}

	if (isChanged)
	{
		lcd_config_mode("RED  ", red_temp_time);
	}

	if (isButtonPressed(&button2))
	{
		if (red_temp_time > amber_time)
		{
			red_time = red_temp_time;
			green_time = red_time - amber_time;
		}
	}
}

void init_amber_time_config()
{
	amber_temp_time = amber_time;
	turn_on_amber();
	lcd_config_mode("AMBER", amber_temp_time);
}

void amber_time_config()
{
	int isChanged = 0;

	if (isButtonPressed(&button1))
	{
		amber_temp_time++;
		if (amber_temp_time > 99)
		{
			amber_temp_time = 1;
		}
		isChanged = 1;
	}

	if (isButtonLongPressed(&button1))
	{
		amber_temp_time += 5;
		if (amber_temp_time > 99)
		{
			amber_temp_time = 1;
		}
		isChanged = 1;
	}

	if (isChanged)
	{
		lcd_config_mode("AMBER", amber_temp_time);
	}

	if (isButtonPressed(&button2))
	{
		if (red_time > amber_temp_time)
		{
			amber_time = amber_temp_time;
			green_time = red_time - amber_time;
		}
	}
}

void init_green_time_config()
{
	green_temp_time = green_time;
	turn_on_green();
	lcd_config_mode("GREEN", green_temp_time);
}

void green_time_config()
{
	int isChanged = 0;

	if (isButtonPressed(&button1))
	{
		green_temp_time++;
		if (green_temp_time > 99)
		{
			green_temp_time = 1;
		}
		isChanged = 1;
	}

	if (isButtonLongPressed(&button1))
	{
		green_temp_time += 5;
		if (green_temp_time > 99)
		{
			green_temp_time = 1;
		}
		isChanged = 1;
	}

	if (isChanged)
	{
		lcd_config_mode("GREEN", green_temp_time);
	}

	if (isButtonPressed(&button2))
	{
		green_time = green_temp_time;
		red_time = green_time + amber_time;
	}
}

void init_manual_red_green()
{
	turn_on_red_green();
	lcd_manual_mode("1:RED_2:GREEN");
}

void manual_red_green()
{
	if (isButtonPressed(&button1))
	{
		TRAFFIC_LIGHT_STATE = MANUAL_RED_AMBER;
		init_manual_red_amber();
	}
}

void init_manual_red_amber()
{
	turn_on_red_amber();
	lcd_manual_mode("1:RED_2:AMBER");
}

void manual_red_amber()
{
	if (isButtonPressed(&button1))
	{
		TRAFFIC_LIGHT_STATE = MANUAL_GREEN_RED;
		init_manual_green_red();
	}
}

void init_manual_green_red()
{
	turn_on_green_red();
	lcd_manual_mode("1:GREEN_2:RED");
}

void manual_green_red()
{
	if (isButtonPressed(&button1))
	{
		TRAFFIC_LIGHT_STATE = MANUAL_AMBER_RED;
		init_manual_amber_red();
	}
}

void init_manual_amber_red()
{
	turn_on_amber_red();
	lcd_manual_mode("1:AMBER_2:RED");
}

void manual_amber_red()
{
	if (isButtonPressed(&button1))
	{
		TRAFFIC_LIGHT_STATE = MANUAL_RED_GREEN;
		init_manual_red_green();
	}
}






























