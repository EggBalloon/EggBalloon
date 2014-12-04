/*
 * Motor_Types.h
 *
 *  Created on: Nov 16, 2014
 *      Author: Esteban
 */
#include "IO_Interface.h" 

#ifndef MOTOR_TYPES_H_
#define MOTOR_TYPES_H_


typedef enum{
	MOTORA,
	MOTORB,
	MOTOREL,
	MaxNumOfMotors
}tenMotorID;

typedef enum{
	CW = 0,
	CCW,
	NoDirection
}tenMotorDir;

#define ChannelMask(IDChannel)	(IDChannel|PWM_MASK)

#endif /* MOTOR_TYPES_H_ */
