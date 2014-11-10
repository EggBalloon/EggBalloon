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
#define VTEMP25_ADC             (14219U)
#define K                       (10000U)
#define M1                      (250000U)
#define M2                      (311U)

#define UPPER_VALUE_LIMIT       (1U)     /*! This value/10 is going to be added to current Temp to set the upper boundary*/
#define LOWER_VALUE_LIMIT       (1U)     /*! This Value/10 is going to be subtracted from current Temp to set the lower boundary*/
#define UPDATE_BOUNDARIES_TIME  (20U)    /*! This value indicates the number of cycles needed to update boundaries. To know the Time it will take, multiply this value times LPTMR_COMPARE_VALUE*/
#define kAdcChannelTemperature  (26U)

uint32_t Temp_Read(void);

#endif /* TEMP_H_ */
