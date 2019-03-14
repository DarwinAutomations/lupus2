#include <libconfig.h++>
#include <memory>
#include "distance_sensor_config.h"

namespace lupus::construction::distanceSensor
{

DistanceSensorConfiguration::DistanceSensorConfiguration(
  float measurementRangeMin,
  float measurementRangeMax,
  float measurementAccuracy,
  float measurementAngle,
  int triggerPin,
  int echoPin
):
  measurementRangeMin(measurementRangeMin),
  measurementRangeMax(measurementRangeMax),
  measurementAccuracy(measurementAccuracy),
  measurementAngle(measurementAngle),
  triggerPin(triggerPin),
  echoPin(echoPin) {}

DistanceSensorConfiguration
  DistanceSensorConfiguration::fromSetting(libconfig::Setting& settings)
{
  float measurementRangeMin = settings.lookup("measurementRangeMin");
  float measurementRangeMax = settings.lookup("measurementRangeMax");
  float measurementAccuracy = settings.lookup("measurementAccuracy");
  float measurementAngle    = settings.lookup("measurementAngle");
  int triggerPin            = settings.lookup("triggerPin");
  int echoPin               = settings.lookup("echoPin");

  return DistanceSensorConfiguration(
    measurementRangeMin,
    measurementRangeMax,
    measurementAccuracy,
    measurementAngle,
    triggerPin,
    echoPin
  );
}

void DistanceSensorConfiguration::intoSetting(libconfig::Setting& settings)
{
  settings.add("measurementRangeMin", libconfig::Setting::Type::TypeFloat)  = measurementRangeMin;
  settings.add("measurementRangeMax", libconfig::Setting::Type::TypeFloat)  = measurementRangeMax;
  settings.add("measurementAccuracy", libconfig::Setting::Type::TypeFloat)  = measurementAccuracy;
  settings.add("measurementAngle", libconfig::Setting::Type::TypeFloat)     = measurementAngle;
  settings.add("triggerPin", libconfig::Setting::Type::TypeInt)             = triggerPin;
  settings.add("echoPin", libconfig::Setting::Type::TypeInt)                = echoPin;
}

}
