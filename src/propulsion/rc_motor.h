#ifndef PROPULSION_RC_MOTOR_H
#define PROPULSION_RC_MOTOR_H

#include <memory>

#include "motor.h"
#include "propulsion_unit.h"
#include "rps_sensor.h"

namespace lupus::propulsion
{

class RCMotor final: public IMotor
{
private:
  std::shared_ptr<PropulsionUnit> propulsionUnit;
  std::shared_ptr<sensors::IRpsSensor> rpsSensor;

public:
  RCMotor (
    std::shared_ptr<PropulsionUnit> propulsionUnit,
    std::shared_ptr<sensors::IRpsSensor> rpsSensor);
  virtual ~RCMotor () = default;

  void setPower(float power);
  float getPower();
  float getRawPower();
  float getRps();
};

} // namespace lupus::propulsion

#endif /* PROPULSION_RC_MOTOR_H */
