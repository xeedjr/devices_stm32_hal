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

    uint64_t freq = 120*1000*1000;
    struct {
        uint32_t prev = 0;
       // uint32_t dist = 0;
        float usec = 0;
    } sonars[3];

    void IT(TIM_HandleTypeDef *htim);
public:
    USSensor(TIM_HandleTypeDef *timer);
    virtual ~USSensor();

    float get_distance(uint8_t idx);
};

#endif /* THIRDPARTY_DEVICES_STM32_HAL_USSENSOR_H_ */
