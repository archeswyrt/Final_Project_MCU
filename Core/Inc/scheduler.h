/*
 * scheduler.h
 *
 *  Created on: Dec 11, 2025
 *      Author: DELL
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"

typedef struct
{
	// Pointer to the task (must be a "void (void)" function)
	void (*pTask)(void);
	// Delay (ticks) until the function will (next) be run
	uint32_t Delay;
	// Interval (ticks) between subsequent runs
	uint32_t Period;
	// Incremented (by scheduler) when task is due to execute
	uint8_t RunMe;
	// Save the ID of the task. In this LAB, this will be the index in task List
	uint32_t TaskID;

} sTask;

// MUST BE ADJUSTED FOR EACH PROJECT
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

#define ERROR_INIT 0
#define ERROR_SCH_EXCEED_MAX_TASK 1
#define ERROR_SCH_EMPTY_LIST_CAN_NOT_REMOVED 2
#define ERROR_SCH_EMPTY_LIST_CAN_NOT_DELETE 3

struct Node
{
	sTask data;
	int32_t next;
};

extern struct Node SCH_task_G[SCH_MAX_TASKS];


void List_resetNodeData(int32_t index);//set Null
void initFreeList();
void List_init();
int32_t List_getFreeIndex();//find index
void List_freeIndex(int32_t index);
uint8_t List_isEmpty();

void List_insertNode(int32_t freeIndex);//delay timer
void List_popHead();//remove node in head

void SCH_Init(void);
void SCH_Update(void);
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(uint32_t taskID);
void SCH_Report_Status();
void SCH_Go_To_Sleep();

#endif /* INC_SCHEDULER_H_ */
