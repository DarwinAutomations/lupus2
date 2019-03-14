#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <memory>

#include "distance_sensor.h"
#include "ultrasonic_service.h"
#include "distance_sensor_config.h"


namespace lupus::construction::distanceSensor
{

class UltrasonicSensor : public IDistanceSensor
{
  private:
    float distance;
    DistanceSensorConfiguration configuration;

  public:
    UltrasonicSensor(DistanceSensorConfiguration config);
    void setDistance(float newDistance) override;
    float getDistance() override;
    DistanceSensorConfiguration getConfiguration();
};

}

#endif /* ULTRASONIC_SENSOR_H */
