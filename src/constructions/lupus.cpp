#include <stdexcept>
#include "lupus.h"

namespace lupus::construction
{

Lupus::Lupus(
  navigation::SteeringUnit *steeringLeft,
  navigation::SteeringUnit *steeringRight,
  navigation::PropulsionUnit *propulsionFrontLeft,
  navigation::PropulsionUnit *propulsionFrontRight,
  navigation::PropulsionUnit *propulsionBackLeft,
  navigation::PropulsionUnit *propulsionBackRight
)
{
  if(
    !steeringLeft ||
    !steeringRight ||
    !propulsionFrontLeft ||
    !propulsionFrontRight ||
    !propulsionBackLeft ||
    !propulsionBackRight
  )
  {
    throw std::invalid_argument("none of the parameters can be null");
  }

  this->steeringLeft = steeringLeft;
  this->steeringRight = steeringRight;
  this->propulsionFrontLeft = propulsionFrontLeft;
  this->propulsionFrontRight = propulsionFrontRight;
  this->propulsionBackLeft = propulsionBackLeft;
  this->propulsionBackRight = propulsionBackRight;
}

void Lupus::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }
  this->steeringLeft->setDirection(direction);
  this->steeringRight->setDirection(direction);
}

float Lupus::getDirection()
{
  return this->steeringLeft->getDirection();
}

void Lupus::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->propulsionFrontLeft->setPower(power);
  this->propulsionFrontRight->setPower(power);
  this->propulsionBackLeft->setPower(power);
  this->propulsionBackRight->setPower(power);
}

float Lupus::getPower()
{
  return this->propulsionFrontLeft->getPower();
}

} // namespace lupus::navigation
