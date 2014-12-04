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

#define DIO21	(0x1500)
#define DIO22	(0x1600)
#define DIO26 	(0x1A00)


uint32_t Analog_Read(void);

void Digital_Write(uint16_t ChannelID, uint16_t value);

uint8_t Digital_Read(uint16_t ChannelID, uint16_t value);


#endif /* IO_INTERFACE_H_ */
