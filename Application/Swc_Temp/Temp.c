/*
 * Temp.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Temp.h"

int32_t Temp_Read(void)
{
	int32_t temperature;
	int64_t Vtemp_mV, tempOffset;
	int32_t intTempInmC;
	uint32_t adcValue;
	

	adcValue = Analog_Read();
	Vtemp_mV=((VREF*adcValue)/65536);
	tempOffset = (((Vtemp_mV -(uint32_t)VTEMP25_ADC))/M1);
	intTempInmC = 25000 - tempOffset;
	
	temperature = (intTempInmC)/1000;

	return temperature;
}
