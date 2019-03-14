#include <stdexcept>

#include "distance_sensor.h"
#include "distance_sensor_config.h"
#include "ultrasonic_sensor.h"

namespace lupus::construction::distanceSensor
{

UltrasonicSensor::UltrasonicSensor(DistanceSensorConfiguration config)
  : configuration(config)
{
  distance = IDistanceSensor::DistanceUnknown;
}

void UltrasonicSensor::setDistance(float newDistance)
{
  distance = newDistance;
}

float UltrasonicSensor::getDistance()
{
  return distance;
}

DistanceSensorConfiguration UltrasonicSensor::getConfiguration()
{
  return configuration;
}

}
