/*
 * Motor_Cfg.h
 *
 *  Created on: Nov 16, 2014
 *      Author: Esteban
 */
#include "Motor_Types.h"

#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

typedef struct{
	uint16_t		u16MtrSpeed;
	tenMotorID		enMotorID;
	tenMotorDir		enMtrDirection;
}tstMotorStatus;

#endif /* MOTOR_CFG_H_ */
