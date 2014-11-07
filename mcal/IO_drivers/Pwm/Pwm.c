/*
 * Pwm.c
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#include "Pwm.h"

void vfnFTMEdgeAligned (uint32_t u32Period, uint32_t u32Duty)
{
                SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK; /* Enable clock for FTM0 */
 
                PORTC_PCR1 = PORT_PCR_MUX(0x4)  ;
 
                FTM0_MOD = u32Period; /* PWM period */
               
                /* Configure timers for edge aligned PWM High True Pulses */
               
                FTM0_C0SC = 0x28; /* No Interrupts; High True pulses on Edge Aligned PWM */
                               
               
                FTM0_C0V = u32Duty; /* 50% pulse width */  
                               
               
                FTM0_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
}

void Pwm_Init(void)
{
	

}

void Pwm_DeInit(void)
{
	

}

void Pwm_SetDutyCycle(void)
{
	

}
