/*
 * Gps.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */
#include <mqx.h>
#include <stdlib.h>
#include <math.h>
#include "Gps.h"
#include "Led.h"

#define GPS_HEADING_OK			((uint16_t)0x8000u)

#define GPS_CMDACK_INVALID		((uint8_t)'0')
#define GPS_CMDACK_NOTSUPPORTED	((uint8_t)'1')
#define GPS_CMDACK_FAILED		((uint8_t)'2')
#define GPS_CMDACK_SUCCEEDED	((uint8_t)'3')

typedef enum
{
	enGpsInit=0,
	enGpsRxGga,
	enGpsRxRmc,
	enGpsRxData,
	enGpsProcess,
	enGpsDataErr
}GPS__tenStates;

const char		ksDestinationName[]	= "a:\\Destination.txt";
const char		ksGpsLogName[]		= "a:\\Gps.log";

static volatile bool 			GPS__boGga_Flg		= FALSE;
static volatile bool 			GPS__boRmc_Flg		= FALSE;
static volatile bool 			GPS__boFirst_Flg	= FALSE;
static volatile uint8_t			GPR__u8ChecksumCtr;
static volatile uint16_t		GPS__u16CurrHeading;
static volatile uint16_t		GPR__u16DestHeading;
static volatile MQX_FILE_PTR 	GPS__pDestination	= NULL;
static volatile Gps_tstPosition GPS__stLastPosition;
static volatile Gps_tstPosition *GPS__pstCurrPosition;
static volatile GPS__tenStates	GPS__enGpsState;
static volatile GPS__tenStates	GPS__enGpsRxStatus;

static volatile uint32_t		GPS__u32DistanceToDest;
static volatile uint32_t		GPS__u32CurrentDistance;

static volatile char			GPS__cNmeaAck;
static volatile char 			GPS__acRxBuffer[GPS_MAX_LEN];
static volatile char 			GPS__acGga[GPS_MAX_LEN];
static volatile char 			GPS__acRmc[GPS_MAX_LEN];
static volatile char *			GPS__pcRxChar;

const char * GPS__kapMtkCommands[]=
{
	"PMTK000*"		/* Test commend */,
	"PMTK220,1000*"	/*Fix update rate in (ms 4)*/,
	"PMTK300,1000*"	/*Fix control rate in (ms 4)*/,
	"PMTK397,0.0*"	/*Navigation speed threshold in m/s */,
	"PMTK527,0.00*"	/*Current Navigation speed threshold in m/s */,
	"PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*"
};

