#include <stdexcept>
#include "lupus.h"

namespace lupus::construction
{

Lupus::Lupus(
  std::shared_ptr<construction::steeringUnit::ISteering> steeringLeft,
  std::shared_ptr<construction::steeringUnit::ISteering> steeringRight,

  std::shared_ptr<construction::motor::IMotor> motorFrontLeft,
  std::shared_ptr<construction::motor::IMotor> motorFrontRight,
  std::shared_ptr<construction::motor::IMotor> motorBackLeft,
  std::shared_ptr<construction::motor::IMotor> motorBackRight,

  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceFrontLeft,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceFrontCenterLeft,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceFrontCenterRight,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceFrontRight,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceBackLeft,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceBackCenterLeft,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceBackCenterRight,
  std::shared_ptr<construction::distanceSensor::IDistanceSensor> distanceBackRight
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


std::shared_ptr<construction::motor::IMotor>
Lupus::getMotor(construction::motor::Motor motor)
{
  switch (motor)
  {
    case construction::motor::Motor::FrontLeft:
      return motorFrontLeft;
    case construction::motor::Motor::FrontRight:
      return motorFrontRight;
    case construction::motor::Motor::BackLeft:
      return motorBackLeft;
    case construction::motor::Motor::BackRight:
      return motorBackRight;
    default:
      throw std::invalid_argument("unknown motor");
  }
}

void Lupus::setPower(construction::motor::Motor motor, float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  switch (motor)
  {
    case construction::motor::Motor::FrontLeft:
      motorFrontLeft->setPower(power);
      break;
    case construction::motor::Motor::FrontRight:
      motorFrontRight->setPower(power);
      break;
    case construction::motor::Motor::BackLeft:
      motorBackLeft->setPower(power);
      break;
    case construction::motor::Motor::BackRight:
      motorBackRight->setPower(power);
      break;
  }
}

float Lupus::getPower(construction::motor::Motor motor)
{
  switch (motor)
  {
    case construction::motor::Motor::FrontLeft:
      return motorFrontLeft->getPower();
    case construction::motor::Motor::FrontRight:
      return motorFrontRight->getPower();
    case construction::motor::Motor::BackLeft:
      return motorBackLeft->getPower();
    case construction::motor::Motor::BackRight:
      return motorBackRight->getPower();
    default:
      throw std::invalid_argument("unknown motor");
  }
}

float Lupus::getRps(construction::motor::Motor motor)
{
  switch (motor)
  {
    case construction::motor::Motor::FrontLeft:
      return motorFrontLeft->getRps();
    case construction::motor::Motor::FrontRight:
      return motorFrontRight->getRps();
    case construction::motor::Motor::BackLeft:
      return motorBackLeft->getRps();
    case construction::motor::Motor::BackRight:
      return motorBackRight->getRps();
    default:
      throw std::invalid_argument("unknown motor");
  }
}



std::shared_ptr<construction::steeringUnit::ISteering>
Lupus::getSteering(construction::steeringUnit::SteeringUnit steering)
{
  switch (steering)
  {
    case construction::steeringUnit::SteeringUnit::Left:
      return steeringLeft;
    case construction::steeringUnit::SteeringUnit::Right:
      return steeringRight;
    default:
      throw std::invalid_argument("get steering: unknown steering");
  }
}

void Lupus::setDirection(
  construction::steeringUnit::SteeringUnit steering,
  float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  switch (steering)
  {
    case construction::steeringUnit::SteeringUnit::Left:
      steeringLeft->setDirection(direction);
      break;
    case construction::steeringUnit::SteeringUnit::Right:
      steeringRight->setDirection(direction);
      break;
  }
}

float Lupus::getDirection(construction::steeringUnit::SteeringUnit steering)
{
  switch (steering)
  {
    case construction::steeringUnit::SteeringUnit::Left:
      return steeringLeft->getDirection();
    case construction::steeringUnit::SteeringUnit::Right:
      return steeringRight->getDirection();
    default:
      throw std::invalid_argument("get direction: unknown steering");
  }
}

std::shared_ptr<construction::distanceSensor::IDistanceSensor>
Lupus::getDistanceSensor(construction::distanceSensor::DistanceSensor distanceSensor)
{
  switch (distanceSensor) {
    case construction::distanceSensor::DistanceSensor::FrontLeft:
      return distanceFrontLeft;
      break;
    case construction::distanceSensor::DistanceSensor::FrontCenterLeft:
      return distanceFrontCenterLeft;
      break;
    case construction::distanceSensor::DistanceSensor::FrontCenterRight:
      return distanceFrontCenterRight;
      break;
    case construction::distanceSensor::DistanceSensor::FrontRight:
      return distanceFrontRight;
      break;
    case construction::distanceSensor::DistanceSensor::BackLeft:
      return distanceBackLeft;
      break;
    case construction::distanceSensor::DistanceSensor::BackCenterLeft:
      return distanceBackCenterLeft;
      break;
    case construction::distanceSensor::DistanceSensor::BackCenterRight:
      return distanceBackCenterRight;
      break;
    case construction::distanceSensor::DistanceSensor::BackRight:
      return distanceBackRight;
      break;
    default:
      throw std::invalid_argument("get distance sensor: unknown sensor");
  }
}

float Lupus::getDistance(construction::distanceSensor::DistanceSensor distanceSensor)
{
  switch (distanceSensor) {
    case construction::distanceSensor::DistanceSensor::FrontLeft:
      return distanceFrontLeft->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::FrontCenterLeft:
      return distanceFrontCenterLeft->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::FrontCenterRight:
      return distanceFrontCenterRight->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::FrontRight:
      return distanceFrontRight->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::BackLeft:
      return distanceBackLeft->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::BackCenterLeft:
      return distanceBackCenterLeft->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::BackCenterRight:
      return distanceBackCenterRight->getDistance();
      break;
    case construction::distanceSensor::DistanceSensor::BackRight:
      return distanceBackRight->getDistance();
      break;
    default:
      throw std::invalid_argument("get distance: unknown sensor");
  }
}

}
