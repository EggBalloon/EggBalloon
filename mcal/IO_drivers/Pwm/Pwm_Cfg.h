/*
 * Pwm_Cfg.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Esteban
 */
#include "Pwm_Types.h"
#include "mqx.h"

#ifndef PWM_CFG_H_
#define PWM_CFG_H_

typedef struct{
	tenFlxTmr		enFlxTimerID;		/* Flex Timer ID */
	Pwm_ChannelType  enPwmChannel;     	/* Pwm Channel ID */
	uint8_t			u8PwmAlignIntCfg;	/* Set the PWM Aligning and Interrupts Configuration */
	uint16_t      	u16PwmDuty;        	/* Duty Cycle */   
}tstPwm_Settings;

typedef struct{
	uint8_t                     u8NumOfChannel;     /* Number of Ports */
	const tstPwm_Settings*    pstPwm_Settings;    /* Pointer to Port Settings */
}Pwm_ConfigType;

extern const Pwm_ConfigType pwmConfig;


#endif /* PWM_CFG_H_ */
