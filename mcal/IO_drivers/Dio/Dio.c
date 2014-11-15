/*
 * Dio.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Dio.h"

#define BSP_RGBRED                    (GPIO_PORT_B | GPIO_PIN22)
#define BSP_RGBRED_MUX_GPIO           (LWGPIO_MUX_B22_GPIO)

#define BSP_RGBGREEN                  (GPIO_PORT_E | GPIO_PIN26)
#define BSP_RGBGREEN_MUX_GPIO         (LWGPIO_MUX_E26_GPIO)

#define BSP_RGBBLUE                   (GPIO_PORT_B | GPIO_PIN21)
#define BSP_RGBBLUE_MUX_GPIO          (LWGPIO_MUX_B21_GPIO)

static LWGPIO_STRUCT stLedRed;
static LWGPIO_STRUCT stLedGreen;
static LWGPIO_STRUCT stLedBlue;

static bool boLedPortsInit=FALSE;
static bool	boRedInit = FALSE;
static bool	boGreenInit = FALSE;
static bool	boBlueInit = FALSE;

static void DIO__vSetLwgpio(LWGPIO_STRUCT * pstPortReg,LWGPIO_VALUE Value);


void Dio_Init(void)
{
	printf("Init LEDs...\n");
    if(FALSE == boLedPortsInit)
    {
    	boLedPortsInit = TRUE;
		if (!lwgpio_init(&stLedRed, BSP_RGBRED, LWGPIO_DIR_OUTPUT, PORT_OFF))
		{
			printf("...RED LED failed!!\n");
		}else
		{
			boRedInit= TRUE;
			printf("R");
			lwgpio_set_functionality(&stLedRed, BSP_RGBRED_MUX_GPIO);
		}
		/*********************************************************************************/
		if (!lwgpio_init(&stLedGreen, BSP_RGBGREEN, LWGPIO_DIR_OUTPUT, PORT_OFF))
		{
			printf("...GREEN LED failed!!\n");
		}else
		{
			boGreenInit = TRUE;
			printf("G");
			lwgpio_set_functionality(&stLedGreen, BSP_RGBGREEN_MUX_GPIO);
		}
		/*********************************************************************************/
		if (!lwgpio_init(&stLedBlue, BSP_RGBBLUE, LWGPIO_DIR_OUTPUT, PORT_OFF))
		{
			printf("...BLUE LED failed!!\n");
		}else
		{
			boBlueInit = TRUE;
			printf("B");
			lwgpio_set_functionality(&stLedBlue, BSP_RGBBLUE_MUX_GPIO);
		}
		if( (TRUE == boRedInit) && (TRUE == boGreenInit) && (TRUE == boBlueInit) )
		{
			printf("...READY!!\n");
		}
		else
		{
			printf("...ERROR on RGB!!\n");
			_time_delay(200);
		}
    }
    else
    {
    	/* do nothing */
    }
}

void Dio_DeInit(void)
{
	
}

void Dio_SetPin(uint8_t Port, uint32_t Pin, uint8_t Value)
{
	if(enPORTB == Port)
	{
		switch(Pin)
		{
		case PIN21:
			DIO__vSetLwgpio(&stLedBlue,(LWGPIO_VALUE)Value);
			break;
		case PIN22:
			DIO__vSetLwgpio(&stLedRed,(LWGPIO_VALUE)Value);
			break;
		case PIN26:
			DIO__vSetLwgpio(&stLedGreen,(LWGPIO_VALUE)Value);
			break;
		default:break;
		}
	}
	else
	{
		/* do nothing (just PORTB is needed) */
	}
}

uint8_t Dio_ReadPin(uint8_t Port, uint32_t Pin)
{
	uint8_t u8RetVal=0;
	
	return u8RetVal;	
}

static void DIO__vSetLwgpio(LWGPIO_STRUCT * pstPortReg,LWGPIO_VALUE Value)
{
	lwgpio_set_value(pstPortReg,Value);
}
