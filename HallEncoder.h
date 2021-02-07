/*
 * HallEncoder.h
 *
 *  Created on: Feb 3, 2021
 *      Author: Bogdan
 */

#pragma once

#include "stm32common_hal.h"
#include "tim.h"

class HallEncoder {
    TIM_HandleTypeDef *timer;

    int64_t count = 0;
    bool is_first = true;

    void overflow_IT(TIM_HandleTypeDef *htim);

protected:
    uint8_t pulses_per_revolution = 16;

public:
    HallEncoder(TIM_HandleTypeDef *timer);
    virtual ~HallEncoder();

    int64_t get_position();
};


