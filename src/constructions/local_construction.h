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

    std::shared_ptr<propulsion::IMotor> getMotor(propulsion::Motor motor);
    void setPower(propulsion::Motor motor, float power);
    float getPower(propulsion::Motor motor);
    float getRps(propulsion::Motor motor);

    std::shared_ptr<navigation::ISteering> getSteering(navigation::SteeringUnit);
    void setDirection(navigation::SteeringUnit steering, float direction);
    float getDirection(navigation::SteeringUnit steering);

    std::shared_ptr<sensors::IDistanceSensor> getDistanceSensor(sensors::DistanceSensor);
    float getDistance(sensors::DistanceSensor);
};

} // namespace lupus::constructions

#endif /* CONSTRUCTION_LOCAL_CONSTRUCTION_H */
