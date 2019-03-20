#include <stdexcept>
#include <memory>

#include "propulsion_unit.h"

namespace lupus::construction::motor::propulsionUnit
{

PropulsionUnit::PropulsionUnit(
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
  PropulsionUnitConfiguration config): configuration(config)
{
  if(!pwmDriver)
  {
    throw std::invalid_argument("pwm_driver must not be null");
  }

  this->pwmDriver = std::move(pwmDriver);;
  this->power = 0;
  this->value = configuration.forwardMin;
}

void PropulsionUnit::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->power = power;

  int offset;
  if(power < 0)
  {
    int range = configuration.backwardMin - configuration.backwardMax;
    offset = configuration.backwardMin - range * -power;
  }
  else
  {
    int range = configuration.forwardMax - configuration.forwardMin;
    offset = configuration.forwardMin + range * power;
  }
  value = offset;
  pwmDriver->setPwm(configuration.pin, 0, offset);
}

float PropulsionUnit::getPower()
{
  return power;
}

int PropulsionUnit::getValue()
{
  return value;
}

}
