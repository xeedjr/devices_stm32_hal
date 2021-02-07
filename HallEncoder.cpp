/*
 * HallEncoder.cpp
 *
 *  Created on: Feb 3, 2021
 *      Author: Bogdan
 */

#include <HallEncoder.h>

HallEncoder::HallEncoder(TIM_HandleTypeDef *timer) :
    timer(timer)
{
    /// Set unused event as object
    if (HAL_TIM_RegisterCallback(timer, HAL_TIM_TRIGGER_HALF_CB_ID, (pTIM_CallbackTypeDef)this) != HAL_OK)
            exit(-1);

    if (HAL_TIM_RegisterCallback(timer,
                HAL_TIM_PERIOD_ELAPSED_CB_ID,
            [](TIM_HandleTypeDef *htim){
            if (htim->TriggerHalfCpltCallback == nullptr)
                exit(-1);

            HallEncoder* thisp = (HallEncoder*)htim->TriggerHalfCpltCallback;

            thisp->overflow_IT(htim);
        }) != HAL_OK)
        exit(-1);

    if (HAL_TIM_Encoder_Start(timer, TIM_CHANNEL_ALL) != HAL_OK)
        exit(-1);

    if (HAL_TIM_Base_Start_IT(timer) != HAL_OK)
        exit(-1);

    __HAL_TIM_SetCounter(timer, 0);



    //__HAL_TIM_GET_COUNTER(timer);
}

HallEncoder::~HallEncoder() {
    // TODO Auto-generated destructor stub
}

void HallEncoder::overflow_IT(TIM_HandleTypeDef *htim) {
    /// we got overflow track it
    if (is_first) {
        is_first = false;
        return;
    }

    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim)) {
        /// down count
        count--;
    } else {
        /// up count
        count++;
    }
}

int64_t HallEncoder::get_position() {
    auto a = count;
    auto b = __HAL_TIM_GET_COUNTER(timer);

    return ((a*0xFFFF) + b);
}
