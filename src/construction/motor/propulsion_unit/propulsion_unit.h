#ifndef CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_H
#define CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_H

#include <memory>

#include "pwm_driver.h"

namespace lupus::construction::motor::propulsionUnit
{

class PropulsionUnit
{
private:
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver;
  float power;
  int rawPower;

  // configuration
  int channel;
  float forwardMin;
  float forwardMax;
  float backwardMin;
  float backwardMax;

public:
  PropulsionUnit (
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    int channel,
    float forwardMin,
    float forwardMax,
    float backwardMin,
    float backwardMax);
  virtual ~PropulsionUnit () = default;

  void setPower(float power);
  float getPower();
  int getRawPower();
};

}

#endif /* CONSTRUCTION_MOTOR_PROPULSION_UNIT_PROPULSION_UNIT_H */
