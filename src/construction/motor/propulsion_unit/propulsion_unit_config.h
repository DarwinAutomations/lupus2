#ifndef CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_CONFIGURATION_H
#define CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_CONFIGURATION_H

#include <libconfig.h++>

namespace lupus::construction::motor::propulsionUnit
{

class PropulsionUnitConfiguration
{
  public:
    const int pin;
    const int forwardMin;
    const int forwardMax;
    const int backwardMin;
    const int backwardMax;


    PropulsionUnitConfiguration(
      int pin,
      int forwardMin,
      int forwardMax,
      int backwardMin,
      int backwardMax);

    static PropulsionUnitConfiguration fromSetting(
      libconfig::Setting& settings);
    void intoSetting(libconfig::Setting& settings);
};

}

#endif /* CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_CONFIGURATION_H */
