/*
 * Motor.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Motor.h"


static tstMotorStatus stCurrentMtrStatus[MaxNumOfMotors];

void FAN_InitMotorCntrl(void)
{
	for(uint8_t indx = 0; indx<MaxNumChannels; indx++)
	{
		Digital_Write(ChannelMask(indx),0);  /* Initialize Duty Cycle to 0% for all channels configured */
		
	}
}

void FAN_DeInitMotorCntrl(void)
{
	for(uint8_t indx = 0; indx<MaxNumChannels; indx++)
	{
		Digital_Write(ChannelMask(indx),0);  /* Initialize Duty Cycle to 0% for all channels configured */
	}
}

void FAN_SetMotorDirection(tenMotorID MotorID, tenMotorDir Direction, uint16_t u16Speed)
{
	switch(MotorID){
		case MOTORA:{
			if(Direction) /* Set Motor Direction CCW */
			{
				Digital_Write(ChannelMask(CHANNEL0),0); 		/* Channel 0 for Motor A */
				Digital_Write(ChannelMask(CHANNEL1),u16Speed);  /* Channel 1 for Motor A */
			}	
			else /* Set Motor Direction CW */
			{
				
				Digital_Write(ChannelMask(CHANNEL0), u16Speed);	/* Channel 0 for Motor A */
				Digital_Write(ChannelMask(CHANNEL1), 0);		/* Channel 1 for Motor A */				
			}	
			stCurrentMtrStatus[MOTORA].enMotorID = MOTORA;
			stCurrentMtrStatus[MOTORA].u16MtrSpeed = u16Speed;
			stCurrentMtrStatus[MOTORA].enMtrDirection = Direction;
		}break;
		case MOTORB:{
			if(Direction) /* Set Motor Direction CCW */
			{
				Digital_Write(ChannelMask(CHANNEL2), 0);		/* Channel 2 for Motor B */
				Digital_Write(ChannelMask(CHANNEL3), u16Speed);	/* Channel 3 for Motor B */
			}	
			else /* Set Motor Direction CW */
			{
				Digital_Write(ChannelMask(CHANNEL2), u16Speed);	/* Channel 2 for Motor B */
				Digital_Write(ChannelMask(CHANNEL3), 0);		/* Channel 3 for Motor B */
			}	
			stCurrentMtrStatus[MOTORB].enMotorID = MOTORB;
			stCurrentMtrStatus[MOTORB].u16MtrSpeed = u16Speed;
			stCurrentMtrStatus[MOTORB].enMtrDirection = Direction;
		}break;		
		default:{/* Do nothing */}break;
	}
}

tenMotorDir FAN_GetMotorDirection(tenMotorID MotorID)
{
	return stCurrentMtrStatus[MotorID].enMtrDirection;
}

void FAN_SetMotorSpeed(tenMotorID MotorID, uint16_t u16Speed)
{
	tenMotorDir CurrDirection = FAN_GetMotorDirection(MotorID);
	
	switch(MotorID)
	{
		case MOTORA:{
			if(CurrDirection) /* Set Motor Direction CCW */
			{
				Digital_Write(ChannelMask(CHANNEL0), 0);		/* Channel 0 for Motor A */
				Digital_Write(ChannelMask(CHANNEL1), u16Speed);	/* Channel 1 for Motor A */				
			}	
			else /* Set Motor Direction CW */
			{
				Digital_Write(ChannelMask(CHANNEL0), u16Speed);	/* Channel 0 for Motor A */
				Digital_Write(ChannelMask(CHANNEL1), 0);		/* Channel 1 for Motor A */				
			}	
			stCurrentMtrStatus[MOTORA].enMotorID = MOTORA;
			stCurrentMtrStatus[MOTORA].u16MtrSpeed = u16Speed;				
			}break;
		case MOTORB:{
			if(CurrDirection) /* Set Motor Direction CCW */
			{
				Digital_Write(ChannelMask(CHANNEL2), 0);		/* Channel 2 for Motor B */
				Digital_Write(ChannelMask(CHANNEL3), u16Speed);	/* Channel 3 for Motor B */
			}	
			else /* Set Motor Direction CW */
			{
				Digital_Write(ChannelMask(CHANNEL2), u16Speed);	/* Channel 2 for Motor B */
				Digital_Write(ChannelMask(CHANNEL3), 0);		/* Channel 3 for Motor B */
			}	
			stCurrentMtrStatus[MOTORB].enMotorID = MOTORB;
			stCurrentMtrStatus[MOTORB].u16MtrSpeed = u16Speed;				
			}break;	
		case MOTOREL:{
			Digital_Write(ChannelMask(CHANNEL6), u16Speed);	/* Channel 6 for Elevation Motor */
			stCurrentMtrStatus[MOTOREL].enMotorID = MOTOREL;
			stCurrentMtrStatus[MOTOREL].u16MtrSpeed = u16Speed;
		}break;
		default:{/* Do nothing */}break;
	}
}

uint16_t FAN_GetMotorSpeed(tenMotorID MotorID)
{
	return stCurrentMtrStatus[MotorID].u16MtrSpeed;
}
