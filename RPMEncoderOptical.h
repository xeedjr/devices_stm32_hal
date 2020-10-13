/*
 * RPMEncoderOptical.h
 *
 *  Created on: Oct 12, 2020
 *      Author: Bogdan
 */

#pragma once

#include "stm32common_hal.h"

/**
 * 	auto clock = HAL_RCC_GetPCLK1Freq()/htim2.Init.Prescaler;
 *	auto pulses = 0.04/(1.0/(float)clock);
 */

class RPMEncoderOptical {
	TIM_HandleTypeDef *timer;
	uint32_t channelRaise, channelFall;
	uint32_t tick_per_revolution = 0;
	uint32_t last_count = 0;
	float last_fall_count = 0;

public:
	RPMEncoderOptical(TIM_HandleTypeDef *timer, uint32_t channelRaise, uint32_t channelFall, uint32_t tick_per_revolution);
	virtual ~RPMEncoderOptical();
	float get_time();
};

