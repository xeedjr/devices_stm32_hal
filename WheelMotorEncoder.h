/*
 * WheelMotorEncoder.h
 *
 *  Created on: 4 лют. 2021 р.
 *      Author: Bogdan
 */

#pragma once

#include "HallEncoder.h"

class WheelMotorEncoder : public HallEncoder {
    uint8_t gear_reduction = 34;
public:
    WheelMotorEncoder(TIM_HandleTypeDef *timer, uint8_t gear_reduction);
    virtual ~WheelMotorEncoder();
    double get_wheel_position();
};

