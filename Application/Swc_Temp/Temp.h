/*
 * Temp.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Miguel
 */

#ifndef TEMP_H_
#define TEMP_H_

#include "IO_Interface.h"

/*!
* @brief These values are used to get the temperature. DO NOT MODIFY
*/
#define VTEMP25_ADC             (14279U)
#define VREF                    (3300000U)
#define M1                      (1715)

int32_t Temp_Read(void);

#endif /* TEMP_H_ */
