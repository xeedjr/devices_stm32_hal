#include "TB6612FNG.h"


void TB6612FNG::init(GPIO_TypeDef  *port,
					  uint32_t ain2, uint32_t ain1,
					  uint32_t bin2, uint32_t bin1,
					  uint32_t stby,
					  TIM_HandleTypeDef *apwmp, uint32_t achannel,
					  TIM_HandleTypeDef *bpwmp, uint32_t bchannel)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	this->port = port;

	chn[kA].in2 = ain2;
	chn[kA].in1 = ain1;
	chn[kA].pwmp = apwmp;
	chn[kA].channel = achannel;

	chn[kB].in2 = bin2;
	chn[kB].in1 = bin1;
	chn[kB].pwmp = bpwmp;
	chn[kB].channel = bchannel;

	this->stby = stby;

	HAL_GPIO_WritePin(port, stby, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(port, ain2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(port, ain1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(port, bin2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(port, bin1, GPIO_PIN_RESET);

	HAL_TIM_PWM_Start(apwmp, achannel);
	HAL_TIM_PWM_Start(bpwmp, bchannel);
}

void TB6612FNG::_set_drive_speed(Channels ch, float pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	assert_param((pwm > 100.0) || (pwm < 0.0));
	auto period = __HAL_TIM_GET_AUTORELOAD(chn[ch].pwmp);
	auto compare = (period/100.0*pwm);
	__HAL_TIM_SET_COMPARE(chn[ch].pwmp, chn[ch].channel, compare);

	if (chn[ch].state != Channel::kPwm) {
		if (HAL_TIM_PWM_Start(chn[ch].pwmp, chn[ch].channel) != HAL_OK)
			assert_param(false);
	}
	chn[ch].state = Channel::kPwm;
}
  
void TB6612FNG::drive(Channels ch, Mode mode, float pwm)
{
	assert_param((pwm > 100.0) || (pwm < 0.0));
    
  HAL_GPIO_WritePin(port, stby, GPIO_PIN_SET);
  
  switch (mode) {
    case kCW:
      HAL_GPIO_WritePin(port, chn[ch].in1, GPIO_PIN_SET);
      HAL_GPIO_WritePin(port, chn[ch].in2, GPIO_PIN_RESET);
      _set_drive_speed(ch, pwm);
    break;
    case kCCW:
      HAL_GPIO_WritePin(port, chn[ch].in1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(port, chn[ch].in2, GPIO_PIN_SET);
      _set_drive_speed(ch, pwm);
    break;
    case kShortBrake:
      HAL_TIM_PWM_Stop(chn[ch].pwmp, chn[ch].channel);
      HAL_GPIO_WritePin(port, chn[ch].in1, GPIO_PIN_SET);
      HAL_GPIO_WritePin(port, chn[ch].in2, GPIO_PIN_SET);
    break;
    default:
    	assert_param(false);
    break;
  }
}  
