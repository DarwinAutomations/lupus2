#ifndef PWM_CONTROL_UNIT_H
#define PWM_CONTROL_UNIT_H

#include "control_unit.h"
#include "pwm_driver.h"

namespace lupus::simulations
{

class SimulatedControlUnit : public lupus::IControlUnit
{
private:
  float value;

public:
  SimulatedControlUnit () = default;
  virtual ~SimulatedControlUnit () = default;
  void setPower(float power) override;
};

} // namespace lupus::simulations

#endif /* SIMULATIONS_CONTROL_UNIT_H */
