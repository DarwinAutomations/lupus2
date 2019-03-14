#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "distance_sensor_config.h"

namespace lupus::construction::distanceSensor
{

class IDistanceSensor
{
public:
  virtual ~IDistanceSensor() = default;
  virtual void setDistance(float newDistance) = 0;
  virtual float getDistance() = 0;
  virtual DistanceSensorConfiguration getConfiguration() = 0;

  const static int DistanceUnknown = -2;
  const static int DistanceOutOfRange = -1;
};

}

#endif /* DISTANCE__SENSOR_H */
