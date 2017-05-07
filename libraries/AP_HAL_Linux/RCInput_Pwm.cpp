#include "RCInput_Pwm.h"
#include <utility>

using namespace Linux;

RCInput_Pwm::RCInput_Pwm(AP_HAL::OwnPtr<AP_HAL::I2CDevice> pwm1_dev, 
						 AP_HAL::OwnPtr<AP_HAL::I2CDevice> pwm2_dev, 
						 AP_HAL::OwnPtr<AP_HAL::I2CDevice> pwm3_dev, 
						 AP_HAL::OwnPtr<AP_HAL::I2CDevice> pwm4_dev,
						 AP_HAL::OwnPtr<AP_HAL::I2CDevice> pwm5_dev)
{	
	_pwm_dev[0] = std::move(pwm1_dev);
	_pwm_dev[1] = std::move(pwm2_dev);
	_pwm_dev[2] = std::move(pwm3_dev);
	_pwm_dev[3] = std::move(pwm4_dev);
	_pwm_dev[4] = std::move(pwm5_dev);
}

RCInput_Pwm::~RCInput_Pwm()
{
}

void RCInput_Pwm::init()
{
}
	
void RCInput_Pwm::_timer_tick(void)
{
	bool result = true;
	uint8_t pwmReadRequest[PWM_CHANNEL_COUNT] = { PWM1_ADDRESS | 1, PWM2_ADDRESS | 1, PWM3_ADDRESS | 1, PWM4_ADDRESS | 1, PWM5_ADDRESS };
	//int i;
	
	uint8_t pwmValue = 0u;

	if (AP_HAL::micros() - _last_timestamp < 50000) {
        return;
    }

	//for (i = 0; i < PWM_CHANNEL_COUNT; i++) {
		result = result && _pwm_dev[currentChannel]->transfer(&pwmReadRequest[currentChannel], 1, &pwmValue, 1); 
		periods[currentChannel] = pwmValue * 13.0; // di modo che il min sia circa 1100 e il max circa 1900
		currentChannel = (currentChannel + 1) % PWM_CHANNEL_COUNT;
	//}
	
    _update_periods(periods, ARRAY_SIZE(periods));

    _last_timestamp = AP_HAL::micros();
}