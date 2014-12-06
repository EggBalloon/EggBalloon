/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
Provide MFS file system on external SD card.
*
*
*END************************************************************************/


#include <mqx.h>
#include <bsp.h>
#include <fio.h>
#include <mfs.h>
#include <shell.h>
#include <sdcard.h>
#include <spi.h>
#include <part_mgr.h>
#include "Temp.h"

#include "Pwm.h"
#include "Os.h"
#include "Dio.h"
#include "Sci.h"

#include "Led.h"
#include "Gps.h"
#include "Motor.h"

#if ! SHELLCFG_USES_MFS
#error "This application requires SHELLCFG_USES_MFS defined non-zero in user_config.h. Please recompile libraries with this option."
#endif

#if defined BSP_SDCARD_ESDHC_CHANNEL
#if ! BSPCFG_ENABLE_ESDHC
#error "This application requires BSPCFG_ENABLE_ESDHC defined non-zero in user_config.h. Please recompile libraries with this option."
#else
#define SDCARD_COM_CHANNEL BSP_SDCARD_ESDHC_CHANNEL
#endif

#elif defined BSP_SDCARD_SDHC_CHANNEL
#if ! BSPCFG_ENABLE_SDHC
#error "This application requires BSPCFG_ENABLE_SDHC defined non-zero in user_config.h. Please recompile libraries with this option."
#else
#define SDCARD_COM_CHANNEL BSP_SDCARD_SDHC_CHANNEL
#endif

#elif defined (BSP_SDCARD_SPI_CHANNEL)
#define SDCARD_COM_CHANNEL BSP_SDCARD_SPI_CHANNEL
#else
#error "SDCARD low level communication device not defined!"
#endif

#define MAXINVALIDTRIES 5
#define MINDWNSPEED 10
#define QUADRANT0 0
#define QUADRANT1 1
#define EAST	0
#define WEST	1
#define STRAIGHT 2
#define	CLCKWISE	0
#define CCLCKWISE	1
#define SYSDIRECTION	CLCKWISE
#define CURRDISTLEFT	255	 /* Replace 255 for a structure defined for distance left. To be provided by Marco */
#define MINDISTANCELEFT	50   /*Distance left units T.B.D. */
static uint8_t TriesCount=0;
typedef enum{
	FINDPOSITION,
	CHECKIFVALID,
	DOWNSOFT,
	UPSOFT,
	INITIAL,
	SYSDIR,
	MOVEON,
	DISTLEFT,
	MaxStates
}enStateMachine;

#define SEEKPOSVAL 0xFFFF
#define VALID_POSMASK	0x8000


#define APP_PERIOD_SECONDS     60
#define LOW_BATTERY_LEVEL      56000


_task_id motorId, readId, SdCardId;

bool boBlueInit;
static uint8_t u8Counter;
static Gps_tstPosition stCurrentPosition;

static uint16_t u16DestPosition;
static uint8_t u8MtrCurrentState=0;
static uint8_t u8DistanceLeft=0;
static uint8_t u8DestDirection;
static uint8_t u8CurrPosition;
static uint8_t u8SystDirection;

static int32_t gTemperatureValueinC;
static uint32_t gSecondsCounter;


void init_task(uint32_t);
void motor_task(uint32_t);
void read_task(uint32_t);
void sdcard_task(uint32_t);

_mqx_uint		u32Counter;
_mqx_uint		u32Counter2;
_mqx_uint		u32ColorCounter;
_mqx_uint		u32ToggleVal;
_mqx_int		u32StrLen;
bool			boFileClosed;
bool			boFileExists;
static MQX_FILE_PTR      fd = NULL;
const char ksFilePath[]="a:\\Test_File.csv";
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
   /* Task Index,   Function,     Stack,  Priority, Name,     Attributes,          Param, Time Slice */
	{ 4,            init_task,    1500,    10,     "Init",  MQX_AUTO_START_TASK, 0,     0 },
	{ 3,            motor_task,   3000,    12,     "Motor",                   0, 0,     0 },
    { 2,            read_task,    3000,    11,     "Read",                    0, 0,     0 },
    { 1,            sdcard_task,  2000,    12,     "SDcard",                  0, 0,     0 },
    { 0 }
};


