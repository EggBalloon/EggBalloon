/*
 * Gps.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */
#include <mqx.h>
#include "Gps.h"


void Gps_vInit(void)
{
	
}

void Gps_vDeInit(void)
{
	
}

uint16_t Gps_u16GetDirection(void)
{
	uint16_t u16RetVal=0;
	
	return u16RetVal;
}

bool Gps_boDetectModule(void)
{
	bool boRetVal=0;
	
	return boRetVal;	
}

uint16_t Gps_u16GetDestDirection(void)
{
	uint16_t u16RetVal=0;
	
	return u16RetVal;
}

void Gps_vProcessPosition(void)
{
	
}

void Gps_vCalculateHeading(void)
{
	
}

uint8_t Gps_u8ComputeChecksum(char *sNmeaSentence)
{
	unsigned char u8Checksumn=0;
	_mqx_uint u32Index;
	
	u32Index=0;
	while( sNmeaSentence[u32Index] != '*' )
	{
		u8Checksumn ^= sNmeaSentence[u32Index];
		u32Index++;
	}
	
	return u8Checksumn;
}

