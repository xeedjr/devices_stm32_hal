/*
 * RPMEncoderOptical.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: Bogdan
 */

#include <RPMEncoderOptical.h>

RPMEncoderOptical::RPMEncoderOptical(TIM_HandleTypeDef *timer, uint32_t channelRaise, uint32_t channelFall) {
	this->timer = timer;
	this->channelRaise = channelRaise;
	this->channelFall = channelFall;

	HAL_TIM_IC_Start(timer, channelRaise);
	HAL_TIM_IC_Start(timer, channelFall);
}

RPMEncoderOptical::~RPMEncoderOptical() {
	// TODO Auto-generated destructor stub
}

float RPMEncoderOptical::get_time() {
	uint32_t raise = __HAL_TIM_GET_COMPARE(timer, channelRaise);
	uint32_t fall = __HAL_TIM_GET_COMPARE(timer, channelFall);

	if (raise < fall) {
		current_rpm = fall - raise;
	}

	return current_rpm;
}
