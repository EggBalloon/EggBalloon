/*
 * Adc.c
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#include "AdcTemp.h"


uint32_t gAdcValue=0;
uint32_t gBatteryLevel=0;

static uint8_t ADC0_Cal(void);
static void Adc_StartBatteryConv(void);

void Adc_Init(void)
{
	uint8_t bCalibration;
	
	bCalibration=ADC0_Cal();
	if(bCalibration==0){
		/*Configure ADC module to read internal temp sensor*/
		ADC0_SC1A=ADC_SC1_ADCH(SENSOR_CHANNEL);
		ADC0_SC1B=0;
		ADC0_CFG1= ADC_CFG1_ADIV(3) | ADC_CFG1_MODE(3)|ADC_CFG1_ADICLK(0);
		ADC0_SC2 &=  ~ADC_SC2_ADTRG_MASK;
		ADC0_SC3 &=  ~ADC_SC3_ADCO_MASK;
		ADC0_SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(1));
		
	}else{
		/*Calibration failed*/
		asm("nop");
	}
}

void Adc_DeInit(void)
{
	ADC0_SC1A=ADC_SC1_ADCH(MODULE_DISABLED);
}

void Adc_StartGroupConv(void)
{
	/*Start Conversion*/
	ADC0_SC1A=ADC_SC1_ADCH(SENSOR_CHANNEL);
	/*Wait for the conversion*/
	while ((ADC0_SC2 & ADC_SC2_ADACT_MASK));
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));
	/*Store conversion in global variable to be reported by Adc_ReadGroup()*/
	gAdcValue=ADC0_RA;
	Adc_StartBatteryConv();
}

void Adc_StartBatteryConv(void)
{
	/*Start Conversion*/
	ADC0_SC1A=ADC_SC1_ADCH(VREFH_CHANNEL);
	/*Wait for the conversion*/
	while ((ADC0_SC2 & ADC_SC2_ADACT_MASK));
	while (!(ADC0_SC1A & ADC_SC1_COCO_MASK));
	/*Store conversion in global variable to be reported by Adc_ReadGroup()*/
	gBatteryLevel=ADC0_RA;
}

uint32_t Adc_ReadGroup(void)
{	
	return gAdcValue;
}

/******************************************************************************
Function 1. Name AUTO CAL ROUTINE  
Parameters  ADC module pointer points to adc0 or adc1 register map 
                         base address.
Returns   Zero indicates success.
Notes           Calibrates the ADC16. Required to meet specifications 
                        after reset and before a conversion is initiated.
******************************************************************************/
uint8_t ADC0_Cal(void)
{
  uint8_t cal_var;
  
  SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
  
  ADC0_SC2 &=  ~ADC_SC2_ADTRG_MASK ; /* Enable Software Conversion Trigger for Calibration Process */ 
  ADC0_SC3 &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); // set single conversion, clear avgs bitfield for next writing
  ADC0_SC3 |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3));  // Turn averaging ON and set at max value ( 32 )
  
  
  ADC0_SC3 |= ADC_SC3_CAL_MASK;      // Start CAL
  while (!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Wait calibration end
   
  if (ADC0_SC3 & ADC_SC3_CALF_MASK)
  {  
   return(1);    /* Calibration failed*/ 
  }
  else{
	  /*Calibration Success */	  
   return (0);
  }
} 
 
 

