/*
 * Adc.h
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#ifndef ADC_H_
#define ADC_H_

#include "MK64F12.h"

#define SENSOR_CHANNEL 		26
#define VREFH_CHANNEL 		29
#define MODULE_DISABLED 	0x1F

extern uint32_t gAdcValue;
extern uint32_t gBatteryLevel;

void Adc_Init(void);
void Adc_DeInit(void);
void Adc_StartGroupConv(void);
uint32_t Adc_ReadGroup(void);

#endif /* ADC_H_ */
