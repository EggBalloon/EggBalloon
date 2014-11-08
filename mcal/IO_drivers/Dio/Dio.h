/*
 * Dio.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef DIO_H_
#define DIO_H_

#include <mqx.h>
#include <bsp.h>
#include <fio.h>

typedef enum
{
	enPORTA=0,
	enPORTB,
	enPORTC,
	enPORTD,
	enPORTE,
}Dio_tenPorts;

#define PIN0	(0x00000001)
#define PIN1	(0x00000002)
#define PIN2	(0x00000004)
#define PIN3	(0x00000008)
#define PIN4	(0x00000010)
#define PIN5	(0x00000020)
#define PIN6	(0x00000040)
#define PIN7	(0x00000080)
#define PIN8	(0x00000100)
#define PIN9	(0x00000200)
#define PIN10 	(0x00000400)
#define PIN11 	(0x00000800)
#define PIN12 	(0x00001000)
#define PIN13 	(0x00002000)
#define PIN14 	(0x00004000)
#define PIN15 	(0x00008000)
#define PIN16	(0x00010000)
#define PIN17	(0x00020000)
#define PIN18	(0x00040000)
#define PIN19	(0x00080000)
#define PIN20	(0x00100000)
#define PIN21	(0x00200000)
#define PIN22	(0x00400000)
#define PIN23	(0x00800000)
#define PIN24	(0x01000000)
#define PIN25	(0x02000000)
#define PIN26 	(0x04000000)
#define PIN27 	(0x08000000)
#define PIN28 	(0x10000000)
#define PIN29 	(0x20000000)
#define PIN30 	(0x40000000)
#define PIN31 	(0x80000000)

#define	PORT_OFF	((uint8_t)LWGPIO_VALUE_HIGH)
#define	PORT_ON		((uint8_t)LWGPIO_VALUE_LOW)

void Dio_Init(void);

void Dio_DeInit(void);

void Dio_SetPin(uint8_t Port, uint32_t Pin, uint8_t Value);

uint8_t Dio_ReadPin(uint8_t Port, uint32_t Pin);

#endif /* DIO_H_ */
