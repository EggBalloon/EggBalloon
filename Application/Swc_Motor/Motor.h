/*
 * Motor.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "IO_Interface.h"
#include "Pwm_Types.h"
#include "Motor_Types.h"
#include "Motor_Cfg.h"
#include "mqx.h"

#define BASESPEED (FTM_Period*0.80)
#define SYSBASESPEED	(FTM_Period*0.60)
#define SYSMAXSPEED	(FTM_Period*0.95)
void FAN_InitMotorCntrl(void);

void FAN_DeInitMotorCntrl(void);

void FAN_SetMotorDirection(tenMotorID MotorID, tenMotorDir Direction, uint16_t u16Speed);

tenMotorDir FAN_GetMotorDirection(tenMotorID MotorID);

void FAN_SetMotorSpeed(tenMotorID MotorID, uint16_t u16Speed);

uint16_t FAN_GetMotorSpeed(tenMotorID MotorID);

#endif /* MOTOR_H_ */
