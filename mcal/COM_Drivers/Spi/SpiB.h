/*
 * SpiB.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef SPIB_H_
#define SPIB_H_



void Spi_Init(void);

void Spi_readIB(void);

void Spi_writeIB(void);

void Spi_SyncTransmit(void);

void Spi_GetSequenceResult(void);

#endif /* SPIB_H_ */
