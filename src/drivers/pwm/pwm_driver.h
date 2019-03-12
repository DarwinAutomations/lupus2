#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

namespace lupus::drivers::pwm
{

class PwmDriver
{
private:
  // Registers/etc:
  const int mode2           = 0x01;
  const int mode1           = 0x00;
  const int prescale        = 0xFE;
  const int led0_on_l       = 0x06;
  const int led0_on_h       = 0x07;
  const int led0_off_l      = 0x08;
  const int led0_off_h      = 0x09;
  const int all_led_on_l    = 0xFA;
  const int all_led_on_h    = 0xFB;
  const int all_led_off_l   = 0xFC;
  const int all_led_off_h   = 0xFD;

  // Bits:
  const int restart         = 0x80;
  const int sleep           = 0x10;
  const int allCall         = 0x01;
  const int outDrv          = 0x04;

  int fd;

public:
  PwmDriver (int address);
  virtual ~PwmDriver ();
  void setPwmFrequency(float frequency);
  void setPwm(int channel, int on, int off);
  void setAllPwm(int on, int off);
};

}
#endif /* PWM_DRIVER_H */
