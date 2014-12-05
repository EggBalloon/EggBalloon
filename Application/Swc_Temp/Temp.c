/*
 * Temp.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Temp.h"



int32_t Temp_Read(void)
{
/*	int32_t temperature;
	int64_t Vtemp_mV, tempOffset;
	int32_t intTempInmC;
	uint32_t adcValue;
	

	adcValue = Analog_Read();
	Vtemp_mV=((VREF*adcValue)/65536);
	tempOffset = (((Vtemp_mV -(uint32_t)VTEMP25_ADC))/M1);
	intTempInmC = 25000 - tempOffset;
	
	temperature = (intTempInmC)/1000;

	return temperature;*/
	
		int32_t currentTemperature = 0;
	    int64_t Vadc=0;
	    uint32_t adcValue;
	    
	    adcValue = Analog_Read();
	    Vadc  = (int64_t)adcValue - (int64_t)(V_TEMP25 * ADC_MAX_SCALE)/V_REFH; //(M1 - (adcValue - VTEMP25_ADC) * M2)*592;
	    Vadc *= 100000UL;
	    Vadc *= V_REFH;
	    Vadc /= ADC_TEMP_SLOPE;
	    Vadc /= ADC_MAX_SCALE;
	    currentTemperature = 2500U - (int32_t)Vadc;
	    currentTemperature -= TEMP_OFFSET;
	    
	    return currentTemperature;
}
