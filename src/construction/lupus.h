#ifndef CONSTRUCTION_LOCAL_CONSTRUCTION_H
#define CONSTRUCTION_LOCAL_CONSTRUCTION_H

#include <memory>

#include "lupus.h"
#include "steering.h"
#include "motor.h"
#include "distance_sensor.h"

namespace lupus::construction
{

class Lupus
{
  private:
    std::shared_ptr<steeringUnit::ISteering> steeringLeft;
    std::shared_ptr<steeringUnit::ISteering> steeringRight;

    std::shared_ptr<motor::IMotor> motorFrontLeft;
    std::shared_ptr<motor::IMotor> motorFrontRight;
    std::shared_ptr<motor::IMotor> motorBackLeft;
    std::shared_ptr<motor::IMotor> motorBackRight;

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
      std::shared_ptr<steeringUnit::ISteering> steeringLeft,
      std::shared_ptr<steeringUnit::ISteering> steeringRight,

      std::shared_ptr<motor::IMotor> motorFrontLeft,
      std::shared_ptr<motor::IMotor> motorFrontRight,
      std::shared_ptr<motor::IMotor> motorBackLeft,
      std::shared_ptr<motor::IMotor> motorBackRight,

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

    std::shared_ptr<motor::IMotor> getMotor(motor::Motor motor);
    void setPower(motor::Motor motor, float power);
    float getPower(motor::Motor motor);
    float getRps(motor::Motor motor);

    std::shared_ptr<steeringUnit::ISteering> getSteering(steeringUnit::SteeringUnit);
    void setDirection(steeringUnit::SteeringUnit steering, float direction);
    float getDirection(steeringUnit::SteeringUnit steering);

    std::shared_ptr<distanceSensor::IDistanceSensor> getDistanceSensor(distanceSensor::DistanceSensor);
    float getDistance(distanceSensor::DistanceSensor);
};

}

#endif /* CONSTRUCTION_LOCAL_CONSTRUCTION_H */
