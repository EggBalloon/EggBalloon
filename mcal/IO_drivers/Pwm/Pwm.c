/*
 * Pwm.c
 *
 *  Created on: Oct 29, 2014
 *      Author: Miguel
 */

#include "Pwm.h"


void Pwm_Init(const Pwm_ConfigType* FtmConfig)
{
	for(uint8_t i=0;i<(FtmConfig->u8NumOfChannel); i++)
	{			
		switch(FtmConfig->pstPwm_Settings[i].enFlxTimerID)
		{
			case 0:	{}break;
			case 1:	{}break;
			case 2:	{}break;
			case 3:
			{
				SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK; /* Enable clock for FTM3 */
				/*FTM0_MODE[WPDIS] = 1; Disable Write Protection - enables changes to QUADEN, DECAPEN */  
				FTM3_MODE |= FTM_MODE_WPDIS_MASK;
				/* FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0 */
				FTM3_MODE |= FTM_MODE_FTMEN_MASK;
				/* QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)*/
				FTM3_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;
				FTM3_CNT = 0x0; /* FTM Counter Value - reset counter to zero */
				FTM3_MOD = FTM_Period;	/* Set Fixed Period 0x1D3 -> 1KHz*/ 
				FTM3_CNTIN = 0; /* Set the Counter Initial Value to 0 */
				/* Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately */
				FTM3_SC = 0; /* Make sure its Off! */
				
				switch(FtmConfig->pstPwm_Settings[i].enPwmChannel)
				{
					case 0:
					{
						PORTD_PCR0 = PORT_PCR_MUX(0x4);						
						FTM3_C0SC = FtmConfig->pstPwm_Settings[i].u8PwmAlignIntCfg;
						FTM3_C0V = FtmConfig->pstPwm_Settings[i].u16PwmDuty;
						FTM3_COMBINE = 0x0;
						FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
						FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
						FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
					}break;
					case 1:
					{
						PORTD_PCR1 = PORT_PCR_MUX(0x4);
						FTM3_C1SC = FtmConfig->pstPwm_Settings[i].u8PwmAlignIntCfg;
						FTM3_C1V = FtmConfig->pstPwm_Settings[i].u16PwmDuty;
						FTM3_COMBINE = 0x0;
						FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
						FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
						FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
					}break;
					case 2:
					{	
						PORTD_PCR2= PORT_PCR_MUX(0x4);
						FTM3_C2SC = FtmConfig->pstPwm_Settings[i].u8PwmAlignIntCfg;
						FTM3_C2V = FtmConfig->pstPwm_Settings[i].u16PwmDuty;
						FTM3_COMBINE = 0x0;
						FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
						FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
						FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
					}break;
					case 3:
					{	
						PORTD_PCR3 = PORT_PCR_MUX(0x4);
						FTM3_C3SC = FtmConfig->pstPwm_Settings[i].u8PwmAlignIntCfg;
						FTM3_C3V = FtmConfig->pstPwm_Settings[i].u16PwmDuty;
						FTM3_COMBINE = 0x0;
						FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
						FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
						FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
					}break;
					case 6:
					{	
						PORTC_PCR10 = PORT_PCR_MUX(0x3);
						FTM3_C6SC = FtmConfig->pstPwm_Settings[i].u8PwmAlignIntCfg;
						FTM3_C6V = FtmConfig->pstPwm_Settings[i].u16PwmDuty;
						FTM3_COMBINE = 0x0;
						FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
						FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
						FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
					}break;
					default: {}break;								
				}
			}break;		
			default:{}break;
		}
		
	}
	
}

void Pwm_DeInit(void)
{	
	SIM_SCGC3 = 0; /* Enable clock for FTM3 */
	/*FTM0_MODE[WPDIS] = 1; Disable Write Protection - enables changes to QUADEN, DECAPEN */  
	FTM3_MODE = 0;
	/* FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0 */
	FTM3_MODE = 0;
	/* QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)*/
	FTM3_QDCTRL &=~0;
	FTM3_CNT = 0x0; /* FTM Counter Value - reset counter to zero */
	FTM3_MOD = 0;	/* Set Fixed Period 0x1D3 -> 1KHz*/ 
	FTM3_CNTIN = 0; /* Set the Counter Initial Value to 0 */
	/* Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately */
	FTM3_SC = 0; /* Make sure its Off! */
	FTM3_C0V = 0;
	FTM3_C1V = 0;
	FTM3_C2V = 0;
	FTM3_C3V = 0;
	FTM3_C6V = 0;
	FTM3_COMBINE = 0x0;
	FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
	FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
	FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;	
}

void Pwm_SetDutyCycle(Pwm_ChannelType enChannelNumber, uint16_t DutyCycle)
{
	if(DutyCycle < FTM_Period)
	{
		switch(enChannelNumber)
		{
			case CHANNEL0:{
				FTM3_SC = 0; /* Make sure its Off! */
				FTM3_C0V = DutyCycle;
				FTM3_COMBINE = 0x0;
				FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
				FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
				FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;			
			}break;
			case CHANNEL1:{
				FTM3_SC = 0; /* Make sure its Off! */
				FTM3_C1V = DutyCycle;
				FTM3_COMBINE = 0x0;
				FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
				FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
				FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
			}break;
			case CHANNEL2:{
				FTM3_SC = 0; /* Make sure its Off! */
				FTM3_C2V = DutyCycle;
				FTM3_COMBINE = 0x0;
				FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
				FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
				FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
			}break;
			case CHANNEL3:{
				FTM3_SC = 0; /* Make sure its Off! */
				FTM3_C3V = DutyCycle;
				FTM3_COMBINE = 0x0;
				FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
				FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
				FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
			}break;
			case CHANNEL4:{}break;
			case CHANNEL5:{}break;
			case CHANNEL6:{
				FTM3_SC = 0; /* Make sure its Off! */
				FTM3_C6V = DutyCycle;
				FTM3_COMBINE = 0x0;
				FTM3_DEADTIME = FTM_DEADTIME_DTVAL(50); /* About 5usec */
				FTM3_SC = 0x08 | FTM_SC_PS(0x7); /* Edge Aligned PWM running from BUSCLK / 1 */
				FTM3_PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
			}break;
			case CHANNEL7:{}break;
		}
	}

}
