/*
 * Os.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Os.h"

void Gpt_Init(void)
{
	
}

void Gpt_EnableNotification(void)
{
	
}

void Gpt_StopTimer(void)
{
	
}

void Gpt_StartTimer(void)
{
	
}

uint32_t OS_CreateTask(uint16_t processor, uint32_t index, uint32_t parameters)
{
	return _task_create(processor, index, parameters);
}

uint32_t OS_CreateTaskBlocked(uint16_t processor, uint32_t index, uint32_t parameters)
{
	return _task_create_blocked(processor, index, parameters);
}

void OS_BlockTask(void)
{
	_task_block();
}

uint32_t  OS_TaskDestroy(uint32_t TaskID)
{
	return _task_destroy(TaskID);
}


