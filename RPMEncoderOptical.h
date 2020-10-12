/*
 * RPMEncoderOptical.h
 *
 *  Created on: Oct 12, 2020
 *      Author: Bogdan
 */

#pragma once

#include "stm32common_hal.h"


class RPMEncoderOptical {
	TIM_HandleTypeDef *timer;
	uint32_t channelRaise, channelFall;
	float current_rpm = 0;

public:
	RPMEncoderOptical(TIM_HandleTypeDef *timer, uint32_t channelRaise, uint32_t channelFall);
	virtual ~RPMEncoderOptical();
	float get_time();
};

