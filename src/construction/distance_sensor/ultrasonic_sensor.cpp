#include <stdexcept>

#include "distance_sensor.h"
#include "ultrasonic_sensor.h"

namespace lupus::construction::distanceSensor
{

UltrasonicSensor::UltrasonicSensor(
  float rangeStart,
  float rangeEnd,
  float accuracy,
  float angle,
  int trigger,
  int echo)
{
  this->distance = IDistanceSensor::DistanceUnknown;
  this->rangeStart = rangeStart;
  this->rangeEnd = rangeEnd;
  this->accuracy = accuracy;
  this->angle = angle;
  this->triggerPin = trigger;
  this->echoPin = echo;
}

void UltrasonicSensor::setDistance(float newDistance)
{
  distance = newDistance;
}

float UltrasonicSensor::getDistance()
{
  return distance;
}

float UltrasonicSensor::getRangeStart()
{
  return rangeStart;
}

float UltrasonicSensor::getRangeEnd()
{
  return rangeEnd;
}

float UltrasonicSensor::getAccuracy()
{
  return accuracy;
}

float UltrasonicSensor::getAngle()
{
  return angle;
}

int UltrasonicSensor::getTriggerPin()
{
  return triggerPin;
}

int UltrasonicSensor::getEchoPin()
{
  return echoPin;
}

}
