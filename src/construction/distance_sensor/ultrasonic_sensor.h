#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <memory>

#include "distance_sensor.h"
#include "ultrasonic_service.h"


namespace lupus::construction::distanceSensor
{

class UltrasonicSensor : public IDistanceSensor
{
  private:
    float distance;
    float rangeStart;
    float rangeEnd;
    float accuracy;
    float angle;
    int triggerPin;
    int echoPin;

  public:
    UltrasonicSensor(
      float rangeStart,
      float rangeEnd,
      float accuracy,
      float angle,
      int trigger,
      int echo);
    void setDistance(float newDistance) override;
    float getDistance() override;
    float getAccuracy() override;
    float getAngle() override;
    float getRangeStart() override;
    float getRangeEnd() override;
    int getTriggerPin() override;
    int getEchoPin() override;
};

}

#endif /* ULTRASONIC_SENSOR_H */
