/*
 * Gps.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef GPS_H_
#define GPS_H_

#include "Sci.h"

#if 0
"PMTK000*"		/* Test commend */,
"PMTK220,200*"	/*Fix update rate in ms*/,
"PMTK300,200*"	/*Fix control rate in ms*/,
"PMTK397,0.2*"	/*Navigation speed threshold in m/s */,
"PMTK527,0.20*"	/*Current Navigation speed threshold in m/s */,
#endif
typedef enum{
	enTest=0,
	enFixUpdateDate,
	enFixCtrlRate,
	enNavSpeedTrhld,
	enCurNavSpeedTrhld
}Gps_tenCommands;

void Gps_vInit(void);

void Gps_vDeInit(void);

void Gps_u16GetDirection(void);

void Gps_boDetectModule(void);

void Gps_u16GetDestDirection(void);

void Gps_vProcessPosition(void);

void Gps_vCalculateHeading(void);

unsigned char Gps_u8ComputeChecksum(char *sNmeaSentence);

#endif /* GPS_H_ */
