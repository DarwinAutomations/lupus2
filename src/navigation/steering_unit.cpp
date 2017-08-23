#include <stdexcept>
#include "steering_unit.h"

namespace lupus::navigation
{

SteeringUnit::SteeringUnit(IControlUnit* controlUnit)
{
  if(!controlUnit)
  {
    throw std::invalid_argument("control_unit must not be null");
  }
  this->controlUnit = controlUnit;
}

void SteeringUnit::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }
  float power = (direction + 1) / 2;
  this->controlUnit->setPower(power);
}

} // namespace lupus::navigation
