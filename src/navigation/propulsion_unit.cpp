#include <stdexcept>
#include <memory>

#include "propulsion_unit.h"

namespace lupus::navigation
{

PropulsionUnit::PropulsionUnit(std::shared_ptr<IControlUnit> controlUnit)
{
  if(!controlUnit)
  {
    throw std::invalid_argument("control_unit must not be null");
  }
  this->controlUnit = std::move(controlUnit);
}

void PropulsionUnit::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  power = (power + 1) / 2;
  this->controlUnit->setPower(power);
}

float PropulsionUnit::getPower()
{
  return this->controlUnit->getPower() * 2 -1;
}

} // namespace lupus::navigation
