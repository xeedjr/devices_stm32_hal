/*
 * USSensor.h
 *
 *  Created on: Feb 7, 2021
 *      Author: Bogdan
 */

#ifndef THIRDPARTY_DEVICES_STM32_HAL_USSENSOR_H_
#define THIRDPARTY_DEVICES_STM32_HAL_USSENSOR_H_

#include "tim.h"


// min 116uS - 2cm,  max 23200uS - 400cm

class USSensor {
    TIM_HandleTypeDef *timer;

    uint32_t prev1 = 0;
    uint32_t dist1 = 0;

    void IT(TIM_HandleTypeDef *htim);
public:
    USSensor(TIM_HandleTypeDef *timer);
    virtual ~USSensor();
};

#endif /* THIRDPARTY_DEVICES_STM32_HAL_USSENSOR_H_ */
