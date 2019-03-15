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

  void PwmControlUnit::setPower(float factor)
  {
    if (factor > 1 || factor < 0)
    {
      throw std::invalid_argument("factor not in range [0, 1]");
    }

    int range = max - min;
    int offset = min + range * factor;

    this->value = offset;

    pwmDriver->setPwm(this->channel, 0, offset);
  }

  float PwmControlUnit::getPower()
  {
    return this->value;
  }

}
