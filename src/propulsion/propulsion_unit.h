#ifndef PROPULSION_PROPULSION_UNIT_H
#define PROPULSION_PROPULSION_UNIT_H

#include <memory>

#include "control_unit.h"
#include "hall_sensor.h"
#include "pwm_driver.h"

namespace lupus::propulsion
{

class PropulsionUnit
{
private:
  std::shared_ptr<pwm::PwmDriver> pwmDriver;
  int channel;
  float power;
  int rawPower;

  float forwardMin;
  float forwardMax;
  float backwardMin;
  float backwardMax;

public:
  PropulsionUnit (
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
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

} // namespace lupus::propulsion

#endif /* PROPULSION_PROPULSION_UNIT_H */
