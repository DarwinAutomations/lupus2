#include "steering_unit_config.h"

namespace lupus::construction::steeringUnit
{

SteeringUnitConfiguration::SteeringUnitConfiguration(
  int pin,
  int min,
  int max)
:
  pin(pin),
  min(min),
  max(max)
{}

SteeringUnitConfiguration
  SteeringUnitConfiguration::fromSetting(libconfig::Setting& settings)
{
  int pin = settings.lookup("pin");
  int min = settings.lookup("min");
  int max = settings.lookup("max");

  printf("%i-%i\n", min, max);

  return SteeringUnitConfiguration(pin, min, max);
}

void SteeringUnitConfiguration::intoSetting(libconfig::Setting& settings)
{
  settings.add("pin", libconfig::Setting::Type::TypeInt) = pin;
  settings.add("min", libconfig::Setting::Type::TypeInt) = min;
  settings.add("max", libconfig::Setting::Type::TypeInt) = max;
}

}
