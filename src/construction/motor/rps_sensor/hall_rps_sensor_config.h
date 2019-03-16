#ifndef LUPUS_CONSTRUCTION_MOTOR_HALL_RPS_SENSOR_CONFIGURATION_H
#define LUPUS_CONSTRUCTION_MOTOR_HALL_RPS_SENSOR_CONFIGURATION_H

#include <libconfig.h++>

namespace lupus::construction::motor::rpsSensor
{

class HallRpsSensorConfiguration
{
  public:
    const int pin;

    HallRpsSensorConfiguration(int pin);

    static HallRpsSensorConfiguration fromSetting(
      libconfig::Setting& settings);
    void intoSetting(libconfig::Setting& settings);

};
}

#endif /* LUPUS_CONSTRUCTION_MOTOR_HALL_RPS_SENSOR_CONFIGURATION_H */
