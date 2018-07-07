#include <stdexcept>
#include "local_construction.h"

namespace lupus::constructions
{

LocalConstruction::LocalConstruction(
  std::shared_ptr<navigation::SteeringUnit> steeringLeft,
  std::shared_ptr<navigation::SteeringUnit> steeringRight,

  std::shared_ptr<navigation::PropulsionUnit> propulsionFrontLeft,
  std::shared_ptr<navigation::PropulsionUnit> propulsionFrontRight,
  std::shared_ptr<navigation::PropulsionUnit> propulsionBackLeft,
  std::shared_ptr<navigation::PropulsionUnit> propulsionBackRight,

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

  // propulsion
  this->propulsionFrontLeft = std::move(propulsionFrontLeft);
  this->propulsionFrontRight = std::move(propulsionFrontRight);
  this->propulsionBackLeft = std::move(propulsionBackLeft);
  this->propulsionBackRight = std::move(propulsionBackRight);

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
  this->propulsionFrontLeft->setPower(power);
}

void LocalConstruction::setPropulsionFrontRightPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->propulsionFrontRight->setPower(power);
}

void LocalConstruction::setPropulsionBackLeftPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->propulsionBackLeft->setPower(power);
}

void LocalConstruction::setPropulsionBackRightPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  this->propulsionBackRight->setPower(power);
}


float LocalConstruction::getPropulsionFrontLeftPower()
{
  return this->propulsionFrontLeft->getPower();
}

float LocalConstruction::getPropulsionFrontRightPower()
{
  return this->propulsionFrontRight->getPower();
}

float LocalConstruction::getPropulsionBackLeftPower()
{
  return this->propulsionBackLeft->getPower();
}

float LocalConstruction::getPropulsionBackRightPower()
{
  return this->propulsionBackRight->getPower();
}

float LocalConstruction::getRpsFrontLeft()
{
  return this->propulsionFrontLeft->getRps();
}

float LocalConstruction::getRpsFrontRight()
{
  return this->propulsionFrontRight->getRps();
}

float LocalConstruction::getRpsBackLeft()
{
  return this->propulsionBackLeft->getRps();
}

float LocalConstruction::getRpsBackRight()
{
  return this->propulsionBackRight->getRps();
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
