/*
 * USSensor.cpp
 *
 *  Created on: Feb 7, 2021
 *      Author: Bogdan
 */

#include <USSensor.h>

USSensor::USSensor(TIM_HandleTypeDef *timer) {
    if (HAL_TIM_RegisterCallback(timer, HAL_TIM_TRIGGER_HALF_CB_ID, (pTIM_CallbackTypeDef)this) != HAL_OK)
            exit(-1);

    if (HAL_TIM_RegisterCallback(timer,
            HAL_TIM_IC_CAPTURE_CB_ID,
            [](TIM_HandleTypeDef *htim){
            if (htim->TriggerHalfCpltCallback == nullptr)
                exit(-1);

            USSensor* thisp = (USSensor*)htim->TriggerHalfCpltCallback;

            thisp->IT(htim);
        }) != HAL_OK)
        exit(-1);

    if (HAL_TIM_IC_Start_IT(timer, TIM_CHANNEL_1) != HAL_OK)
        exit(-2);
    if (HAL_TIM_IC_Start_IT(timer, TIM_CHANNEL_2) != HAL_OK)
        exit(-2);
}

USSensor::~USSensor() {
    // TODO Auto-generated destructor stub
}
uint32_t var = 0;
void USSensor::IT(TIM_HandleTypeDef *htim) {

    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET) {
        /// Channel 1
        auto curr = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);

        if ((curr - prev1) > 0) {
               dist1 = curr - prev1;
               var = dist1;
        }

        prev1 = curr;
    }
}
