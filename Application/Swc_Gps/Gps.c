/*
 * Gps.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */
#include <mqx.h>
#include "Gps.h"
#include "Led.h"

#define GPS_CMDACK_INVALID		((uint8_t)'0')
#define GPS_CMDACK_NOTSUPPORTED	((uint8_t)'1')
#define GPS_CMDACK_FAILED		((uint8_t)'2')
#define GPS_CMDACK_SUCCEEDED	((uint8_t)'3')

const char		ksDestinationName[]	= "a:\\Destination.txt";
const char		ksGpsLogName[]		= "a:\\Gps.log";

static bool 	GPS__boGga_Flg = FALSE;
static bool 	GPS__boRmc_Flg = FALSE;
static MQX_FILE_PTR 	pDestination	= NULL;
static Gps_tstPosition stLastPosition;

const char * GPS__kapNmeaSentences[]=
{
	"GPGGA",
	"GPRMC",
};

const char * GPS__kapMtkCommands[]=
{
	"PMTK000*"		/* Test commend */,
	"PMTK220,125*"	/*Fix update rate in (ms x 4)*/,
	"PMTK300,125*"	/*Fix control rate in (ms x 4)*/,
	"PMTK397,0.2*"	/*Navigation speed threshold in m/s */,
	"PMTK527,0.20*"	/*Current Navigation speed threshold in m/s */,
};

static uint8_t Gps__u8ComputeChecksum(char *sNmeaSentence);
static bool GPS__boSendCommand(const char * sCmd,uint8_t u8Retries);
static void GPS__vWaitChar(const char kcChar);

void Gps_vInit(void)
{
	pDestination= fopen(ksDestinationName, "r");
	
	/* Try to detect GPS module */
	printf("GPS...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enTest],5)==TRUE)
	{
		printf("Found\n");
		Led_vSetColor(enLedColorGreen);
	}
	else
	{
		printf("not Found\n");
		Led_vSetColor(enLedColorRed);
	}
	
	/* Configure the update rate */
	printf("GPS Fix rate...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enFixUpdateDate],5)==TRUE)
	{
		printf("OK\n");
		Led_vSetColor(enLedColorYellow);
	}
	else
	{
		printf("ERR\n");
		Led_vSetColor(enLedColorRed);
	}

	/* Configure navigation threshold */
	printf("GPS threshold...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enNavSpeedTrhld],5)==TRUE)
	{
		printf("OK\n");
		Led_vSetColor(enLedColorMagenta);
	}
	else
	{
		printf("ERR\n");
		Led_vSetColor(enLedColorRed);
	}
	stLastPosition.u32Lat=0;
	stLastPosition.u32Lon=0;
	stLastPosition.u32Time=0;
	stLastPosition.u8Stat=0;
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

void Gps_vProcessPosition(Gps_tstPosition * pstPos)
{
	pstPos->u32Lat=pstPos->u32Lat;
	pstPos->u32Lon=pstPos->u32Lon;
	pstPos->u32Time=pstPos->u32Time;
	pstPos->u8Stat=pstPos->u8Stat;
}

void Gps_vCalculateHeading(void)
{
	
}

static uint8_t Gps__u8ComputeChecksum(char *sNmeaSentence)
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

static bool GPS__boSendCommand(const char * sCmd,uint8_t u8Retries)
{
	bool boRetVal=FALSE;
	uint8_t u8Temp=u8Retries;
	uint8_t u8Checksum;
	uint8_t au8BytesToSend[128];
	uint8_t au8CmdAck[32];
	uint16_t u16StrLen=0;
	uint8_t u8AckLen;
	char cAck='\0';
	
	do{
		u8Checksum=0;
		/* Compute the command's checksum */
		u8Checksum = Gps__u8ComputeChecksum((char*)sCmd);
		/* Prepare the information in NMEA format */
		sprintf((char*)au8BytesToSend,"$%s%X\r\n",sCmd,u8Checksum);
		/* Get the lenght of the string */
		u16StrLen=strlen((char*)au8BytesToSend);
		/* Send out bytes over SCI */
		Sci_Write(au8BytesToSend,u16StrLen);
		_time_delay(100/*ms to allow ACK being received*/);
		/* Extract the command number ("$PMTK000*32" -> "000") */
		strcpy((char*)au8CmdAck,(char*) &au8BytesToSend[5]);
		/* Set NULL character to reduce string to 3 ASCII chars */
		au8CmdAck[3]=(uint8_t)NULL;
		if(strcmp("000",(const char*)au8CmdAck)==0)
		{
			u8AckLen=12;/*size of "001,0,3*30'<CR>''<LF>'"*/
		}
		else
		{
			u8AckLen=14;/*size of "001,XXX,y*cc'<CR>''<LF>'"*/
		}
		
		/* Wait for 'K' in the incoming buffer */
		GPS__vWaitChar('K');
		Sci_Read(au8CmdAck,u8AckLen);
		cAck = au8CmdAck[u8AckLen-6];
		
		/* Check the result */
		if(GPS_CMDACK_SUCCEEDED == cAck)
		{
			boRetVal=TRUE;
			/* No further retries needed */
			u8Temp=0;
		}
		else
		{
			_time_delay(5);
			u8Temp--;
		}
		printf("ACK[%c]\n",cAck);
	}while(u8Temp!=0);
	
	return boRetVal;
}

static void GPS__vWaitChar(const char kcChar)
{
	char cTemp;
	uint8_t u8Temp;
	
	while(  cTemp != kcChar )
	{
		u8Temp = Sci_Read((uint8_t*)&cTemp,1);
		if(u8Temp != 0)
		{
			printf(".");
		}
		else
		{
			/* do nothing */
		}	
	}
}
