#ifndef NAVIGATION_RC_STEERING_H
#define NAVIGATION_RC_STEERING_H

#include <memory>
#include "pwm_driver.h"

namespace lupus::construction::steeringUnit
{

enum SteeringUnitPosition
{
  Left,
  Right
};

class SteeringUnit
{
private:
  // why not pwm_control_unit? its currently unused and offers the needed func.
  std::shared_ptr<drivers::pwm::PwmDriver> driver;
  float direction;
  int value;

  // configuration
  int channel;
  float min;
  float max;
  void setPwm(float factor);

public:
  SteeringUnit (
    std::shared_ptr<drivers::pwm::PwmDriver> driver,
    int channel,
    float min,
    float max);
  virtual ~SteeringUnit () = default;

  void setDirection(float direction);
  float getDirection();
  int getValue();
};

}

#endif /* NAVIGATION_RC_STEERING_H */
