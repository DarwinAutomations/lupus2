#ifndef CONSTRUCTION_LOCAL_CONSTRUCTION_H
#define CONSTRUCTION_LOCAL_CONSTRUCTION_H

#include <memory>

#include "lupus.h"
#include "steering_unit.h"
#include "rc_motor.h"
#include "distance_sensor.h"

namespace lupus::construction
{

class Lupus
{
  private:
    std::shared_ptr<steeringUnit::SteeringUnit> steeringLeft;
    std::shared_ptr<steeringUnit::SteeringUnit> steeringRight;

    std::shared_ptr<motor::RCMotor> motorFrontLeft;
    std::shared_ptr<motor::RCMotor> motorFrontRight;
    std::shared_ptr<motor::RCMotor> motorBackLeft;
    std::shared_ptr<motor::RCMotor> motorBackRight;

    std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontLeft;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontCenterLeft;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontCenterRight;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontRight;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackLeft;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackCenterLeft;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackCenterRight;
    std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackRight;

  public:
    Lupus (
      std::shared_ptr<steeringUnit::SteeringUnit> steeringLeft,
      std::shared_ptr<steeringUnit::SteeringUnit> steeringRight,

      std::shared_ptr<motor::RCMotor> motorFrontLeft,
      std::shared_ptr<motor::RCMotor> motorFrontRight,
      std::shared_ptr<motor::RCMotor> motorBackLeft,
      std::shared_ptr<motor::RCMotor> motorBackRight,

      std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontLeft,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontCenterLeft,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontCenterRight,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceFrontRight,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackLeft,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackCenterLeft,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackCenterRight,
      std::shared_ptr<distanceSensor::IDistanceSensor> distanceBackRight
    );
    virtual ~Lupus () = default;

    std::shared_ptr<motor::RCMotor> getMotor(motor::MotorPosition motor);
    void setPower(motor::MotorPosition motor, float power);
    float getPower(motor::MotorPosition motor);
    float getRps(motor::MotorPosition motor);

    std::shared_ptr<steeringUnit::SteeringUnit> getSteeringUnit(steeringUnit::SteeringUnitPosition position);
    void setDirection(steeringUnit::SteeringUnitPosition position, float direction);
    float getDirection(steeringUnit::SteeringUnitPosition position);

    std::shared_ptr<distanceSensor::IDistanceSensor> getDistanceSensor(distanceSensor::DistanceSensor);
    float getDistance(distanceSensor::DistanceSensor);
};

}

#endif /* CONSTRUCTION_LOCAL_CONSTRUCTION_H */
