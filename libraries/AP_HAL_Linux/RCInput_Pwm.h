#pragma once

#include "AP_HAL_Linux.h"
#include "RCInput.h"
#include <AP_HAL/I2CDevice.h>

#define PWM1_ADDRESS            0x08
#define PWM2_ADDRESS            0x09
#define PWM3_ADDRESS            0x0A
#define PWM4_ADDRESS            0x0B
#define PWM5_ADDRESS			0x0C

#define PWM_CHANNEL_COUNT		5

namespace Linux 
{
	
class RCInput_Pwm : public RCInput
{
public:
	RCInput_Pwm() {}
	RCInput_Pwm(AP_HAL::OwnPtr<AP_HAL::I2CDevice>, AP_HAL::OwnPtr<AP_HAL::I2CDevice>, AP_HAL::OwnPtr<AP_HAL::I2CDevice>, AP_HAL::OwnPtr<AP_HAL::I2CDevice>, AP_HAL::OwnPtr<AP_HAL::I2CDevice>);
	~RCInput_Pwm();
    void init() override;
    void _timer_tick(void) override;
	
private:
    static const size_t CHANNEL_COUNT = PWM_CHANNEL_COUNT;
    AP_HAL::OwnPtr<AP_HAL::I2CDevice> _pwm_dev[PWM_CHANNEL_COUNT];
    uint64_t _last_timestamp = 0l;
    uint16_t periods[PWM_CHANNEL_COUNT] = {0};
	uint8_t currentChannel = 0; // il canale corrente ad essere misurato
};
	
}