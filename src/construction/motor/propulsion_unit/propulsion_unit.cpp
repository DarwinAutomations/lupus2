#include <stdexcept>
#include <memory>

#include "propulsion_unit.h"

namespace lupus::construction::motor::propulsionUnit
{

PropulsionUnit::PropulsionUnit(
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
  int channel,
  float forwardMin,
  float forwardMax,
  float backwardMin,
  float backwardMax)
{
  if(!pwmDriver)
  {
    throw std::invalid_argument("pwm_driver must not be null");
  }

  this->pwmDriver = std::move(pwmDriver);
  this->channel = channel;
  this->forwardMin = forwardMin;
  this->forwardMax = forwardMax;
  this->backwardMin = backwardMin;
  this->backwardMax = backwardMax;
  this->power = 0;
}

void PropulsionUnit::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->power = power;

  int off = forwardMin;
  if(power < 0)
  {
    off = backwardMin - (backwardMin - backwardMax) * -power;
  }
  else
  {
    off = forwardMin + (forwardMax - forwardMin) * power;
  }
  this->rawPower = off;
  pwmDriver->setPwm(this->channel, 0, off);
}

float PropulsionUnit::getPower()
{
  return this->power;
}

int PropulsionUnit::getRawPower()
{
  return this->rawPower;
}

}
