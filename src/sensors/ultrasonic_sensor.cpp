#include <stdexcept>
#include "ultrasonic_sensor.h"

namespace lupus::sensors
{

UltrasonicSensor::UltrasonicSensor(UltrasonicService* service, int range, int accuracy, float angle, int trigger, int echo)
{
  if(!service)
  {
    throw std::invalid_argument("ultrasonic_service must not be null");
  }

  this->service = service;
  this->range = range;
  this->accuracy = accuracy;
  this->angle = angle;

  this->id = this->service->registerSensor(trigger, echo);
}

UltrasonicSensor::~UltrasonicSensor()
{
  this->service->deregisterSensor(this->id);
}

int UltrasonicSensor::getDistance()
{
  return this->service->getDistance(this->id);
}

int UltrasonicSensor::getRange()
{
  return this->range;
}

int UltrasonicSensor::getAccuracy()
{
  return this->accuracy;
}

float UltrasonicSensor::getAngle()
{
  return this->angle;
}

} // namespace lupus::sensors
