#ifndef LUPUS_CONSTRUCTION_STEERING_UNIT_STEERING_UNITCONFIGURATION_H
#define LUPUS_CONSTRUCTION_STEERING_UNIT_STEERING_UNITCONFIGURATION_H

#include <libconfig.h++>

namespace lupus::construction::steeringUnit
{

class SteeringUnitConfiguration
{
  public:
    const int pin;
    const int min;
    const int max;

    SteeringUnitConfiguration(
      int pin,
      int min,
      int max);

    static SteeringUnitConfiguration fromSetting(
      libconfig::Setting& settings);
    void intoSetting(libconfig::Setting& settings);

};
}

#endif /* LUPUS_CONSTRUCTION_STEERING_UNIT_STEERING_UNITCONFIGURATION_H */
