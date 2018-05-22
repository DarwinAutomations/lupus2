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
  navigation::PropulsionUnit *propulsionBackRight,

  sensors::IDistanceSensor *distanceFrontLeft,
  sensors::IDistanceSensor *distanceFrontCenterLeft,
  sensors::IDistanceSensor *distanceFrontCenterRight,
  sensors::IDistanceSensor *distanceFrontRight,
  sensors::IDistanceSensor *distanceBackLeft,
  sensors::IDistanceSensor *distanceBackCenterLeft,
  sensors::IDistanceSensor *distanceBackCenterRight,
  sensors::IDistanceSensor *distanceBackRight
)
{
  if(
    !steeringLeft ||
    !steeringRight ||
    !propulsionFrontLeft ||
    !propulsionFrontRight ||
    !propulsionBackLeft ||
    !propulsionBackRight ||
    !distanceFrontLeft || 
    !distanceFrontCenterLeft || 
    !distanceFrontCenterRight || 
    !distanceFrontRight || 
    !distanceBackLeft || 
    !distanceBackCenterLeft || 
    !distanceBackCenterRight || 
    !distanceBackRight
  )
  {
    throw std::invalid_argument("none of the parameters can be null");
  }

  // steering
  this->steeringLeft = steeringLeft;
  this->steeringRight = steeringRight;

  // propulsion
  this->propulsionFrontLeft = propulsionFrontLeft;
  this->propulsionFrontRight = propulsionFrontRight;
  this->propulsionBackLeft = propulsionBackLeft;
  this->propulsionBackRight = propulsionBackRight;

  // sensors
  this->distanceFrontLeft = distanceFrontLeft;
  this->distanceFrontCenterLeft = distanceFrontCenterLeft;
  this->distanceFrontCenterRight = distanceFrontCenterRight;
  this->distanceFrontRight = distanceFrontRight;
  this->distanceBackLeft = distanceBackLeft;
  this->distanceBackCenterLeft = distanceBackCenterLeft;
  this->distanceBackCenterRight = distanceBackCenterRight;
  this->distanceBackRight = distanceBackRight;

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

void getSurroundings(int resolution, int *result)
{
  for(int i = 0; i < resolution; i++)
  {
    result[i] = sensors::IDistanceSensor::DistanceUnknown;
  }
}

void getSerroundingsSector(float sectorStart, float sectorStop, int resolution, int *result)
{
  for(int i = 0; i < resolution; i++)
  {
    result[i] = sensors::IDistanceSensor::DistanceUnknown;
  }
}

} // namespace lupus::navigation
