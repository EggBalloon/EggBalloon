/*
 * Adc.h
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#ifndef ADC_H_
#define ADC_H_

#include "MK64F12.h"

void Adc_Init(void);
void Adc_DeInit(void);
void Adc_StartGroupConv(void);
void Adc_ReadGroup(void);

#endif /* ADC_H_ */
