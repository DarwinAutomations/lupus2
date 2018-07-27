#include <memory>
#include <stdexcept>

#include "rc_steering.h"

namespace lupus::navigation
{

RCSteering::RCSteering(std::shared_ptr<Servo> servo)
{
  if(!servo)
  {
    throw std::invalid_argument("servo must not be null");
  }
  this->servo = std::move(servo);
}

void RCSteering::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }
  this->servo->setDirection((direction + 1) / 2);
}

float RCSteering::getDirection()
{
  return this->servo->getDirection() * 2 -1;
}

float RCSteering::getRawDirection()
{
  return this->servo->getRawDirection();
}

} // namespace lupus::navigation
