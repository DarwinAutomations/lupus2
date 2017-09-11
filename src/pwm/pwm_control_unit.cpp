#include <stdexcept>
#include "pwm_control_unit.h"

namespace lupus::pwm
{

PwmControlUnit::PwmControlUnit(
  PwmDriver* pwmDriver,
  int channel,
  int min,
  int max)
{
  if(!pwmDriver)
  {
    throw std::invalid_argument("pwm_driver must not be null");
  }
  this->pwmDriver = pwmDriver;
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
  int off = (min - max) * power + max;
  pwmDriver->setPwm(this->channel, 0, off);
}

} // namespace lupus::pwm
