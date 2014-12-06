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
	enCurNavSpeedTrhld,
	enSentenceEnable
}Gps_tenCommands;

typedef struct
{
	signed int bitGpsFlag 		: 1;/* GPS Present */
	signed int bitGpsGgaFlag 	: 1;/* GGA Present */
	signed int bitGpsRmcFlag 	: 1;/* RMC Present */
	signed int bitGpsFixedFlag 	: 1;/* GPS Fixed position */
	signed int bitGpsDestFlag 	: 1;/* Destination reached */
	signed int bitReserved		: 4;/* GPS Reserved flags */
}Gps_tstFlags;

typedef struct
{
	int32_t 		i32Lat;
	int32_t 		i32Lon;
	uint32_t 		u32Time;
	uint32_t		u32DistToDest;/*Remaining distance to destination*/
	uint32_t		u32CurrDist;
	uint8_t			u8Stat;
	Gps_tstFlags	stFlags;
}Gps_tstPosition;
/* Debug switch which enables different types of messages
 * 0 - Messages OFF
 * 1 - Just GGA and RMC reception debug messages
 * 2 - Just GPS parsing debug messages
 * */
#define GPS_DBG_SWITCH		(3)

#define GPS_ASCII_TO_DEC	(0x30)

#define GPS_TIME_POS		(6)
#define GPS_FIX_POS			(18)

#define GPS_LATH_POS		(20)
#define GPS_LATD_POS		(22)
#define GPS_LATM_POS		(25)

#define GPS_LONH_POS		(34)
#define GPS_LOND_POS		(37)
#define GPS_LONM_POS		(40)

#define GPS_SPD_POS			(49)

#define GPS_TIME_LEN		(6)
#define GPS_LATH_LEN		(2)

#define GPS_LATH_LEN		(2)
#define GPS_LATD_LEN		(2)
#define GPS_LATM_LEN		(4)

#define GPS_LONH_LEN		(3)
#define GPS_LOND_LEN		(2)
#define GPS_LONM_LEN		(4)

#define GPS_HEADING_LEN		(3)

#define GPS_MAX_LEN			(128)
#define	GPS_U8_ERROR		(0xFFU)
#define	GPS_U16_ERROR		(0xFFFFU)
#define	GPS_U32_ERROR		(0xFFFFFFFFU)
#define GPS_MAX_HOUR		(235959u)

#define GPS_MAX_HEADING		(359)
#define GPS_CLR_HEADING		(0x7FFF)
#define GPS_SET_HEADING		(0x8000)

#define	GPS_LAT_DEST		(6546)
#define	GPS_LON_DEST		(5646)

#define GPS_LAT_SCALING		(115)
#define GPS_LON_SCALING		(110)

#define	GPS_HEADING_DEST	(85)
#define GPS_DEFAULT_DIST	(2800)

void Gps_vInit(void);

void Gps_vDeInit(void);

uint16_t Gps_u16GetDirection(void);

bool Gps_boDetectModule(void);

uint16_t Gps_u16GetDestDirection(void);

void Gps_vProcessPosition(Gps_tstPosition * pstPos);

void Gps_vCalculateHeading(void);

#endif /* GPS_H_ */
