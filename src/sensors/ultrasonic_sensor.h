#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <memory>

#include "distance_sensor.h"
#include "ultrasonic_service.h"


namespace lupus::sensors
{

class UltrasonicSensor : public IDistanceSensor
{
  private:
    std::shared_ptr<UltrasonicService> service;
    int id;

    float rangeStart;
    float rangeEnd;
    float accuracy;
    float angle;

  public:
    UltrasonicSensor(
      std::shared_ptr<UltrasonicService> service,
      float rangeStart,
      float rangeEnd,
      float accuracy,
      float angle,
      int trigger,
      int echo);
    virtual ~UltrasonicSensor();
    float getDistance();
    float getAccuracy() override;
    float getAngle() override;
    float getRangeStart() override;
    float getRangeEnd() override;

};

} // namespace lupus::sensors

#endif /* ULTRASONIC_SENSOR_H */
