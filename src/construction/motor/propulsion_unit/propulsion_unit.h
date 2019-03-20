#ifndef CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_H
#define CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_H

#include <memory>

#include "pwm_driver.h"
#include "propulsion_unit_config.h"

namespace lupus::construction::motor::propulsionUnit
{

class PropulsionUnit
{
private:
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver;
  float power;
  int value;
  PropulsionUnitConfiguration configuration;

public:
  PropulsionUnit (
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    PropulsionUnitConfiguration config);
  virtual ~PropulsionUnit () = default;

  void setPower(float power);
  float getPower();
  int getValue();
};

}

#endif /* CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_H */