/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void init_task(uint32_t temp)
{
	_task_id init_taskId;
    (void)temp; /* suppress 'unused variable' warning */
    
    /* Place MCAL initialization here */
    Pwm_Init(&pwmConfig);
    Adc_Init();
    Dio_Init();
    Led_vSetColor(enLedColorBlue);/* Set BLUE LED during the initialization */
    Sci_Init();

    FAN_InitMotorCntrl();
   
    for(uint8_t i=0;i<10;i++){
    	Adc_StartGroupConv();
    	AdcValue=Adc_ReadGroup();
    }

    OS_Delay(100);
    
    /* Place SWC initializations here */
   // Gps_vInit();
#if 0
	if (!lwgpio_init(&stLedBlue, BSP_RGBBLUE, LWGPIO_DIR_OUTPUT, LED_OFF))
	{
		printf("...RED LED failed!!\n");
	}else
	{
		boBlueInit= TRUE;
		printf("R");
		lwgpio_set_functionality(&stLedBlue, BSP_RGBBLUE_MUX_GPIO);
	}
#endif    
    init_taskId=_task_get_id();
    /* Run the shell on the serial port */
    printf("Demo Initialized\n");
    
    motorId =  OS_CreateTask(0, 3, 0, 1);
    SdCardId = OS_CreateTask(0, 1, 0, 1);
    readId  =  OS_CreateTask(0, 2, 0, 0);
    _task_destroy(init_taskId);
    u8Counter = 0;
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void read_task(uint32_t temp)
{
	bool boTemp=FALSE;
	uint32_t u32Void;
    (void)temp; /* suppress 'unused variable' warning */
    _task_id motor_Id, sdcard_Id;
    TD_STRUCT_PTR motor_ptr;
    TD_STRUCT_PTR sdcard_ptr;
    
    
    motor_Id = _task_get_id_from_name("Motor");
    sdcard_Id = _task_get_id_from_name("SDcard"); 
    
    motor_ptr = _task_get_td(motor_Id);
    sdcard_ptr = _task_get_td(sdcard_Id);
    
    Led_vSetColor(enLedColorGreen);/* Set BLUE GREEN: System is ready and running*/
        
    for(;;)
    {
    	gTemperatureValueinC = Temp_Read();
    	Gps_vProcessPosition(&stCurrentPosition);   
    	ioctl(stdout,IO_IOCTL_SERIAL_TRANSMIT_DONE,&u32Void);
    	 /* Run the shell on the serial port */
    	     	
    	 u8Counter++;
    	 if(u8Counter>19)
    	 {
    		 printf("Read Task\n");
    		 u8Counter = 0;
    		 
			_task_ready(motor_ptr);
			_task_ready(sdcard_ptr);
			
			if(LOW_BATTERY_LEVEL>gBatteryLevel){
				Led_vSetColor(enLedColorRed);
			}else{
				/*Do nothing*/
			}
    	 }
    	 else
    	 {
    		 /* do nothing */
    	 }   	    
    	OS_Delay (50);
    }
    
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : shell_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void motor_task(uint32_t temp)
{
    (void)temp; /* suppress 'unused variable' warning */
    
    /* Run the shell on the serial port */
    for(;;){
    
    /* Starts Motor control Task*/
   	uint16_t TmpPosition; /* Local variable to store current position value invalid or valid */
   // TmpPosition = Gps_u16GetDirection(); /* Get current GPS position */
    	        
    switch(u8MtrCurrentState){
    	case FINDPOSITION:{
    		TmpPosition = Gps_u16GetDirection(); /* Get current GPS position */
    	   	if(TmpPosition==SEEKPOSVAL) /* Initial Position found? */
    	   	{	
    	   		/* GPS is searching for position, stay here */
    	   		u8MtrCurrentState = FINDPOSITION;
    	   	}else
    	   	{
    	   		/* Check for valid data, move forward */
    	   		u8MtrCurrentState = CHECKIFVALID;
    	   	}
    	}break;
    	case CHECKIFVALID:{
    	  	if(TmpPosition & VALID_POSMASK) /* Is current direction read valid? */
    	   	{
    	   		TmpPosition = TmpPosition & 0x01FF; /* Remove validation bit from MSB */
    	   		if(TriesCount>0)
    	   		{
    	   			TriesCount--;    	   			
    	   		}else
    	   		{
    	   			/*Do nothing */
    	   		}
    	   		u8MtrCurrentState = UPSOFT;  /* Go Up softly */
    	   	}else
    	   	{	/* Invalid position */
    	   		if(TriesCount>=MAXINVALIDTRIES) /* is Invalid position detected more than MAXINVALIDTRIES times? */
    	   		{
    	   			u8MtrCurrentState = DOWNSOFT;  /* Go down softly */
    	   		}else
    	   		{
    	   			TriesCount++;		
    	   			u8MtrCurrentState = FINDPOSITION;  /* Check for valid position */
    	   		}    		
    	   	}
    	}break;
    	case DOWNSOFT:{
    	   	uint16_t u16TmpSpeed = FAN_GetMotorSpeed(MOTOREL);
    	   	if(u16TmpSpeed > MINDWNSPEED)
    	   	{
    	   		FAN_SetMotorSpeed(MOTOREL, (u16TmpSpeed-MINDWNSPEED));    	   		
    	   	}else
    	   	{
    	   		FAN_SetMotorSpeed(MOTORA, 0);
    	   		FAN_SetMotorSpeed(MOTORB, 0);
    	   		FAN_SetMotorSpeed(MOTOREL,0);
    	   	}
    	   	if(CURRDISTLEFT<(MINDISTANCELEFT/10))
    	   	{
    	   		u8MtrCurrentState=DOWNSOFT;
    	   	}else
    	   	{
    	   		u8MtrCurrentState=FINDPOSITION;
    	   	}    	   	   	
    	}break;
    	case UPSOFT:{
    		uint16_t u16TmpSpeed = FAN_GetMotorSpeed(MOTOREL);
    		if((u16TmpSpeed >= 0)&&(u16TmpSpeed < BASESPEED))
    		{
    			FAN_SetMotorSpeed(MOTOREL, (u16TmpSpeed + ((uint16_t)BASESPEED>>3)));    			
    		}else
    		{
    		 	/* Do Nothing */
    		}	
    		u8MtrCurrentState = INITIAL;  /* Init movement process */
    	}break;
    	case INITIAL:{
    		u16DestPosition = Gps_u16GetDestDirection();
    		if((u16DestPosition<=359)&&(TmpPosition<=359))
    		{
    			if((u16DestPosition > 0)&&(u16DestPosition<=180))
    			{
    				u8DestDirection=QUADRANT0;	/* Current position is in range 1 - 180 degrees*/
    			}else
    			{
    				u8DestDirection=QUADRANT1;	/* Current position is in range 181 - 0 degrees */
    			}
    			if((TmpPosition > 0)&&(TmpPosition<=180))
    			{
    				u8CurrPosition=QUADRANT0;  /* Current position is in range 1 - 180 degrees*/
    			}else
    			{
    				u8CurrPosition=QUADRANT1;  /* Current position is in range 181 - 0 degrees */
    			}
    			u8MtrCurrentState=SYSDIR;	/* Get system direction to move */
    		}else
    		{	/* Destiny or Current position out of range look for a new position */
    			u8MtrCurrentState=FINDPOSITION;
    		}
    	}break;
    	case SYSDIR:{
    		if(u8DestDirection == u8CurrPosition) /*Destiny and current position are in the same quadrant*/
    		{
    			if(u8DestDirection>u8CurrPosition)
    			{u8SystDirection=EAST;}else{/*do nothing */}
    			if(u8DestDirection<u8CurrPosition)
    			{u8SystDirection=WEST;}else{/*do nothing */}
    			if(u8DestDirection==u8CurrPosition)
    			{u8SystDirection=STRAIGHT;}else{/*do nothing */}
    		}else{/*Nothing to do*/}
    		if((u8DestDirection == QUADRANT0)&&(u8CurrPosition==QUADRANT1))
    		{
    			u8SystDirection=EAST;
    		}else{/*Nothing to do*/}
    		if((u8DestDirection == QUADRANT1)&&(u8CurrPosition==QUADRANT0))
    		{
    			u8SystDirection=WEST;
    		}else{/*Nothing to do*/}    
    		u8MtrCurrentState=MOVEON;
    	}break;
    	case MOVEON:{
    		if(u8DestDirection==EAST)
    		{
    			FAN_SetMotorDirection(MOTORA,SYSDIRECTION,SYSBASESPEED);
    			FAN_SetMotorDirection(MOTORB,SYSDIRECTION,SYSMAXSPEED);
    		}else{/*Do Nothing*/}
    		if(u8DestDirection==WEST)
    		{
    			FAN_SetMotorDirection(MOTORB,SYSDIRECTION,SYSBASESPEED);
    			FAN_SetMotorDirection(MOTORA,SYSDIRECTION,SYSMAXSPEED);
    		}else{/*Do Nothing*/}
    		if(u8DestDirection==STRAIGHT)
    		{
    			FAN_SetMotorDirection(MOTORB,SYSDIRECTION,SYSBASESPEED);
    			FAN_SetMotorDirection(MOTORA,SYSDIRECTION,SYSBASESPEED);
    		}else{/*Do Nothing*/}
    		u8MtrCurrentState=DISTLEFT;
    	}break;
    	case DISTLEFT:{
    		if(CURRDISTLEFT<MINDISTANCELEFT)
    		{
    			u8MtrCurrentState=DOWNSOFT;
    		}else
    		{
    			u8MtrCurrentState=FINDPOSITION;
    		}
    	}break;
    	default:{/* Do nothing */}break;
    }/*End switch */
    	        
    /* Ends Motor control Task */
    printf("Motor Task\n");
    OS_BlockTask();
    }
}

/*TASK*-----------------------------------------------------------------
*
* Function Name  : sdcard_task
* Returned Value : void
* Comments       :
*
*END------------------------------------------------------------------*/
void sdcard_task(uint32_t temp)
{
    (void)          temp; /* suppress 'unused variable' warning */
    bool            inserted = TRUE, readonly = FALSE, last = FALSE;
    _mqx_int        error_code;
    _mqx_uint       param;
    MQX_FILE_PTR    com_handle, sdcard_handle, filesystem_handle, partition_handle;
    char            filesystem_name[] = "a:";
    char            partman_name[] = "pm:";
    char            partition_name[] = "pm:1";
    char			sDataToWrite[128];
#if defined BSP_SDCARD_GPIO_DETECT
    LWGPIO_STRUCT   sd_detect;
#endif
        
    /* Open low level communication device */
    com_handle = fopen(SDCARD_COM_CHANNEL, (void *)(SPI_FLAG_FULL_DUPLEX));

    if (NULL == com_handle)
    {
        printf("Error opening communication handle %s, check your user_config.h.\n", SDCARD_COM_CHANNEL);
        OS_BlockTask();
    }

#if defined BSP_SDCARD_GPIO_DETECT
    /* Init GPIO pins for other SD card signals */
    error_code = lwgpio_init(&sd_detect, BSP_SDCARD_GPIO_DETECT, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE);
       if (!error_code)
       {
           printf("Initializing GPIO with sdcard detect pin failed.\n");
           OS_BlockTask();
       }
       
       /*Set detect and protect pins as GPIO Function */
       lwgpio_set_functionality(&sd_detect,BSP_SDCARD_DETECT_MUX_GPIO);
#if defined(BSP_SDCARD_DETECT_ACTIVE_LOW)
       lwgpio_set_attribute(&sd_detect, LWGPIO_ATTR_PULL_DOWN, LWGPIO_AVAL_ENABLE);
#endif
#endif /* BSP_SDCARD_GPIO_DETECT */
    /* Install SD card device */
    error_code = _io_sdcard_install("sdcard:", (void *)&_bsp_sdcard0_init, com_handle);
    if ( error_code != MQX_OK )
    {
        printf("Error installing SD card device (0x%x)\n", error_code);
        OS_BlockTask();
    }

    for (;;)
    {
        /* Run the shell on the serial port */
        printf("Sdcard Task\n");
#if defined BSP_SDCARD_GPIO_DETECT
#if defined(BSP_SDCARD_DETECT_ACTIVE_LOW)
        inserted = lwgpio_get_value(&sd_detect);
#endif /* BSP_SDCARD_DETECT_ACTIVE_LOW */
#endif /* BSP_SDCARD_GPIO_DETECT */

        if (last != inserted)
        {
            last = inserted;
        	        
            if (inserted)
            {
                OS_Delay (200);
                /* Open the device which MFS will be installed on */
                sdcard_handle = fopen("sdcard:", 0);
                if (sdcard_handle == NULL)
                {
                    printf("Unable to open SD card device.\n");
                    continue;
                }

                /* Set read only flag as needed */
                param = 0;
                if (readonly)
                {
                    param = IO_O_RDONLY;
                }
                if (IO_OK != ioctl(sdcard_handle, IO_IOCTL_SET_FLAGS, (char *) &param))
                {
                    printf("Setting device read only failed.\n");
                    continue;
                }

                /* Install partition manager over SD card driver */
                error_code = _io_part_mgr_install(sdcard_handle, partman_name, 0);
                if (error_code != MFS_NO_ERROR)
                {
                    printf("Error installing partition manager: %s\n", MFS_Error_text((uint32_t)error_code));
                    continue;
                }

                /* Open partition */
                partition_handle = fopen(partition_name, NULL);
                if (partition_handle != NULL)
                {
                    printf("Installing MFS over partition...\n");
                    
                    /* Validate partition */
                    error_code = _io_ioctl(partition_handle, IO_IOCTL_VAL_PART, NULL);
                    if (error_code != MFS_NO_ERROR)
                    {
                        printf("Error validating partition: %s\n", MFS_Error_text((uint32_t)error_code));
                        printf("Not installing MFS.\n");
                        continue;
                    }

                    /* Install MFS over partition */
                    error_code = _io_mfs_install(partition_handle, filesystem_name, 0);
                    if (error_code != MFS_NO_ERROR)
                    {
                        printf("Error initializing MFS over partition: %s\n", MFS_Error_text((uint32_t)error_code));
                    }

                } else {

                    printf("Installing MFS over SD card driver...\n");
                	
                    /* Install MFS over SD card driver */
                    error_code = _io_mfs_install(sdcard_handle, filesystem_name, (_file_size)0);
                    if (error_code != MFS_NO_ERROR)
                    {
                        printf("Error initializing MFS: %s\n", MFS_Error_text((uint32_t)error_code));
                    }
                }

                /* Open file system */
                if (error_code == MFS_NO_ERROR) {
                    filesystem_handle = fopen(filesystem_name, NULL);
                    error_code = ferror(filesystem_handle);
                    if (error_code == MFS_NOT_A_DOS_DISK)
                    {
                        printf("NOT A DOS DISK! You must format to continue.\n");
                    }
                    else if (error_code != MFS_NO_ERROR)
                    {
                        printf("Error opening filesystem: %s\n", MFS_Error_text((uint32_t)error_code));
                        continue;
                    }

                    printf ("SD card installed to %s\n", filesystem_name);
                    if (readonly)
                    {
                        printf ("SD card is locked (read only).\n");
                    }
                }
            }
            else
            {
                /* Close the filesystem */
                if ((filesystem_handle != NULL) && (MQX_OK != fclose(filesystem_handle)))
                {
                    printf("Error closing filesystem.\n");
                }
                filesystem_handle = NULL;

                /* Uninstall MFS  */
                error_code = _io_dev_uninstall(filesystem_name);
                if (error_code != MFS_NO_ERROR)
                {
                    printf("Error uninstalling filesystem.\n");
                }
                
                /* Close partition */
                if ((partition_handle != NULL) && (MQX_OK != fclose(partition_handle)))
                {
                    printf("Error closing partition.\n");
                }
                partition_handle = NULL;

                /* Uninstall partition manager  */
                error_code = _io_dev_uninstall(partman_name);
                if (error_code != MFS_NO_ERROR)
                {
                    printf("Error uninstalling partition manager.\n");
                }

                /* Close the SD card device */
                if ((sdcard_handle != NULL) && (MQX_OK != fclose(sdcard_handle)))
                {
                    printf("Unable to close SD card device.\n");
                }
                sdcard_handle = NULL;

                printf ("SD card uninstalled.\n");
            }
        }

        /* MaLo Test routine */
        if(0 == u32Counter)
        {
        	u32StrLen=sprintf(sDataToWrite,"%s",ksFilePath);
        	fd=fopen(sDataToWrite, "a+");
        	u32Counter++;
        	if(fd!=NULL)
        	{
        		printf ("File opened\n");	
        	}
        	else
        	{
        		printf ("ERROR opening file \n");
        	}
        }
        else
        {
        	if( (fd!=NULL)&&(u32Counter2<APP_PERIOD_SECONDS))
        	{
        		u32Counter=0;
        		gSecondsCounter++;
        		u32StrLen=sprintf(sDataToWrite,"Temperature, %.2d, Distance, %6.6d, Time, %d\r\n",gTemperatureValueinC,stCurrentPosition.u32CurrDist,gSecondsCounter);
        		write(fd,sDataToWrite,u32StrLen);
        		printf ("%s",sDataToWrite);
        		if(u32ToggleVal&0x01)
        		{
        			Led_vSetColor(enLedColorWhite);
        		}
        		else
        		{
        			Led_vSetColor(enLedColorOff);
        		}
        		//lwgpio_set_value(&stLedBlue, u32ToggleVal);/* MaLo */
        		u32Counter2++;
        		u32Counter++;
        		u32ToggleVal^=1;/* MaLo: Toggle */

        	}
        	else
        	{
        		if(u32Counter2 >= APP_PERIOD_SECONDS)
        		{
        			if( FALSE ==boFileClosed  )
        			{
        				boFileClosed = TRUE;
        				if( !fclose(fd) )
						{
							printf ("File CLOSED\n");
							Led_vSetColor(enLedColorMagenta);
						}
						else
						{
							printf ("ERROR closing file \n");
							Led_vSetColor(enLedColorCyan);
						}
        				fd=NULL;
        			}
        			else
        			{
        				/* do nothing */
        			}
        		}
        		else
        		{/* do nothing */}
        	}
        }
        OS_BlockTask();
    }
}

/* EOF */
