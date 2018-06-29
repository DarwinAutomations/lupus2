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
    
    int range;
    int accuracy;
    float angle;

  public:
    UltrasonicSensor(std::shared_ptr<UltrasonicService> service, int range, int accuracy, float angle, int trigger, int echo);
    virtual ~UltrasonicSensor();
    int getDistance();
    int getAccuracy() override;
    float getAngle() override;
    int getRange() override;

};

} // namespace lupus::sensors

#endif /* ULTRASONIC_SENSOR_H */
