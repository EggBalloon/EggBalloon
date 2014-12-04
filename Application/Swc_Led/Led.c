/*
 * Led.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Led.h"
#include "IO_Interface.h"

#define	LEDS_RED_MSK	(0x01)
#define	LEDS_GREEN_MSK	(0x02)
#define	LEDS_BLUE_MSK	(0x04)

static LWGPIO_VALUE enRed	= PORT_OFF;
static LWGPIO_VALUE enGreen	= PORT_OFF;
static LWGPIO_VALUE enBlue	= PORT_OFF;
static bool LED__boToggle	= FALSE; 

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

	Digital_Write(enPORTB | DIO21,enBlue);
	Digital_Write(enPORTB | DIO22,enRed);
	Digital_Write(enPORTB | DIO26,enGreen);	
}

void Led_vToggle(void)
{
	if(FALSE == LED__boToggle)
	{
		LED__boToggle = TRUE;
		Digital_Write(enPORTB | DIO21,enBlue);
		Digital_Write(enPORTB | DIO22,enRed);
		Digital_Write(enPORTB | DIO26,enGreen);
	}
	else
	{
		LED__boToggle = FALSE;
		Digital_Write(enPORTB | DIO21,PORT_OFF);
		Digital_Write(enPORTB | DIO22,PORT_OFF);
		Digital_Write(enPORTB | DIO26,PORT_OFF);
	}
}
