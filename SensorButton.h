/*
 * SensorButton.h
 *
 *  Created on: Sep 27, 2020
 *      Author: Bogdan
 */

#ifndef THIRD_PARTY_DEVICES_STM32_HAL_SENSORBUTTON_H_
#define THIRD_PARTY_DEVICES_STM32_HAL_SENSORBUTTON_H_

#include "stm32f0xx_hal.h"

namespace stm32hal {

class SensorButton {
public:
	typedef void (*callback_t)(void);

	SensorButton(GPIO_TypeDef  *port,
				uint32_t pin,
				callback_t pushed_cb,
				callback_t released_cb);
	virtual ~SensorButton();

	void event();
private:
	void event_process_();
	bool is_pushed_old_state_ = false;
	GPIO_TypeDef  * port_;
	uint8_t pin_;
	callback_t pushed_cb_;
	callback_t released_cb_;
	callback_t timer_cb_;
    callback_t ext_interrupt_;
};

} /* namespace stm32hal */

#endif /* THIRD_PARTY_DEVICES_STM32_HAL_SENSORBUTTON_H_ */
