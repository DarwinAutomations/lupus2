#include "hall_rps_sensor_config.h"

namespace lupus::construction::motor::rpsSensor
{

HallRpsSensorConfiguration::HallRpsSensorConfiguration(int pin): pin(pin) {}

HallRpsSensorConfiguration
  HallRpsSensorConfiguration::fromSetting(libconfig::Setting& settings)
{
  int pin = settings.lookup("pin");
  return HallRpsSensorConfiguration(pin);
}

void HallRpsSensorConfiguration::intoSetting(libconfig::Setting& settings)
{
  settings.add("pin", libconfig::Setting::Type::TypeInt) = pin;
}

}
