/*
 * Led.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef LED_H_
#define LED_H_

#include <mqx.h>
#include <bsp.h>
#include <fio.h>

typedef enum _tenLedColors
{
	enLedColorOff=0,
	enLedColorRed,
	enLedColorGreen,
	enLedColorYellow,
	enLedColorBlue,
	enLedColorMagenta,
	enLedColorCyan,
	enLedColorWhite,
	enLedColorError	
}LED_tenLedColors;

void Led_vSetColor(LED_tenLedColors enColor);

void Led_vToggle(void);

#endif /* LED_H_ */
