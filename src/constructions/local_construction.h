#ifndef CONSTRUCTION_LOCAL_CONSTRUCTION_H
#define CONSTRUCTION_LOCAL_CONSTRUCTION_H

#include <memory>

#include "construction.h"
#include "steering.h"
#include "motor.h"
#include "distance_sensor.h"

namespace lupus::constructions
{

class LocalConstruction: public IConstruction
{
  private:
    std::shared_ptr<navigation::ISteering> steeringLeft;
    std::shared_ptr<navigation::ISteering> steeringRight;

    std::shared_ptr<propulsion::IMotor> motorFrontLeft;
    std::shared_ptr<propulsion::IMotor> motorFrontRight;
    std::shared_ptr<propulsion::IMotor> motorBackLeft;
    std::shared_ptr<propulsion::IMotor> motorBackRight;

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
      std::shared_ptr<navigation::ISteering> steeringLeft,
      std::shared_ptr<navigation::ISteering> steeringRight,

      std::shared_ptr<propulsion::IMotor> motorFrontLeft,
      std::shared_ptr<propulsion::IMotor> motorFrontRight,
      std::shared_ptr<propulsion::IMotor> motorBackLeft,
      std::shared_ptr<propulsion::IMotor> motorBackRight,

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

    void setPower(propulsion::Motor motor, float power);
    float getPower(propulsion::Motor motor);
    float getRps(propulsion::Motor motor);
    void setDirection(navigation::Steering steering, float direction);
    float getDirection(navigation::Steering steering);
};

} // namespace lupus::constructions

#endif /* CONSTRUCTION_LOCAL_CONSTRUCTION_H */
