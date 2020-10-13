/*
 * RPMEncoderOptical.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: Bogdan
 */

#include <RPMEncoderOptical.h>

#define RPM_ENCODER_OPTICAL_GET_PRESCALER(__HANDLE__)       ((__HANDLE__)->Init->Prescaler)

RPMEncoderOptical::RPMEncoderOptical(TIM_HandleTypeDef *timer, uint32_t channelRaise, uint32_t channelFall, uint32_t tick_per_revolution) {
	this->timer = timer;
	this->channelRaise = channelRaise;
	this->channelFall = channelFall;
	this->tick_per_revolution = tick_per_revolution;

	HAL_TIM_IC_Start(timer, channelRaise);
	HAL_TIM_IC_Start(timer, channelFall);
}

RPMEncoderOptical::~RPMEncoderOptical() {
	// TODO Auto-generated destructor stub
}

float RPMEncoderOptical::get_time() {
	uint32_t current_count = 0;

	uint32_t raise = __HAL_TIM_GET_COMPARE(timer, channelRaise);
	uint32_t fall = __HAL_TIM_GET_COMPARE(timer, channelFall);

	if (last_fall_count != fall) {
		if (raise < fall) {
			current_count = fall - raise;
		} else {
			/// we have overflow
			auto t = __HAL_TIM_GET_AUTORELOAD(timer) - raise;
			current_count = fall + t;
		}
	} else {
		/// we do not have yet readings
		current_count = last_count;
	}

	last_fall_count = fall;
	last_count = current_count;

	return ((float)current_count/(float)tick_per_revolution);
}
