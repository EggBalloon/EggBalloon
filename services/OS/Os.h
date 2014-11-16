/*
 * Os.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef OS_H_
#define OS_H_

#include "mqx.h"

#define TD_STRUCT_PTR void *

void Gpt_Init(void);

void Gpt_EnableNotification(void);

void Gpt_StopTimer(void);

void Gpt_StartTimer(void);

uint32_t OS_CreateTask(uint16_t processor, uint32_t index, uint32_t parameters);

uint32_t OS_CreateTaskBlocked(uint16_t processor, uint32_t index, uint32_t parameters);

void OS_BlockTask(void);

uint32_t  OS_TaskDestroy(uint32_t TaskID);

#endif /* OS_H_ */
