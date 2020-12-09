#pragma once

#include "stm32common_hal.h"

class TB6612FNG  {
public:
  enum Mode {
    kShortBrake,
    kCCW,
    kCW,
    kStop,
    kStandby
  };
  enum Channels {
    kA = 0,
    kB = 1,
    kCount = 2,
  };

private:
  struct Channel {
	uint32_t in1, in2;
	TIM_HandleTypeDef *pwmp;
    uint32_t channel;
    enum {
    	kStop,
		kRun,
		kPwm,
    } state = kStop;
  };
  GPIO_TypeDef  *port;
  struct Channel chn[Channels::kCount];
  uint32_t stby;

  void _set_drive_speed(Channels ch, float pwm);

public:
  TB6612FNG() {};
  void init (GPIO_TypeDef  *port,
		  	  uint32_t ain2, uint32_t ain1,
			  uint32_t bin2, uint32_t bin1,
			  uint32_t stby,
			  TIM_HandleTypeDef *apwmp, uint32_t achannel,
			  TIM_HandleTypeDef *bpwmp, uint32_t bchannel);
                
  void drive(Channels ch, Mode mode, float pwm);
};
