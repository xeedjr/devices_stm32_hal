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
  struct Line {
      GPIO_TypeDef  *port;
      uint16_t      pin;
  };

private:
  struct Channel {
    Line in1, in2;
	TIM_HandleTypeDef *pwmp;
    uint32_t channel;
    enum {
    	kStop,
		kRun,
		kPwm,
    } state = kStop;
  };
  struct Channel chn[Channels::kCount];
  Line stby;

  void _set_drive_speed(Channels ch, float pwm);

public:
  TB6612FNG() {};
  void init (Line ain2, Line ain1,
              Line bin2, Line bin1,
              Line stby,
			  TIM_HandleTypeDef *apwmp, uint32_t achannel,
			  TIM_HandleTypeDef *bpwmp, uint32_t bchannel);
                
  void drive(Channels ch, Mode mode, float pwm);
};
