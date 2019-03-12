#ifndef PROPULSION_RC_MOTOR_H
#define PROPULSION_RC_MOTOR_H

#include <memory>

#include "motor.h"
#include "propulsion_unit.h"
#include "rps_sensor.h"

namespace lupus::construction::motor
{

class RCMotor final: public IMotor
{
private:
  std::shared_ptr<PropulsionUnit> propulsionUnit;
  std::shared_ptr<construction::rpsSensor::IRpsSensor> rpsSensor;

public:
  RCMotor (
    std::shared_ptr<PropulsionUnit> propulsionUnit,
    std::shared_ptr<construction::rpsSensor::IRpsSensor> rpsSensor);
  virtual ~RCMotor () = default;

  void setPower(float power);
  float getPower();
  float getRawPower();
  float getRps();
};

}

#endif /* PROPULSION_RC_MOTOR_H */
