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

/*!
* @brief These values are used to get the temperature. DO NOT MODIFY
*/
#define V_REFH          3400U     //3075U3300U   /* [mV] */
#define V_TEMP25        719U    /*719 [mV] */
#define ADC_MAX_SCALE   65536U  /* 2^16 bits */
#define ADC_TEMP_SLOPE  1715U   //1620U 1715U   /* [(mV*1000)/C] */
#define TEMP_OFFSET     200U    /* [C*100] */

int32_t Temp_Read(void);

#endif /* TEMP_H_ */
