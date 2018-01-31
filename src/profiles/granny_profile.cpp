#include <stdexcept>
#include <math.h>

#include "granny_profile.h"

namespace lupus::profiles
{
float GrannyProfile::computeAcceleration(float acceleration)
{
  if(acceleration > 1 || acceleration < -1)
  {
    throw std::invalid_argument("acceleration not in range -1, +1");
  }
  return std::pow(acceleration, 3) / 10.0f;
}

} // namespace lupus::profiles
