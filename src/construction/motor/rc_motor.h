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

class RCMotor
{
private:
  std::shared_ptr<lupus::construction::motor::propulsionUnit::PropulsionUnit> propulsionUnit;
  std::shared_ptr<rpsSensor::HallRpsSensor> rpsSensor;

public:
  RCMotor (
    std::shared_ptr<lupus::construction::motor::propulsionUnit::PropulsionUnit> propulsionUnit,
    std::shared_ptr<rpsSensor::HallRpsSensor> rpsSensor);
  virtual ~RCMotor () = default;

  void setPower(float power);
  float getPower();
  float getRawPower();
  float getRps();
};

}

#endif /* CONSTRUCTION_MOTOR_RC_MOTOR_H */
