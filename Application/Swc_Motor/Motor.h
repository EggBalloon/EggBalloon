/*
 * Motor.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "IO_Interface.h"

void FAN_InitMotorCntrl(void);

void FAN_DeInitMotorCntrl(void);

void FAN_SetMotorDirection(void);

void FAN_GetMotorDirection(void);

void FAN_MotorSpeed(void);

void FAN_GetMotorSpeed(void);

#endif /* MOTOR_H_ */
