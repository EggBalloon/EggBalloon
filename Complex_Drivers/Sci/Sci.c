/*
 * Sci.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#include "Sci.h"
#include "user_config.h"
static bool GPS__boDestination_Flg	= FALSE;
static MQX_FILE_PTR 	pGpsDev		= NULL;

const char				kacGpsUart[] = "ittyb:";


void Sci_Init(void)
{
	printf("SCI Init...");
	
	pGpsDev = fopen(kacGpsUart,(void*)(IO_SERIAL_NON_BLOCKING));
	if(pGpsDev!=NULL)
	{
		printf("OK\n");
	}
	else
	{
		printf("ERR\n");
	}
	/* Flush Tx/Rx buffers */
	Sci_flush();
}

void Sci_DeInit(void)
{
	Sci_flush();	
}

uint16_t Sci_Read(uint8_t *pu8Buffer,uint16_t u16DataLen)
{
	uint8_t u8ReadByte;
	uint8_t u8Temp;
	uint16_t u16Temp;
	uint16_t u16RetVal=0;
	
	if(pGpsDev!=NULL)
	{
		if(u16DataLen<enSciStatus)
		{
			u16Temp = 0;
			u8ReadByte = 0;
			while(u16Temp<u16DataLen)
			{
				u8Temp=read(pGpsDev,&u8ReadByte,1);
				if(1 == u8Temp)
				{
					pu8Buffer[u16Temp]=u8ReadByte;
					u16Temp++;
				}
				else
				{
					u16Temp=0xFFFF;/*ERROR*/
				}
			}
			if(u16Temp!=0xFFFF)
			{
				u16RetVal=u16Temp;
			}
			else
			{
				u16RetVal=(uint16_t)enSciErrNoData;
			}
		}
		else
		{
			ioctl(pGpsDev,IO_IOCTL_CHAR_AVAIL,&u16RetVal);
		}
	}
	else
	{
		u16RetVal=(uint16_t)enSciErrNoInit;
	}
	return u16RetVal;	
}

uint16_t Sci_Write(uint8_t *pu8Buffer,uint16_t u16DataLen)
{
	uint16_t u16RetVal=0;
	
	if(pGpsDev!=NULL)
	{
		u16RetVal=(uint16_t)write(pGpsDev,pu8Buffer,u16DataLen);
	}
	else
	{
		u16RetVal=(uint16_t)enSciErrNoInit;
	}
	return u16RetVal;
}

void Sci_flush(void)
{
	/* Flush Tx/Rx buffers */
	fflush(pGpsDev);
}
