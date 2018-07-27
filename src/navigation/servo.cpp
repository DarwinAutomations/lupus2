#include "servo.h"

namespace lupus::navigation
{

Servo::Servo(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    int channel,
    float min,
    float max)
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
void Servo::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  value = direction;

  int off = min + (max - min) * direction;
  rawValue = off;
  pwmDriver->setPwm(channel, 0, off);
}

float Servo::getDirection()
{
  return value;
}

int Servo::getRawDirection()
{
  return rawValue;
}

} // namespace lupus::navigation
