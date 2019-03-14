#ifndef LUPUS_CONSTRUCTION_DISTANCE_SENSOR_CONFIGURATION_H
#define LUPUS_CONSTRUCTION_DISTANCE_SENSOR_CONFIGURATION_H

#include <libconfig.h++>
#include <memory>

namespace lupus::construction::distanceSensor
{

enum DistanceSensor
{
  FrontLeft,
  FrontCenterLeft,
  FrontCenterRight,
  FrontRight,
  BackLeft,
  BackCenterLeft,
  BackCenterRight,
  BackRight
};

class DistanceSensorConfiguration
{
  public:
    const float measurementRangeMin;
    const float measurementRangeMax;
    const float measurementAccuracy;
    const float measurementAngle;
    const int triggerPin;
    const int echoPin;

    DistanceSensorConfiguration(
      float measurementRangeMin,
      float measurementRangeMax,
      float measurementAccuracy,
      float measurementAngle,
      int triggerPin,
      int echoPin);

    static DistanceSensorConfiguration fromSetting(libconfig::Setting& settings);

    void intoSetting(libconfig::Setting& settings);

};
}

#endif /* LUPUS_CONSTRUCTION_DISTANCE_SENSOR_CONFIGURATION_H */
