#ifndef PWM_CONTROL_UNIT_H
#define PWM_CONTROL_UNIT_H

#include <memory>

#include "pwm_driver.h"

namespace lupus::drivers::pwm
{

class PwmControlUnit
{
  private:
    std::shared_ptr<PwmDriver> pwmDriver;
    int channel;
    float min;
    float max;
    float value;

  public:
    PwmControlUnit (
      std::shared_ptr<PwmDriver> pwmDriver,
      int channel,
      int min,
      int max);
    virtual ~PwmControlUnit () = default;
    void setPower(float power);
    float getPower();
};

}

#endif /* PWM_CONTROL_UNIT_H */
