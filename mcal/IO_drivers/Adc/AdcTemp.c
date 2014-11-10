/*
 * Adc.c
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#include "AdcTemp.h"

void Adc_Init(void)
{
	ADC0_SC1A=0;	
	
}

void Adc_DeInit(void)
{
	
}

void Adc_StartGroupConv(void)
{
	
}

uint32_t Adc_ReadGroup(void)
{
	uint32_t temp;
	
	temp++;
	
	return temp;
}
