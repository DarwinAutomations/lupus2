#ifndef CONSTRUCTION_MOTOR_RC_MOTOR_H
#define CONSTRUCTION_MOTOR_RC_MOTOR_H

#include <memory>

#include "propulsion_unit.h"
#include "hall_rps_sensor.h"

namespace lupus::construction::motor
{

enum MotorPosition
{
  FrontLeft,
  FrontRight,
  BackLeft,
  BackRight
};

class RCMotor final
{
private:
  std::shared_ptr<PropulsionUnit> propulsionUnit;
  std::shared_ptr<construction::rpsSensor::HallRpsSensor> rpsSensor;

public:
  RCMotor (
    std::shared_ptr<PropulsionUnit> propulsionUnit,
    std::shared_ptr<construction::rpsSensor::HallRpsSensor> rpsSensor);
  virtual ~RCMotor () = default;

  void setPower(float power);
  float getPower();
  float getRawPower();
  float getRps();
};

}

#endif /* CONSTRUCTION_MOTOR_RC_MOTOR_H */
