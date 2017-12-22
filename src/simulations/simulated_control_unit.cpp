#include <stdexcept>
#include "pwm_control_unit.h"

namespace lupus::pwm
{
void SimulatedControlUnit::setPower(float power)
{
  if (power > 1 || power < 0)
  {
    throw std::invalid_argument("power not in range 0, 1");
  }
  value = power;
}

} // namespace lupus::pwm
