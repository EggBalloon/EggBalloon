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

void Analog_Read(void);

void Digital_Write(void);

void Digital_Read(void);


#endif /* IO_INTERFACE_H_ */
