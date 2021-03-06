/*
 * stm32common_hal.h
 *
 *  Created on: Oct 11, 2020
 *      Author: Bogdan
 */

#ifndef DEVICES_STM32_HAL_STM32COMMON_HAL_H_
#define DEVICES_STM32_HAL_STM32COMMON_HAL_H_

#ifdef STM32F1
#	include "stm32f1xx_hal.h"
#endif
#ifdef STM32F4
#	include "stm32f4xx_hal.h"
#endif
#ifdef STM32H7
#   include "stm32h7xx_hal.h"
#endif



#endif /* DEVICES_STM32_HAL_STM32COMMON_HAL_H_ */
