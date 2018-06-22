#include <stdexcept>
#include <memory>

#include "raw_controller.h"
#include "construction.h"

namespace lupus::controllers
{

RawController::RawController(
  std::shared_ptr<constructions::IConstruction> construction
)
{
  if (!construction)
  {
    throw std::invalid_argument("construction cannot be null");
  }

  this->construction = std::move(construction);

}

void RawController::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  this->construction->setSteeringLeftDirection(direction);
  this->construction->setSteeringRightDirection(direction);
}

float RawController::getDirection()
{
  float direction = this->construction->getSteeringLeftDirection();
  direction += this->construction->getSteeringRightDirection();
  direction /= 2;
  return direction;
}

void RawController::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }

  this->construction->setPropulsionFrontLeftPower(power);
  this->construction->setPropulsionFrontRightPower(power);
  this->construction->setPropulsionBackLeftPower(power);
  this->construction->setPropulsionBackRightPower(power);
}

float RawController::getPower()
{
  float power = this->construction->getPropulsionFrontLeftPower();
  power += this->construction->getPropulsionFrontRightPower();
  power += this->construction->getPropulsionBackLeftPower();
  power += this->construction->getPropulsionBackRightPower();
  power /= 4;
  return power;
}

} // namespace lupus::controllers
