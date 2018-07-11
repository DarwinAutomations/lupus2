#include <stdexcept>
#include "ultrasonic_sensor.h"

namespace lupus::sensors
{

UltrasonicSensor::UltrasonicSensor(
  std::shared_ptr<UltrasonicService> service,
  float rangeStart,
  float rangeEnd,
  float accuracy,
  float angle,
  int trigger,
  int echo)
{
  if(!service)
  {
    throw std::invalid_argument("ultrasonic_service must not be null");
  }

  this->service = std::move(service);
  this->rangeStart = rangeStart;
  this->rangeEnd = rangeEnd;
  this->accuracy = accuracy;
  this->angle = angle;

  this->id = this->service->registerSensor(trigger, echo);
}

UltrasonicSensor::~UltrasonicSensor()
{
  this->service->deregisterSensor(this->id);
}

float UltrasonicSensor::getDistance()
{
  return this->service->getDistance(this->id);
}

float UltrasonicSensor::getRangeStart()
{
  return this->rangeStart;
}

float UltrasonicSensor::getRangeEnd()
{
  return this->rangeEnd;
}

float UltrasonicSensor::getAccuracy()
{
  return this->accuracy;
}

float UltrasonicSensor::getAngle()
{
  return this->angle;
}

} // namespace lupus::sensors
