/*
 * USTrigger.h
 *
 *  Created on: Feb 7, 2021
 *      Author: Bogdan
 */

#ifndef THIRDPARTY_DEVICES_STM32_HAL_USTRIGGER_H_
#define THIRDPARTY_DEVICES_STM32_HAL_USTRIGGER_H_

#include "tim.h"

class USTrigger {
    TIM_HandleTypeDef *timer;
public:
    USTrigger(TIM_HandleTypeDef *timer) {
        if (HAL_TIM_PWM_Start(timer, TIM_CHANNEL_1) != HAL_OK)
            exit(-2);
    };
    virtual ~USTrigger() {};
};

#endif /* THIRDPARTY_DEVICES_STM32_HAL_USTRIGGER_H_ */
