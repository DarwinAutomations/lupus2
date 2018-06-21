#ifndef CONSTRUCTION_LOCAL_CONSTRUCTION_H
#define CONSTRUCTION_LOCAL_CONSTRUCTION_H

#include <memory>

#include "construction.h"
#include "steering_unit.h"
#include "propulsion_unit.h"
#include "distance_sensor.h"

namespace lupus::constructions
{

class LocalConstruction: public IConstruction
{
  private:
    std::shared_ptr<navigation::SteeringUnit> steeringLeft;
    std::shared_ptr<navigation::SteeringUnit> steeringRight;

    std::shared_ptr<navigation::PropulsionUnit> propulsionFrontLeft;
    std::shared_ptr<navigation::PropulsionUnit> propulsionFrontRight;
    std::shared_ptr<navigation::PropulsionUnit> propulsionBackLeft;
    std::shared_ptr<navigation::PropulsionUnit> propulsionBackRight;

    std::shared_ptr<sensors::IDistanceSensor> distanceFrontLeft;
    std::shared_ptr<sensors::IDistanceSensor> distanceFrontCenterLeft;
    std::shared_ptr<sensors::IDistanceSensor> distanceFrontCenterRight;
    std::shared_ptr<sensors::IDistanceSensor> distanceFrontRight;
    std::shared_ptr<sensors::IDistanceSensor> distanceBackLeft;
    std::shared_ptr<sensors::IDistanceSensor> distanceBackCenterLeft;
    std::shared_ptr<sensors::IDistanceSensor> distanceBackCenterRight;
    std::shared_ptr<sensors::IDistanceSensor> distanceBackRight;

  public:
    LocalConstruction (
      std::shared_ptr<navigation::SteeringUnit> steeringLeft,
      std::shared_ptr<navigation::SteeringUnit> steeringRight,
      
      std::shared_ptr<navigation::PropulsionUnit> propulsionFrontLeft,
      std::shared_ptr<navigation::PropulsionUnit> propulsionFrontRight,
      std::shared_ptr<navigation::PropulsionUnit> propulsionBackLeft,
      std::shared_ptr<navigation::PropulsionUnit> propulsionBackRight,

      std::shared_ptr<sensors::IDistanceSensor> distanceFrontLeft,
      std::shared_ptr<sensors::IDistanceSensor> distanceFrontCenterLeft,
      std::shared_ptr<sensors::IDistanceSensor> distanceFrontCenterRight,
      std::shared_ptr<sensors::IDistanceSensor> distanceFrontRight,
      std::shared_ptr<sensors::IDistanceSensor> distanceBackLeft,
      std::shared_ptr<sensors::IDistanceSensor> distanceBackCenterLeft,
      std::shared_ptr<sensors::IDistanceSensor> distanceBackCenterRight,
      std::shared_ptr<sensors::IDistanceSensor> distanceBackRight
    );
    virtual ~LocalConstruction () = default;

    void setPower(float power);
    float getPower();
    void setDirection(float direction);
    float getDirection();
};

} // namespace lupus::constructions

#endif /* CONSTRUCTION_LOCAL_CONSTRUCTION_H */
