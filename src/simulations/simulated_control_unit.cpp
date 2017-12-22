#include <stdexcept>
#include "simulated_control_unit.h"

namespace lupus::simulations
{
  void SimulatedControlUnit::setPower(float power)
  {
    if (power > 1 || power < 0)
    {
      throw std::invalid_argument("power not in range 0, 1");
    }
    this->value = power;
  }

  float SimulatedControlUnit::getPower()
  {
    return this->value;
  }

} // namespace lupus::simulations
