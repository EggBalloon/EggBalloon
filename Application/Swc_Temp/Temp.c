/*
 * Temp.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Temp.h"

uint32_t gTemperatureValue;

uint32_t Temp_Read(void)
{
	uint32_t temperature;
	uint32_t adcValue;

	adcValue = Analog_Read();
	
	temperature = (M1 - (adcValue - VTEMP25_ADC) * 583)/K;

	return temperature;
}
