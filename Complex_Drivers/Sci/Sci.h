/*
 * Sci.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef SCI_H_
#define SCI_H_

#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include "MK64F12.h"

typedef enum
{
	enSciErrNull=0x8000,
	enSciErrNoInit,
	enSciErrNoData,
	enSciErrOvRun,
}SCI_tenErrorCodes;

void Sci_Init(void);

void Sci_DeInit(void);

uint16_t Sci_Read(uint8_t *pu8Buffer,uint16_t u16DataLen);

uint16_t Sci_Write(uint8_t *pu8Buffer,uint16_t u16DataLen);

#endif /* SCI_H_ */
