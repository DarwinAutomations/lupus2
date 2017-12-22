#ifndef SIMULATIONS_CONTROL_UNIT_H
#define SIMULATIONS_CONTROL_UNIT_H

#include "control_unit.h"

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
  float getPower() override;
};

} // namespace lupus::simulations

#endif /* SIMULATIONS_CONTROL_UNIT_H */
