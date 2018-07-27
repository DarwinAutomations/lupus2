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


std::shared_ptr<propulsion::IMotor> LocalConstruction::getMotor(propulsion::Motor motor)
{
  switch (motor)
  {
    case propulsion::Motor::FrontLeft:
      return motorFrontLeft;
    case propulsion::Motor::FrontRight:
      return motorFrontRight;
    case propulsion::Motor::BackLeft:
      return motorBackLeft;
    case propulsion::Motor::BackRight:
      return motorBackRight;
    default:
      throw std::invalid_argument("unknown motor");
  }
}

void LocalConstruction::setPower(propulsion::Motor motor, float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  switch (motor)
  {
    case propulsion::Motor::FrontLeft:
      motorFrontLeft->setPower(power);
      break;
    case propulsion::Motor::FrontRight:
      motorFrontRight->setPower(power);
      break;
    case propulsion::Motor::BackLeft:
      motorBackLeft->setPower(power);
      break;
    case propulsion::Motor::BackRight:
      motorBackRight->setPower(power);
      break;
  }
}

float LocalConstruction::getPower(propulsion::Motor motor)
{
  switch (motor)
  {
    case propulsion::Motor::FrontLeft:
      return motorFrontLeft->getPower();
    case propulsion::Motor::FrontRight:
      return motorFrontRight->getPower();
    case propulsion::Motor::BackLeft:
      return motorBackLeft->getPower();
    case propulsion::Motor::BackRight:
      return motorBackRight->getPower();
    default:
      throw std::invalid_argument("unknown motor");
  }
}

float LocalConstruction::getRps(propulsion::Motor motor)
{
  switch (motor)
  {
    case propulsion::Motor::FrontLeft:
      return motorFrontLeft->getRps();
    case propulsion::Motor::FrontRight:
      return motorFrontRight->getRps();
    case propulsion::Motor::BackLeft:
      return motorBackLeft->getRps();
    case propulsion::Motor::BackRight:
      return motorBackRight->getRps();
    default:
      throw std::invalid_argument("unknown motor");
  }
}



std::shared_ptr<navigation::ISteering> LocalConstruction::getSteering(navigation::Steering steering)
{
  switch (steering)
  {
    case navigation::Steering::Left:
      return steeringLeft;
    case navigation::Steering::Right:
      return steeringRight;
    default:
      throw std::invalid_argument("get steering: unknown steering");
  }
}

void LocalConstruction::setDirection(
  navigation::Steering steering,
  float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  switch (steering)
  {
    case navigation::Steering::Left:
      steeringLeft->setDirection(direction);
      break;
    case navigation::Steering::Right:
      steeringRight->setDirection(direction);
      break;
  }
}

float LocalConstruction::getDirection(navigation::Steering steering)
{
  switch (steering)
  {
    case navigation::Steering::Left:
      return steeringLeft->getDirection();
    case navigation::Steering::Right:
      return steeringRight->getDirection();
    default:
      throw std::invalid_argument("get direction: unknown steering");
  }
}

} // namespace lupus::constructions
