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

typedef struct
{
	uint32_t 	u32Lat;
	uint32_t 	u32Lon;
	uint32_t 	u32Time;
	uint8_t		u8Stat;
}Gps_tstPosition;

void Gps_vInit(void);

void Gps_vDeInit(void);

uint16_t Gps_u16GetDirection(void);

bool Gps_boDetectModule(void);

uint16_t Gps_u16GetDestDirection(void);

void Gps_vProcessPosition(Gps_tstPosition * pstPos);

void Gps_vCalculateHeading(void);

#endif /* GPS_H_ */
