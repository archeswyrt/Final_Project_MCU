/*
 * scheduler.c
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#include "scheduler.h"

struct Node SCH_task_G[SCH_MAX_TASKS];
int32_t head = -1;
int32_t freeHead = 0;
uint32_t Error_code_G = ERROR_INIT;

void List_resetNodeData(int32_t index)
{
	SCH_task_G[index].data.pTask = NULL;
	SCH_task_G[index].data.Delay = 0;
	SCH_task_G[index].data.Period = 0;
	SCH_task_G[index].data.RunMe = 0;
	SCH_task_G[index].data.TaskID = 0;
}

void initFreeList()
{
	for(int i = 0; i < SCH_MAX_TASKS - 1; ++i)
	{
		SCH_task_G[i].next = i + 1;
	}
	SCH_task_G[SCH_MAX_TASKS - 1].next = -1;
}

void List_init()
{
	head = -1;
	freeHead = 0;
	initFreeList();
}

int32_t List_getFreeIndex()
{
	if(freeHead == -1)
	{
		return -1;
	}
	int32_t freeIndex = freeHead;
	freeHead = SCH_task_G[freeHead].next;

	return freeIndex;
}

void List_freeIndex(int32_t index)
{
    if(index < 0 || index >= SCH_MAX_TASKS)
    {
        Error_code_G = ERROR_SCH_EMPTY_LIST_CAN_NOT_DELETE;
        return;
    }

	List_resetNodeData(index);
	SCH_task_G[index].next = freeHead;
	freeHead = index;
}

uint8_t List_isEmpty()
{
	return head == -1;
}

void List_insertNode(int32_t freeIndex)
{
	if(head == -1)//insert at head
	{
		//delay=0 => run task
		if(SCH_task_G[freeIndex].data.Delay == 0)
		{
			SCH_task_G[freeIndex].data.RunMe = 1;
		}

		head = freeIndex;
		SCH_task_G[head].next = -1;
		return;
	}
	//insert into index
	int32_t current = head;
	int32_t previous = -1;
	while(current != -1)
	{
		if(SCH_task_G[current].data.Delay > SCH_task_G[freeIndex].data.Delay)//insert next current
		{
			if(SCH_task_G[freeIndex].data.Delay == 0)
			{
				SCH_task_G[freeIndex].data.RunMe = 1;
			}

			SCH_task_G[freeIndex].next = current;
			if(previous == -1)
			{
				head = freeIndex;
			}
			else
			{
				SCH_task_G[previous].next = freeIndex;
			}
			//The task behind need to minus by the new task delay
			SCH_task_G[current].data.Delay -= SCH_task_G[freeIndex].data.Delay;
			if(SCH_task_G[current].data.Delay == 0)
			{
				SCH_task_G[current].data.RunMe = 1;
			}
			return;
		}
		//check on index, minus delay
		SCH_task_G[freeIndex].data.Delay -= SCH_task_G[current].data.Delay;
		previous = current;
		current = SCH_task_G[current].next;
	}

	//insert to tail, current = -1
	if(SCH_task_G[freeIndex].data.Delay == 0)//dispatch
	{
		SCH_task_G[freeIndex].data.RunMe = 1;
	}
	SCH_task_G[previous].next = freeIndex;
	SCH_task_G[freeIndex].next = -1;
}

void List_popHead()
{
	if(head == -1)
	{
		Error_code_G = ERROR_SCH_EMPTY_LIST_CAN_NOT_REMOVED;
		return;
	}
	head = SCH_task_G[head].next;
}

void SCH_Init(void)
{
	List_init();
	Error_code_G = ERROR_INIT;
}

void SCH_Update(void)
{
	if(List_isEmpty())
	{
		return;
	}

	if(SCH_task_G[head].data.Delay > 0)
	{
		SCH_task_G[head].data.Delay--;
	}

	if(SCH_task_G[head].data.Delay == 0)
	{
		SCH_task_G[head].data.RunMe = 1;
	}
}

void SCH_Dispatch_Tasks(void)
{
	if(List_isEmpty())
	{
		return;
	}

	int32_t current = head;
	if(SCH_task_G[current].data.RunMe == 1)
	{
		SCH_task_G[current].data.pTask();
		SCH_task_G[current].data.RunMe = 0;

		int32_t deleted = current;
		List_popHead();
		if(head == -1) return; //empty list

		if(Error_code_G == ERROR_SCH_EMPTY_LIST_CAN_NOT_REMOVED)
		{
		    return; //avoid crash
		}
		if(SCH_task_G[deleted].data.Period == 0)
		{
			List_freeIndex(deleted);
		}
		else
		{
			SCH_task_G[deleted].data.Delay = SCH_task_G[deleted].data.Period;
			List_insertNode(deleted);
		}
	}
	//check status
	SCH_Report_Status();

	if(SCH_task_G[current].data.RunMe == 0)
	{
		SCH_Go_To_Sleep();
	}
}
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	int32_t freeIndex = List_getFreeIndex();
	if(freeIndex == -1)
	{
		Error_code_G = ERROR_SCH_EXCEED_MAX_TASK;
		return UINT32_MAX;
	}
	//assign data to freeIndex
	SCH_task_G[freeIndex].data.pTask = pFunction;
	SCH_task_G[freeIndex].data.Delay = DELAY;
	SCH_task_G[freeIndex].data.Period = PERIOD;
	SCH_task_G[freeIndex].data.RunMe = 0;
	SCH_task_G[freeIndex].data.TaskID = freeIndex;

	List_insertNode(freeIndex);
	return freeIndex; //return task ID
}
uint8_t SCH_Delete_Task(uint32_t taskID)
{
	if(List_isEmpty())
	{
		Error_code_G = ERROR_SCH_EMPTY_LIST_CAN_NOT_DELETE;
		return 0;
	}

	int current = head;
	int previous = -1;
	while(current != -1)
	{
		if(SCH_task_G[current].data.TaskID == taskID)//find index
		{
			if(previous == -1) //remove head
			{
				if(SCH_task_G[current].next != -1) //check not tail
				{
					//Modify the Delay of the behind task
					SCH_task_G[SCH_task_G[current].next].data.Delay += SCH_task_G[current].data.Delay;
					if (SCH_task_G[SCH_task_G[current].next].data.Delay != 0)
					{
						SCH_task_G[SCH_task_G[current].next].data.RunMe = 0;
					}
				}
				List_popHead();
				List_freeIndex(current);
			}
			else//no remove at head
			{
				if(SCH_task_G[current].next != -1) // IF NOT TAIL
				{
					//Modify the Delay of the behind task
					SCH_task_G[SCH_task_G[current].next].data.Delay += SCH_task_G[current].data.Delay;
					if(SCH_task_G[SCH_task_G[current].next].data.Delay != 0)
					{
						SCH_task_G[SCH_task_G[current].next].data.RunMe = 0;
					}
				}
				SCH_task_G[previous].next = SCH_task_G[current].next;
				List_resetNodeData(current);
				List_freeIndex(current);
			}
			return 0;
		}
		//continue
		previous = current;
		current = SCH_task_G[current].next;
	}
	return 0;
}
void SCH_Report_Status()
{
	//handle error
	//...
	Error_code_G = ERROR_INIT;
}
void SCH_Go_To_Sleep()
{
	//sleep mode
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	//After an ISR is execute: Exit sleep Mode
	HAL_ResumeTick();
}

