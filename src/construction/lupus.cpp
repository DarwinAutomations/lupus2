#include <stdexcept>
#include "lupus.h"

namespace lupus::construction
{

Lupus::Lupus(
  std::shared_ptr<construction::steeringUnit::SteeringUnit> steeringLeft,
  std::shared_ptr<construction::steeringUnit::SteeringUnit> steeringRight,

  std::shared_ptr<construction::motor::Motor> motorFrontLeft,
  std::shared_ptr<construction::motor::Motor> motorFrontRight,
  std::shared_ptr<construction::motor::Motor> motorBackLeft,
  std::shared_ptr<construction::motor::Motor> motorBackRight,

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


std::shared_ptr<construction::motor::Motor>
Lupus::getMotor(construction::motor::MotorPosition motor)
{
  switch (motor)
  {
    case construction::motor::MotorPosition::FrontLeft:
      return motorFrontLeft;
    case construction::motor::MotorPosition::FrontRight:
      return motorFrontRight;
    case construction::motor::MotorPosition::BackLeft:
      return motorBackLeft;
    case construction::motor::MotorPosition::BackRight:
      return motorBackRight;
    default:
      throw std::invalid_argument("unknown motor");
  }
}

void Lupus::setPower(construction::motor::MotorPosition motor, float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }
  switch (motor)
  {
    case construction::motor::MotorPosition::FrontLeft:
      motorFrontLeft->setPower(power);
      break;
    case construction::motor::MotorPosition::FrontRight:
      motorFrontRight->setPower(power);
      break;
    case construction::motor::MotorPosition::BackLeft:
      motorBackLeft->setPower(power);
      break;
    case construction::motor::MotorPosition::BackRight:
      motorBackRight->setPower(power);
      break;
  }
}

float Lupus::getPower(construction::motor::MotorPosition motor)
{
  switch (motor)
  {
    case construction::motor::MotorPosition::FrontLeft:
      return motorFrontLeft->getPower();
    case construction::motor::MotorPosition::FrontRight:
      return motorFrontRight->getPower();
    case construction::motor::MotorPosition::BackLeft:
      return motorBackLeft->getPower();
    case construction::motor::MotorPosition::BackRight:
      return motorBackRight->getPower();
    default:
      throw std::invalid_argument("unknown motor");
  }
}

float Lupus::getRps(construction::motor::MotorPosition motor)
{
  switch (motor)
  {
    case construction::motor::MotorPosition::FrontLeft:
      return motorFrontLeft->getRps();
    case construction::motor::MotorPosition::FrontRight:
      return motorFrontRight->getRps();
    case construction::motor::MotorPosition::BackLeft:
      return motorBackLeft->getRps();
    case construction::motor::MotorPosition::BackRight:
      return motorBackRight->getRps();
    default:
      throw std::invalid_argument("unknown motor");
  }
}



std::shared_ptr<construction::steeringUnit::SteeringUnit>
Lupus::getSteeringUnit(construction::steeringUnit::SteeringUnitPosition position)
{
  switch (position)
  {
    case construction::steeringUnit::SteeringUnitPosition::Left:
      return steeringLeft;
    case construction::steeringUnit::SteeringUnitPosition::Right:
      return steeringRight;
    default:
      throw std::invalid_argument("get steering: unknown steering");
  }
}

void Lupus::setDirection(
  construction::steeringUnit::SteeringUnitPosition position,
  float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  switch (position)
  {
    case construction::steeringUnit::SteeringUnitPosition::Left:
      steeringLeft->setDirection(direction);
      break;
    case construction::steeringUnit::SteeringUnitPosition::Right:
      steeringRight->setDirection(direction);
      break;
  }
}

float Lupus::getDirection(construction::steeringUnit::SteeringUnitPosition position)
{
  switch (position)
  {
    case construction::steeringUnit::SteeringUnitPosition::Left:
      return steeringLeft->getDirection();
    case construction::steeringUnit::SteeringUnitPosition::Right:
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
