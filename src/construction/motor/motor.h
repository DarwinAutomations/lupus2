#ifndef CONSTRUCTION_MOTOR_MOTOR_H
#define CONSTRUCTION_MOTOR_MOTOR_H

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

class Motor
{
private:
  std::shared_ptr<lupus::construction::motor::propulsionUnit::PropulsionUnit> propulsionUnit;
  std::shared_ptr<rpsSensor::HallRpsSensor> rpsSensor;

public:
  Motor (
    std::shared_ptr<lupus::construction::motor::propulsionUnit::PropulsionUnit> propulsionUnit,
    std::shared_ptr<rpsSensor::HallRpsSensor> rpsSensor);
  virtual ~Motor () = default;

  void setPower(float power);
  float getPower();
  float getValue();
  float getRps();
};

}

#endif /* CONSTRUCTION_MOTOR_MOTOR_H */
