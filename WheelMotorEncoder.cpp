/*
 * WheelMotorEncoder.cpp
 *
 *  Created on: 4 лют. 2021 р.
 *      Author: Bogdan
 */

#include <WheelMotorEncoder.h>

WheelMotorEncoder::WheelMotorEncoder(TIM_HandleTypeDef *timer, uint8_t gear_reduction) :
    HallEncoder(timer),
    gear_reduction(gear_reduction)
{

}

WheelMotorEncoder::~WheelMotorEncoder() {
    // TODO Auto-generated destructor stub
}

double WheelMotorEncoder::get_wheel_position() {
    auto revolutions = (double)get_position() / ((float)gear_reduction * (float)pulses_per_revolution);

    return ( revolutions * (M_PI*2.0) );
}
