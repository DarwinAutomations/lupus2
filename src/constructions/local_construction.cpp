#include <stdexcept>
#include "local_construction.h"

namespace lupus::constructions
{

LocalConstruction::LocalConstruction(
  std::shared_ptr<navigation::ISteering> steeringLeft,
  std::shared_ptr<navigation::ISteering> steeringRight,

  std::shared_ptr<propulsion::IMotor> motorFrontLeft,
  std::shared_ptr<propulsion::IMotor> motorFrontRight,
  std::shared_ptr<propulsion::IMotor> motorBackLeft,
  std::shared_ptr<propulsion::IMotor> motorBackRight,

  std::shared_ptr<sensors::IDistanceSensor> distanceFrontLeft,
  std::shared_ptr<sensors::IDistanceSensor> distanceFrontCenterLeft,
  std::shared_ptr<sensors::IDistanceSensor> distanceFrontCenterRight,
  std::shared_ptr<sensors::IDistanceSensor> distanceFrontRight,
  std::shared_ptr<sensors::IDistanceSensor> distanceBackLeft,
  std::shared_ptr<sensors::IDistanceSensor> distanceBackCenterLeft,
  std::shared_ptr<sensors::IDistanceSensor> distanceBackCenterRight,
  std::shared_ptr<sensors::IDistanceSensor> distanceBackRight
)
{
  // steering
  this->steeringLeft = std::move(steeringLeft);
  this->steeringRight = std::move(steeringRight);

  // motors
  this->motorFrontLeft = std::move(motorFrontLeft);
  this->motorFrontRight = std::move(motorFrontRight);
  this->motorBackLeft = std::move(motorBackLeft);
  this->motorBackRight = std::move(motorBackRight);

  // sensors
  this->distanceFrontLeft = std::move(distanceFrontLeft);
  this->distanceFrontCenterLeft = std::move(distanceFrontCenterLeft);
  this->distanceFrontCenterRight = std::move(distanceFrontCenterRight);
  this->distanceFrontRight = std::move(distanceFrontRight);
  this->distanceBackLeft = std::move(distanceBackLeft);
  this->distanceBackCenterLeft = std::move(distanceBackCenterLeft);
  this->distanceBackCenterRight = std::move(distanceBackCenterRight);
  this->distanceBackRight = std::move(distanceBackRight);
}


void LocalConstruction::setPropulsionFrontLeftPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->motorFrontLeft->setPower(power);
}

void LocalConstruction::setPropulsionFrontRightPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->motorFrontRight->setPower(power);
}

void LocalConstruction::setPropulsionBackLeftPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->motorBackLeft->setPower(power);
}

void LocalConstruction::setPropulsionBackRightPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->motorBackRight->setPower(power);
}


float LocalConstruction::getPropulsionFrontLeftPower()
{
  return this->motorFrontLeft->getPower();
}

float LocalConstruction::getPropulsionFrontRightPower()
{
  return this->motorFrontRight->getPower();
}

float LocalConstruction::getPropulsionBackLeftPower()
{
  return this->motorBackLeft->getPower();
}

float LocalConstruction::getPropulsionBackRightPower()
{
  return this->motorBackRight->getPower();
}

float LocalConstruction::getRpsFrontLeft()
{
  return this->motorFrontLeft->getRps();
}

float LocalConstruction::getRpsFrontRight()
{
  return this->motorFrontRight->getRps();
}

float LocalConstruction::getRpsBackLeft()
{
  return this->motorBackLeft->getRps();
}

float LocalConstruction::getRpsBackRight()
{
  return this->motorBackRight->getRps();
}

void LocalConstruction::setSteeringLeftDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }
  this->steeringLeft->setDirection(direction);
}

void LocalConstruction::setSteeringRightDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }
  this->steeringRight->setDirection(direction);
}

float LocalConstruction::getSteeringLeftDirection()
{
  return this->steeringLeft->getDirection();
}

float LocalConstruction::getSteeringRightDirection()
{
  return this->steeringRight->getDirection();
}

} // namespace lupus::constructions
