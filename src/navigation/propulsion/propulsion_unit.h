#ifndef NAVIGATION_PROPULSION_PROPULSION_UNIT_H
#define NAVIGATION_PROPULSION_PROPULSION_UNIT_H

#include <memory>

#include "control_unit.h"
#include "hall_sensor.h"
#include "pwm_driver.h"

namespace lupus::navigation::propulsion
{

class PropulsionUnit
{
private:
  std::shared_ptr<pwm::PwmDriver> pwmDriver;
  int channel;
  float power;

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
};

} // namespace lupus::navigation::propulsion

#endif /* NAVIGATION_PROPULSION_PROPULSION_UNIT_H */
