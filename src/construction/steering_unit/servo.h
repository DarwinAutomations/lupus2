#ifndef NAVIGATION_SERVO_H
#define NAVIGATION_SERVO_H

#include <memory>

#include "pwm_driver.h"

namespace lupus::construction::steeringUnit
{

class Servo
{
private:
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver;
  int channel;
  float value;
  int rawValue;
  float min;
  float max;
public:
  Servo(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    int channel,
    float min,
    float max);
  virtual ~Servo () = default;
  virtual void setDirection(float direction);
  virtual float getDirection();
  virtual int getRawDirection();
};

}

#endif /* NAVIGATION_SERVO_H */