static uint8_t Gps__u8ComputeChecksum(char *sNmeaSentence);
static bool GPS__boSendCommand(const char * sCmd,uint8_t u8Retries);
static uint16_t GPS__u16WaitChar(const char kcChar);
static bool GPS__boRxNmeaSentence(const char * kpcSentence);
static void GPS__vParseGpsInfo(void);
static bool GPS__boProcessSentence(void);
static uint16_t GPS_u16Sqrt32(uint32_t n);
/*****************************************************************************/
void Gps_vInit(void)
{
	GPS__pDestination= fopen(ksDestinationName, "r");
	GPS__stLastPosition.stFlags.bitGpsFlag = Gps_boDetectModule();
	/*****************************************************************************/
	/* Try to detect GPS module */
	printf("GPS...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enTest],5)==TRUE)
	{
		printf("Found\n");
		/*Led_vSetColor(enLedColorGreen);*/
	}
	else
	{
		printf("not Found\n");
		/*Led_vSetColor(enLedColorRed);*/
	}
	/*****************************************************************************/
	/* Configure the update rate */
	printf("GPS Fix rate...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enFixUpdateDate],5)==TRUE)
	{
		printf("OK\n");
		/*Led_vSetColor(enLedColorCyan);*/
	}
	else
	{
		printf("ERR\n");
		/*Led_vSetColor(enLedColorRed);*/
	}
	/*****************************************************************************/
	/* Configure navigation threshold */
	printf("GPS threshold...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enNavSpeedTrhld],5)==TRUE)
	{
		printf("OK\n");
		/*Led_vSetColor(enLedColorYellow);*/
	}
	else
	{
		printf("ERR\n");
		/*Led_vSetColor(enLedColorRed);*/
	}
	/*****************************************************************************/
	/* Configure sentence enable */
	printf("GPS Sentence...");
	if(GPS__boSendCommand(GPS__kapMtkCommands[enSentenceEnable],5)==TRUE)
	{
		printf("OK\n");
		/*Led_vSetColor(enLedColorCyan);*/
	}
	else
	{
		printf("ERR\n");
		/*Led_vSetColor(enLedColorRed);*/
	}
	
	GPS__stLastPosition.i32Lat = 0;
	GPS__stLastPosition.i32Lon = 0;
	GPS__stLastPosition.u32Time= 0;
	GPS__stLastPosition.u8Stat = 0;
	GPS__stLastPosition.u32DistToDest = GPS_U32_ERROR;
	GPS__stLastPosition.u32CurrDist = GPS_U32_ERROR;
	GPS__stLastPosition.stFlags.bitGpsGgaFlag = FALSE;
	GPS__stLastPosition.stFlags.bitGpsRmcFlag = FALSE;
	GPS__stLastPosition.stFlags.bitGpsDestFlag= FALSE;
	GPS__stLastPosition.stFlags.bitGpsFixedFlag = FALSE;
	GPS__u16CurrHeading = GPS_U16_ERROR;
	GPR__u16DestHeading = GPS_U16_ERROR;
	
	GPS__enGpsState = enGpsInit;
	GPS__enGpsRxStatus = enGpsRxGga;
	
	Led_vSetColor(enLedColorOff);	/* System is ready */
	GPR__u16DestHeading=GPS_HEADING_DEST;
}
/*****************************************************************************/
void Gps_vDeInit(void)
{
	Sci_DeInit();
}
/*****************************************************************************/
uint16_t Gps_u16GetDirection(void)
{
	return GPS__u16CurrHeading;
}
/*****************************************************************************/
bool Gps_boDetectModule(void)
{
	bool boRetVal=0;
	
	return boRetVal;	
}
/*****************************************************************************/
uint16_t Gps_u16GetDestDirection(void)
{
	return GPR__u16DestHeading;
}
/*****************************************************************************/
void Gps_vProcessPosition(Gps_tstPosition * pstPos)
{
	uint8_t u8Dummy;
	uint8_t u8Temp;
	uint8_t u8HeaderChar;
	u8Temp = 0;

	GPS__pstCurrPosition = pstPos;
	/* Check for available characters */
	u8Temp = Sci_Read(&u8Dummy,enSciRxData);
	if(u8Temp != 0 )
	{

		do
		{
			switch(GPS__enGpsState)
			{
				case enGpsInit:
					u8HeaderChar=0;
					/* Wait for start of NMEA sentence ('$') */
					if( (Sci_Read(&u8HeaderChar,1)!=0) && (u8HeaderChar == '$') )
					{
						#if GPS_DBG_SWITCH == 1
						putchar('\t');
						#endif
						GPS__enGpsState = enGpsRxData;
						GPS__acGga[0]=(char)u8HeaderChar;
						GPS__acRmc[0]=(char)u8HeaderChar;
					}
					else
					{
						/* do nothing
						 * The reception is not synchronized */
					}
					break;
				case enGpsRxData:
					if(GPS__boRxNmeaSentence("GPS")==TRUE)
					{
						if( /*(TRUE == GPS__boGga_Flg) && (TRUE == GPS__boRmc_Flg)*/TRUE == GPS__boProcessSentence() )
						{
							GPS__enGpsState = enGpsProcess;
						}
						else
						{
							GPS__enGpsState = enGpsDataErr;
						}
					}
					else
					{
						GPS__enGpsState = enGpsDataErr;
					}
					//puts("\n");
					break;
				case enGpsDataErr:
				default:
					GPS__boGga_Flg=FALSE;
					GPS__boRmc_Flg=FALSE;
					GPS__enGpsState = enGpsInit;
					break;
			}
		}while( (GPS__enGpsState != enGpsProcess) && (Sci_Read(&u8Dummy,enSciRxData)!=0) );
		
		if( enGpsProcess == GPS__enGpsState )
		{
			GPS__vParseGpsInfo();
			GPS__boGga_Flg = FALSE;
			GPS__boRmc_Flg = FALSE;
			GPS__enGpsState = enGpsInit;
		}
		else
		{
			/* do nothing
			 * Both sentences have to be received */
		}
	}
	else
	{
		/* do nothig
		 * NO DATA AVAILABLE */
	}
}
/*****************************************************************************/
void Gps_vCalculateHeading(void)
{
	
}
/*****************************************************************************/
static uint8_t Gps__u8ComputeChecksum(char *sNmeaSentence)
{
	uint8_t u8Checksumn=0;
	_mqx_uint u32Index;
	
	u32Index=0;
	GPR__u8ChecksumCtr = 0;
	/* Compute checksum XOR-ing all the chars until a star ('*') is found */
	while( sNmeaSentence[u32Index] != '*' )
	{
		if(sNmeaSentence[u32Index] != '$')
		{
			u8Checksumn ^= sNmeaSentence[u32Index];
		}
		else
		{
			/* do nothing */
		}
		u32Index++;
		GPR__u8ChecksumCtr++;
	}
	/*Return the computed checksum*/
	return u8Checksumn;
}
/*****************************************************************************/
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
		
		/* Get the length of the string */
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
			u8AckLen=14;/*size of "001,ABC,D*EF'<CR>''<LF>'"*/
		}
		
		/* Wait for 'K' in the incoming buffer */
		if( GPS__u16WaitChar('K') < GPS_MAX_LEN )
		{
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
			printf("[%c] ",cAck);			
		}
		else
		{
			printf("CMD ERR\n");
		}
	}while(u8Temp!=0);
	
	return boRetVal;
}
/*****************************************************************************/
static uint16_t GPS__u16WaitChar(const char kcChar)
{
	uint16_t u16Counter;
	uint16_t u16Retries=GPS_U16_ERROR;
	char cTemp;
	uint8_t u8Temp;
	
	u16Counter = 0;
	while(  (u16Counter < GPS_MAX_LEN) && (cTemp != kcChar) && (u16Retries>0) )
	{
		u8Temp = Sci_Read((uint8_t*)&cTemp,1);
		if(0 == u8Temp )
		{
			_time_delay(1);
			u16Counter++;
		}
		else
		{
			/* do nothing */
		}
		u16Retries--;
	}
	
	if(0 == u16Retries)
	{
		u16Counter=GPS_U8_ERROR;
	}
	return u16Counter;
}
/*****************************************************************************/
static bool GPS__boRxNmeaSentence(const char * kpcSentence)
{
	uint8_t u8TempChecksum;
	char acTempBuffer[6];
	bool boRetVal = FALSE;
	uint8_t u8RxChars;
	
	u8RxChars = 0;
	GPS__pcRxChar = &GPS__acRxBuffer[0];
	/* Receive remaining ASCII chars */
	do
	{
		if(Sci_Read((uint8_t *)GPS__pcRxChar,1)!=0)
		{
			if( *GPS__pcRxChar!='\n'){GPS__pcRxChar++;}
			else{/* do nothing */}
			u8RxChars++;
		}
		else
		{
			u8RxChars=GPS_U8_ERROR;
		}
	}while( (*GPS__pcRxChar!='\n') && (u8RxChars < GPS_MAX_LEN ) );
	
	/* Check if the whole sentence was received */
	if(u8RxChars!=GPS_U8_ERROR)
	{	
		GPS__pcRxChar++;
		*GPS__pcRxChar='\0';/* Set end of string */
		
		boRetVal =TRUE;
	}
	else
	{
		/* do nothing
		 * Rx data ERROR (limit reached without '\n') */
		puts(" RxERR");
	}
	return boRetVal;
}
/*****************************************************************************/
static void GPS__vParseGpsInfo(void)
{
	/* =================FORMAT OF "RMC" SENTENCE (NMEA 0183)===================

		$GPRMC,165321.000,V,2035.669169,N,10325.956956,W,0.00,0.00,051214,,,N*63
		$GPRMC,172541.398,A,2705.0451,N,10926.7149,W,25.47,172.86,210606,,*2D
		   |	  |		  |	  |	   |  |	  |		|  |   |	  |		|		|
		   |	  |		  |	  |	   |  |	  |		|  |   |	  |		|		|
		   |	  |		  |	  |	   |  |	  |		|  |   |	  |		|		+-- CHECKSUM
		   |	  |		  |	  |	   |  |	  |		|  |   |	  |		+---------- DATE (xxyyzz)
		   |	  |		  |	  |	   |  |	  |		|  |   |	  +---------------- HEADING (ggg.gg)
		   |	  |		  |	  |	   |  |	  |		|  |   +----------------------- SPEED (in Knots)
		   |	  |		  |	  |	   |  |	  |		|  +--------------------------- DIRECTION LONGITUD (E/W)
		   |	  |		  |	  |	   |  |	  |		+------------------------------ LONGITUDE (.mmmm)
		   |	  |		  |	  |	   |  |   +------------------------------------ LONGITUDE (ggmm)
		   |	  |		  |	  |	   |  +---------------------------------------- DIRECCION LATITUD (N/S)
		   |	  |		  |	  |	   +------------------------------------------- LATITUDE (.mmmm)
		   |	  |		  |   +------------------------------------------------ LATITUDE (gggmm)
		   |	  |		  +---------------------------------------------------- ACK de coordenadas validas
		   |	  +------------------------------------------------------------ HOUR (HHMMSS.SSS)
           +------------------------------------------------------------------- HEADER

 |    COORDINATES         |      GPS DATEE         |           GPS TIME          |
	g= degree	m=minute	x=day	y=month	z=year	H=hour		M=minute	S=sec
	 * */
	char acTemp[16];
	char acHeading[4];
	char *pcHeading;
	uint32_t u32Time;
	int32_t i32Temp;
	int32_t i32TempLat;
	int32_t i32TempLon;
	
	if(FALSE == GPS__boFirst_Flg)
	{
		GPS__boFirst_Flg = TRUE;
		GPS__stLastPosition.u32DistToDest = GPS_DEFAULT_DIST;
		memcpy((void*)GPS__pstCurrPosition,(void*)&GPS__stLastPosition,sizeof(GPS__stLastPosition));
	}
	else
	{
		/*DISATNCE*/
		memcpy((void*)&acTemp[0],(void*)&GPS__acRmc[7],GPS_TIME_POS);
		acTemp[GPS_TIME_POS]='\0';/*Set end of string*/
		u32Time=atoi(acTemp);
		if(u32Time > GPS_MAX_HOUR)
		{u32Time=0;}
		GPS__pstCurrPosition->u32Time = u32Time;
		
		/*FIX POSITION*/
		GPS__cNmeaAck = GPS__acRmc[GPS_FIX_POS];
		if(GPS__cNmeaAck == 'A')
		{GPS__pstCurrPosition->stFlags.bitGpsFixedFlag=TRUE;}

		/*
						New Point (X2,Y2)
							(X2,Y2)
							.
							|\
							| \
						a   |  \  c = (a² + b²)½    or you can use    ((X2-X1)²+(Y2-Y1)²)½
							|   \
							|    \
							+-----· Last Point 
							   b        (X1,Y1)
		 * */
		
		if(TRUE == GPS__boRmc_Flg )
		{
			/*LATITUDE*/
			memcpy((void*)&acTemp[0],(void*)&GPS__acRmc[GPS_LATM_POS],GPS_LATM_LEN);
			acTemp[GPS_LATM_LEN]='\0';												/*Set end of string*/
			GPS__pstCurrPosition->i32Lat=atoi(acTemp);								/*remove decimal point*/
			i32TempLat = GPS__stLastPosition.i32Lat - GPS__pstCurrPosition->i32Lat;
			i32Temp = (i32TempLat*GPS_LAT_SCALING)/10;								/* convert to cm */
			i32TempLat = i32Temp*i32Temp;											/* power */ 
			
			/*LONGITUDE*/
			memcpy((void*)&acTemp[0],(void*)&GPS__acRmc[GPS_LONM_POS],GPS_LONM_LEN);
			acTemp[GPS_LONM_LEN]='\0';												/*Set end of string*/
			GPS__pstCurrPosition->i32Lon=atoi(acTemp);								/*remove decimal point*/
			i32TempLon= GPS__stLastPosition.i32Lon - GPS__pstCurrPosition->i32Lon;
			i32Temp = (i32TempLon*GPS_LON_SCALING)/10;								/* convert to cm */
			i32TempLon = i32Temp*i32Temp;											/* power */
			GPS__u32CurrentDistance = GPS_u16Sqrt32(i32TempLat+i32TempLon);
			GPS__stLastPosition.u32CurrDist = GPS__u32CurrentDistance;				/* CURRENT DISTANCE */
			
			/*EVALUATE TRAVELED DISTANCE*/
			if(GPS__stLastPosition.u32DistToDest >= GPS__stLastPosition.u32CurrDist)
			{
				/*SUBSTRACT CALCULATED DISTANCE*/
				GPS__stLastPosition.u32DistToDest-=GPS__stLastPosition.u32CurrDist;
			}
			else
			{
				/*DESTINATION REACHED ( +/- ERROR ) */
				GPS__stLastPosition.stFlags.bitGpsDestFlag= TRUE;
			}
			
			/*HEADING*/
			pcHeading = strchr((const char*)&GPS__acRmc[GPS_SPD_POS],',');pcHeading++;
			acHeading[0] =*pcHeading;pcHeading++;
			acHeading[1] =*pcHeading;pcHeading++;
			acHeading[2] =*pcHeading;pcHeading++;
			acHeading[3] ='\0';

			GPS__u16CurrHeading=atoi(acHeading);									/* ASCII to VALUE */
			if(GPS__u16CurrHeading > GPS_MAX_HEADING)
			{
				GPS__u16CurrHeading = GPS_MAX_HEADING;
			}
			if(TRUE ==GPS__pstCurrPosition->stFlags.bitGpsFixedFlag)
			{
				GPS__u16CurrHeading |= GPS_SET_HEADING;				
			}
			else
			{
				GPS__u16CurrHeading &= GPS_CLR_HEADING;
			}
			
			/*STORE VALUES FOR THE NEXT READING*/
			memcpy((void*)&GPS__stLastPosition,(void*)GPS__pstCurrPosition,sizeof(GPS__stLastPosition));			
		}
		else
		{
			/* do nothing */
		}
	}

	
	/* Clear received data */
	memset((void*)GPS__acGga,0,sizeof(GPS__acGga));
	memset((void*)GPS__acRmc,0,sizeof(GPS__acRmc));
	memset((void*)GPS__acRxBuffer,0,sizeof(GPS__acRxBuffer));
	#if GPS_DBG_SWITCH == 3
	printf("\tGPS[%X]\n",GPS__u16CurrHeading);
	#endif
}
/*****************************************************************************/
static bool GPS__boProcessSentence(void)
{
	bool boResult;
	uint8_t u8Checksum;
	uint8_t u8RxChecksum;
	uint8_t u8StrLen;
	uint8_t u8CompResult;
	char acTempBuffer[7];
	
	memcpy((void*)&acTempBuffer[0],(void*)&GPS__acRxBuffer[0],5);
	acTempBuffer[2]='\0';/*Set end of string*/
	
	boResult = FALSE;
	u8CompResult = strcmp("GP",acTempBuffer);
	if( 0 == u8CompResult )
	{
		#if GPS_DBG_SWITCH == 2
		putchar('R');
		#endif
		/*Copy NMEA sentence ID*/
		memcpy((void*)&acTempBuffer[0],(void*)&GPS__acRxBuffer[2],3);
		acTempBuffer[3]='\0';/*Set end of string*/
		if(0 == strcmp("GGA",acTempBuffer))
		{
			#if GPS_DBG_SWITCH == 2
			putchar('x');
			#endif
			GPS__boGga_Flg = TRUE;
			strcpy((void*)&GPS__acGga[1],(const char *)&GPS__acRxBuffer);
		}
		else
		{
			if(0 == strcmp("RMC",acTempBuffer))
			{
				#if GPS_DBG_SWITCH == 2
				putchar('X');
				#endif
				
				strcpy((void*)&GPS__acRmc[1],(const char *)&GPS__acRxBuffer);
				u8StrLen = strlen((char*)GPS__acRmc);
				u8Checksum = Gps__u8ComputeChecksum((char*)GPS__acRmc);
				
				/* set end of string to be able to convert the checksum */
				GPS__pcRxChar = strrchr((const char*)GPS__acRmc,'*');
				GPS__pcRxChar++;
				sprintf(&acTempBuffer[0],"%2.2X",u8Checksum);
				acTempBuffer[3]= *GPS__pcRxChar;GPS__pcRxChar++;
				acTempBuffer[4]= *GPS__pcRxChar;
				acTempBuffer[5]='\0';
				boResult = TRUE;
				if(strcmp((const char *)&acTempBuffer[0],(const char *)&acTempBuffer[3])==0)
				{
					GPS__boRmc_Flg = TRUE;
				}
				else
				{
					GPS__boRmc_Flg = FALSE;
					printf(" %s %s",&acTempBuffer[0],&acTempBuffer[3]);
				}
			}
			else
			{
				#if GPS_DBG_SWITCH == 2
				putchar('?');
				#endif
			}
			#if GPS_DBG_SWITCH == 2
			putchar('\n');
			#endif
		}
	}
	else
	{
		#if GPS_DBG_SWITCH == 2
		putchar('r');
		#endif
		memset((void*)&GPS__acRxBuffer[0],0,sizeof(GPS__acRxBuffer));
	}
	return boResult;
}

/* Experimental SQUARE ROOT algorithm since no float point is implemented */
static uint16_t GPS_u16Sqrt32(uint32_t n)  
{  
	uint16_t c = 0x8000;  
	uint16_t g = 0x8000;  
  
    for(;;) {  
        if(g*g > n)  
            g ^= c;  
        c >>= 1;  
        if(c == 0)  
            return g;  
        g |= c;  
    }  
}
