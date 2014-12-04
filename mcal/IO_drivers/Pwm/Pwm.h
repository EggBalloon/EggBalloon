/*
 * Pwm.h
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#ifndef PWM_H_
#define PWM_H_

#include "MK64F12.h"
#include "Pwm_Cfg.c"


void Pwm_Init(const Pwm_ConfigType* FtmConfig);
void Pwm_DeInit(void);
void Pwm_SetDutyCycle(Pwm_ChannelType enChannelNumber, uint16_t DutyCycle);


#endif /* PWM_H_ */
