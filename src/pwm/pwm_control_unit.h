#ifndef PWM_CONTROL_UNIT_H
#define PWM_CONTROL_UNIT_H

#include "control_unit.h"
#include "pwm_driver.h"

namespace lupus::pwm
{

class PwmControlUnit : public lupus::IControlUnit{
  private:
    PwmDriver* pwmDriver;
    int channel;
    float min;
    float max;

  public:
    PwmControlUnit (
      PwmDriver* pwmDriver,
      int channel,
      int min,
      int max);
    virtual ~PwmControlUnit () = default;
    void setPower(float power) override;
};

} // namespace lupus::pwm

#endif /* PWM_CONTROL_UNIT_H */
