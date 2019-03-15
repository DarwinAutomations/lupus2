#include <memory>
#include <stdexcept>

#include "steering_unit.h"

namespace lupus::construction::steeringUnit
{

SteeringUnit::SteeringUnit(
  std::shared_ptr<drivers::pwm::PwmDriver> driver,
  int channel,
  float min,
  float max)
{
  if(!driver)
  {
    throw std::invalid_argument("pwm dirver must not be null");
  }

  this->driver = std::move(driver);

  // config
  this->channel = channel;
  this->min = min;
  this->max = max;
}

void SteeringUnit::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range [-1, 1]");
  }

  this->direction = direction;

  this->setPwm((direction + 1) / 2);
}

void SteeringUnit::setPwm(float factor)
{
  if(factor > 1 || factor < 0)
  {
    throw std::invalid_argument("factor not in range [0, 1]");
  }

  int range = max - min;
  int offset = min + range * factor;

  value = offset;

  driver->setPwm(channel, 0, offset);
}

float SteeringUnit::getDirection()
{
  return direction;
}

int SteeringUnit::getValue()
{
  return value;
}

}
