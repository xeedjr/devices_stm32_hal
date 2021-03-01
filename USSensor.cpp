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
    if (HAL_TIM_IC_Start_IT(timer, TIM_CHANNEL_3) != HAL_OK)
        exit(-2);
}

USSensor::~USSensor() {
    // TODO Auto-generated destructor stub
}

void USSensor::IT(TIM_HandleTypeDef *htim) {

    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
        /// Channel 1
        auto curr = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);

        if (curr > sonars[0].prev) {
            auto dist = curr - sonars[0].prev;
            auto usec = ((1.0/freq)*dist)*1000*1000;
            if (usec > (2.0*58.0) && usec < (500.0*58.0))
                sonars[0].usec = usec;
        }

        sonars[0].prev = curr;
    }
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) {
        /// Channel 2
        auto curr = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_3);

        if (curr > sonars[1].prev) {
            auto dist = curr - sonars[1].prev;
            auto usec = ((1.0/freq)*dist)*1000*1000;
            if (usec > (2.0*58.0) && usec < (500.0*58.0))
                sonars[1].usec = usec;
        }

        sonars[1].prev = curr;
    }
}

float USSensor::get_distance(uint8_t idx) {
    double dist = sonars[idx].usec/58.0;

    return dist;
}
