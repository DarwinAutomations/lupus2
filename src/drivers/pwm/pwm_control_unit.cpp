#include <stdexcept>
#include "pwm_control_unit.h"

namespace lupus::drivers::pwm
{

  PwmControlUnit::PwmControlUnit(
    std::shared_ptr<PwmDriver> pwmDriver,
    int channel,
    int min,
    int max)
  {
    if(!pwmDriver)
    {
      throw std::invalid_argument("pwm_driver must not be null");
    }

    this->pwmDriver = std::move(pwmDriver);
    this->channel = channel;
    this->min = min;
    this->max = max;
  }

  void PwmControlUnit::setPower(float power)
  {
    if (power > 1 || power < 0)
    {
      throw std::invalid_argument("power not in range 0, 1");
    }

    int off = min + (max - min) * power;
    pwmDriver->setPwm(this->channel, 0, off);
    this->value = power;
  }

  float PwmControlUnit::getPower()
  {
    return this->value;
  }

}
