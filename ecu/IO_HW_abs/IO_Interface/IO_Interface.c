/*
 * IO_Interface.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "IO_Interface.h"

uint32_t Analog_Read(void)
{
	uint32_t u32AdcResult;
	
	Adc_StartGroupConv();
	
	u32AdcResult=Adc_ReadGroup();
	
	return u32AdcResult;	
}

void Digital_Write(uint16_t ChannelID, uint16_t value)
{
	uint16_t tempDIO;

	if(ChannelID&PWM_MASK)
	{
		/*Clear flags*/
		ChannelID&=FLAGS_MASK;
		/*Clear PWM mask*/
		ChannelID&=~PWM_MASK;
		/*Set duty cycle for the specified PWM channel*/
		Pwm_SetDutyCycle(ChannelID, value);
	}else{
		tempDIO = (ChannelID>>8);
		ChannelID&=FLAGS_MASK;

		if(enPORTB ==ChannelID){
			switch(tempDIO){
			case 21:
				Dio_SetPin(enPORTB, PIN21, (uint8_t)value);
				break;
			case 22:
				Dio_SetPin(enPORTB, PIN22, (uint8_t)value);
				break;
			case 26:
				Dio_SetPin(enPORTB, PIN26, (uint8_t)value);
				break;
			default:
				asm("nop");
				break;
			}
		}
	}
}

uint8_t Digital_Read(uint16_t ChannelID, uint16_t value)
{
	uint8_t u8Result;
	uint16_t u16Pin;
	
    ChannelID&=FLAGS_MASK;
    u16Pin=(value>>8);
    
    switch(ChannelID)
   	 		{
   	 		case enPORTA:
   	 			
   	 			break;
   	 		case enPORTB:
   	 			if (21==u16Pin){
   	 				u8Result=Dio_ReadPin(enPORTB, PIN21);	
   	 			}else if(22==u16Pin){
   	 				u8Result=Dio_ReadPin(enPORTB, PIN22);
   	 			}else if(26==u16Pin){
   	 				u8Result=Dio_ReadPin(enPORTB, PIN26);
   	 			}
   	 		    break;
   	 		case enPORTC:
   	 					
   	 			break;
   	 		case enPORTD:
   	 							
   	 			break;
   	 		case enPORTE:
   	 			 							
   	 			break;
   	 		default:
   	 			u8Result=0xFF;
   	 			break;
   	 		}
    
    return u8Result;
}
