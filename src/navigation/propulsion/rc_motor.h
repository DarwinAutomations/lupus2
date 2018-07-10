#ifndef NAVIGATION_PROPULSION_RC_MOTOR_H
#define NAVIGATION_PROPULSION_RC_MOTOR_H

#include <memory>

#include "motor.h"
#include "propulsion_unit.h"
#include "rps_sensor.h"

namespace lupus::navigation::propulsion
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
  float getRps();
};

} // namespace lupus::navigation::propulsion

#endif /* NAVIGATION_PROPULSION_RC_MOTOR_H */
