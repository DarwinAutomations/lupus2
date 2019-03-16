#include <stdexcept>
#include <memory>

#include "rc_motor.h"

namespace lupus::construction::motor
{

RCMotor::RCMotor(
    std::shared_ptr<motor::propulsionUnit::PropulsionUnit> propulsionUnit,
    std::shared_ptr<rpsSensor::HallRpsSensor> rpsSensor)
{
  if(!propulsionUnit)
  {
    throw std::invalid_argument("propulsion_unit must not be null");
  }

  if(!rpsSensor)
  {
    throw std::invalid_argument("rps_sensor must not be null");
  }

  this->propulsionUnit = std::move(propulsionUnit);
  this->rpsSensor = std::move(rpsSensor);
}

void RCMotor::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->propulsionUnit->setPower(power);
}

float RCMotor::getPower()
{
  return this->propulsionUnit->getPower();
}

float RCMotor::getRawPower()
{
  return this->propulsionUnit->getRawPower();
}

float RCMotor::getRps()
{
  return this->rpsSensor->getRps();
}

}
