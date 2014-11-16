/*
 * Pwm_Types.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Esteban
 */
#include "mqx.h"

#ifndef PWM_TYPES_H_
#define PWM_TYPES_H_

typedef enum {
  CHANNEL0,
  CHANNEL1,
  CHANNEL2,
  CHANNEL3,
  CHANNEL4,
  CHANNEL5,
  CHANNEL6,
  CHANNEL7,
  MaxNumChannels
}Pwm_ChannelType;

typedef enum{
	FlxTmr0,
	FlxTmr1,
	FlxTmr2,
	FlxTmr3,
	MaxFlxTmrs
}tenFlxTmr;

#define WPDIS_ENABLE		FTM_MODE_WPDIS_MASK
#define WPDIS_DISABLE		0u
#define FTM_ENABLE			FTM_MODE_FTMEN_MASK
#define FTM_DISABLE			0u
#define FTM_Period			0x1D3 /* Fixed Duty Cycle to 1KHz*/

#define SIM_SCGC(u8FlxTmr)		SIM_SCGC##u8FlxTmr##_FTM##u8FlxTmr##_MASK

#endif /* PWM_TYPES_H_ */
