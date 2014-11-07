/*
 * Gps.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef GPS_H_
#define GPS_H_

#include "Sci.h"

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

uint8_t Gps_u8ComputeChecksum(char *sNmeaSentence);

#endif /* GPS_H_ */
