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

uint32_t OS_CreateTask(uint16_t processor, uint32_t index, uint32_t parameters, uint8_t blocked)
{
	uint32_t result;
	if(1==blocked)
	{
		result=_task_create_blocked(processor, index, parameters);
	}else{
		result=_task_create(processor, index, parameters);
	}
	return result;
}

void OS_BlockTask(void)
{
	_task_block();
}

void OS_Delay(uint32_t delay)
{
	_time_delay(delay);
}


