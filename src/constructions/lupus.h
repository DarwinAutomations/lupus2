#ifndef CONSTRUCTION_LUPUS_H
#define CONSTRUCTION_LUPUS_H

#include "steering_unit.h"
#include "propulsion_unit.h"
#include "distance_sensor.h"

namespace lupus::construction
{

class Lupus
{
  private:
    navigation::SteeringUnit *steeringLeft;
    navigation::SteeringUnit *steeringRight;

    navigation::PropulsionUnit *propulsionFrontLeft;
    navigation::PropulsionUnit *propulsionFrontRight;
    navigation::PropulsionUnit *propulsionBackLeft;
    navigation::PropulsionUnit *propulsionBackRight;

    sensors::IDistanceSensor *distanceFrontLeft;
    sensors::IDistanceSensor *distanceFrontCenterLeft;
    sensors::IDistanceSensor *distanceFrontCenterRight;
    sensors::IDistanceSensor *distanceFrontRight;
    sensors::IDistanceSensor *distanceBackLeft;
    sensors::IDistanceSensor *distanceBackCenterLeft;
    sensors::IDistanceSensor *distanceBackCenterRight;
    sensors::IDistanceSensor *distanceBackRight;

  public:
    Lupus (
      navigation::SteeringUnit *steeringLeft,
      navigation::SteeringUnit *steeringRight,
      
      navigation::PropulsionUnit *propulsionFrontLeft,
      navigation::PropulsionUnit *propulsionFrontRight,
      navigation::PropulsionUnit *propulsionBackLeft,
      navigation::PropulsionUnit *propulsionBackRight,

      sensors::IDistanceSensor *distanceFrontLeft,
      sensors::IDistanceSensor *distanceFrontCenterLeft,
      sensors::IDistanceSensor *distanceFrontCenterRight,
      sensors::IDistanceSensor *distanceFrontRight,
      sensors::IDistanceSensor *distanceBackLeft,
      sensors::IDistanceSensor *distanceBackCenterLeft,
      sensors::IDistanceSensor *distanceBackCenterRight,
      sensors::IDistanceSensor *distanceBackRight
    );
    virtual ~Lupus () = default;

    void setPower(float power);
    float getPower();
    void setDirection(float direction);
    float getDirection();
};

} // namespace lupus::navigation

#endif /* CONSTRUCTION_LUPUS_H */
