/*
 * Led.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Led.h"
#include "Dio.h"

#define	LEDS_RED_MSK	(0x01)
#define	LEDS_GREEN_MSK	(0x02)
#define	LEDS_BLUE_MSK	(0x04)

static LWGPIO_VALUE enRed;
static LWGPIO_VALUE enGreen;
static LWGPIO_VALUE enBlue;
static bool LED__boToggle=FALSE; 

void Led_vSetColor(LED_tenLedColors enColor)
{

	if( (enColor != enLedColorOff) && (enColor < enLedColorError) )
	{
		/********** RED LED **********/ 
		if(enColor&LEDS_RED_MSK)
		{	enRed = PORT_ON;}
		else
		{	enRed = PORT_OFF;}
		/********* GREEN LED *********/
		if(enColor&LEDS_GREEN_MSK)
		{	enGreen = PORT_ON;}
		else
		{	enGreen = PORT_OFF;}
		/********* BLUE LED **********/
		if(enColor&LEDS_BLUE_MSK)
		{	enBlue = PORT_ON;}
		else
		{	enBlue = PORT_OFF;}
		
		LED__boToggle = TRUE;/*At least one color was set*/
	}
	else
	{
		/* ALL LEDs off */
		enRed   = PORT_OFF;
		enGreen = PORT_OFF;
		enBlue  = PORT_OFF;
		LED__boToggle = FALSE;/*All colors OFF*/
	}

	Dio_SetPin(enPORTB,PIN21,(uint8_t)enBlue);
	Dio_SetPin(enPORTB,PIN22,(uint8_t)enRed);
	Dio_SetPin(enPORTB,PIN26,(uint8_t)enGreen);	
}

void Led_vToggle(void)
{
	if(FALSE == LED__boToggle)
	{
		LED__boToggle = TRUE;
		Dio_SetPin(enPORTB,PIN21,(uint8_t)enBlue);
		Dio_SetPin(enPORTB,PIN22,(uint8_t)enRed);
		Dio_SetPin(enPORTB,PIN26,(uint8_t)enGreen);
	}
	else
	{
		LED__boToggle = FALSE;
		Dio_SetPin(enPORTB,PIN21,(uint8_t)PORT_OFF);
		Dio_SetPin(enPORTB,PIN22,(uint8_t)PORT_OFF);
		Dio_SetPin(enPORTB,PIN26,(uint8_t)PORT_OFF);
	}
}
