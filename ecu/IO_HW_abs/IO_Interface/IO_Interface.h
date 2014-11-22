/*
 * IO_Interface.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef IO_INTERFACE_H_
#define IO_INTERFACE_H_

#include "AdcTemp.h"
#include "Dio.h"
#include "Pwm.h"

#define PWM_MASK 		0x10
#define FLAGS_MASK 		0x00FF

typedef enum
{
	enPWM1=0,
	enPWM2,
	enPWM3,
	enPWM4,
	enPWM5,
}Pwm_tenPwm;

#define DIO0	(0x0100)
#define DIO1	(0x0200)
#define DIO2	(0x0300)
#define DIO3	(0x0400)
#define DIO4	(0x0500)
#define DIO5	(0x0600)
#define DIO6	(0x0700)
#define DIO7	(0x0800)
#define DIO8	(0x0900)
#define DIO9	(0x0A00)
#define DIO10 	(0x0B00)
#define DIO11 	(0x0C00)
#define DIO12 	(0x0D00)
#define DIO13 	(0x0E00)
#define DIO14 	(0x0F00)
#define DIO15 	(0x1000)
#define DIO16	(0x1100)
#define DIO17	(0x1200)
#define DIO18	(0x1300)
#define DIO19	(0x1400)
#define DIO20	(0x1500)
#define DIO21	(0x1600)
#define DIO22	(0x1700)
#define DIO23	(0x1800)
#define DIO24	(0x1900)
#define DIO25	(0x2000)
#define DIO26 	(0x2100)
#define DIO27 	(0x2200)
#define DIO28 	(0x2300)
#define DIO29 	(0x2400)
#define DIO30 	(0x2500)
#define DIO31 	(0x2600)

uint32_t Analog_Read(void);

void Digital_Write(uint16_t ChannelID, uint16_t value);

uint8_t Digital_Read(uint16_t ChannelID, uint16_t value);


#endif /* IO_INTERFACE_H_ */
