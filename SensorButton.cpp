/*
 * SensorButton.cpp
 *
 *  Created on: Sep 27, 2020
 *      Author: Bogdan
 */

#include "SensorButton.h"

namespace stm32hal {

SensorButton::SensorButton(GPIO_TypeDef  *port,
							uint32_t pin,
							callback_t pushed_cb,
							callback_t released_cb) {
	// TODO Auto-generated constructor stub
	port_ = port;
	pin_ = pin;
	pushed_cb_ = pushed_cb;
	released_cb_ = released_cb;
}

SensorButton::~SensorButton() {
	// TODO Auto-generated destructor stub
}

void SensorButton::event_process_() {
	if (is_pushed_old_state_ == true) {

		if (HAL_GPIO_ReadPin(port_, pin_) == 0) {
			/// un pushed GPIOA_BUTTON
			is_pushed_old_state_ = false;

			if (released_cb_ != nullptr)
				released_cb_();
		};
	} else {
		if (HAL_GPIO_ReadPin(port_, pin_) == 1) {
			/// pushed GPIOA_BUTTON
			/// received new state need send event and change old state
			is_pushed_old_state_ = true;

			if (pushed_cb_ != nullptr)
				pushed_cb_();
		};
	};
}

/** @brief !!! Shall be in  chSysLockFromISR
 *
 */
void SensorButton::event() {
	event_process_();
}


} /* namespace stm32hal */

