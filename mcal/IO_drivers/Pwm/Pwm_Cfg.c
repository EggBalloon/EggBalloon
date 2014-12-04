/*
 * Pwm_Cfg.c
 *
 *  Created on: Nov 15, 2014
 *      Author: Esteban
 */
#include "mqx.h"
#include "Pwm_Types.h"
#include "Pwm_Cfg.h"

tstPwm_Settings stPwm_Settings[]= { 
		  {	FlxTmr3, CHANNEL0, 0x28, 0x00 },
		  {	FlxTmr3, CHANNEL1, 0x28, 0x00 },
		  {	FlxTmr3, CHANNEL2, 0x28, 0x00 },
		  {	FlxTmr3, CHANNEL3, 0x28, 0x00 },
		  {	FlxTmr3, CHANNEL6, 0x28, 0x00 }
       };


const Pwm_ConfigType pwmConfig = { 
                                    sizeof(stPwm_Settings)/sizeof(stPwm_Settings[0]),  
                                    stPwm_Settings
                                   };
                                   

