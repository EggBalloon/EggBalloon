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

void Gps_u16GetDirection(void)
{
	
}

void Gps_boDetectModule(void)
{
	
}

void Gps_u16GetDestDirection(void)
{
	
}

void Gps_vProcessPosition(void)
{
	
}

void Gps_vCalculateHeading(void)
{
	
}
unsigned char Gps_u8ComputeChecksum(char *sNmeaSentence)
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

