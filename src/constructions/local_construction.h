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
 
    void setPropulsionFrontLeftPower(float power);
    void setPropulsionFrontRightPower(float power);
    void setPropulsionBackLeftPower(float power);
    void setPropulsionBackRightPower(float power);
    float getPropulsionFrontLeftPower();
    float getPropulsionFrontRightPower();
    float getPropulsionBackLeftPower();
    float getPropulsionBackRightPower();
    void setSteeringLeftDirection(float direction);
    void setSteeringRightDirection(float direction);
    float getSteeringLeftDirection();
    float getSteeringRightDirection();
};

} // namespace lupus::constructions

#endif /* CONSTRUCTION_LOCAL_CONSTRUCTION_H */
