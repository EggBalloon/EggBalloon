/*
 * Pwm.h
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#ifndef PWM_H_
#define PWM_H_

#include "MK64F12.h"

void vfnFTMEdgeAligned (uint32_t u32Period, uint32_t u32Duty);
void Pwm_Init(void);
void Pwm_DeInit(void);
void Pwm_SetDutyCycle(void);


#endif /* PWM_H_ */
