#include "propulsion_unit_config.h"

namespace lupus::construction::motor::propulsionUnit
{

PropulsionUnitConfiguration::PropulsionUnitConfiguration(
  int pin,
  int forwardMin,
  int forwardMax,
  int backwardMin,
  int backwardMax)
:
  pin(pin),
  forwardMin(forwardMin),
  forwardMax(forwardMax),
  backwardMin(backwardMin),
  backwardMax(backwardMax)
{}

PropulsionUnitConfiguration
  PropulsionUnitConfiguration::fromSetting(libconfig::Setting& settings)
{
  int pin = settings.lookup("pin");
  int forwardMin = settings.lookup("forwardMin");
  int forwardMax = settings.lookup("forwardMax");
  int backwardMin = settings.lookup("backwardMin");
  int backwardMax = settings.lookup("backwardMax");

  return PropulsionUnitConfiguration(
    pin,
    forwardMin,
    forwardMax,
    backwardMin,
    backwardMax);
}

void PropulsionUnitConfiguration::intoSetting(libconfig::Setting& settings)
{
  settings.add("pin", libconfig::Setting::Type::TypeInt) = pin;
  settings.add("forwardMin", libconfig::Setting::Type::TypeInt) = forwardMin;
  settings.add("forwardMax", libconfig::Setting::Type::TypeInt) = forwardMax;
  settings.add("backwardMin", libconfig::Setting::Type::TypeInt) = backwardMin;
  settings.add("backwardMax", libconfig::Setting::Type::TypeInt) = backwardMax;
}

}
