#ifndef GPIO_GPIO_DRIVER_H
#define GPIO_GPIO_DRIVER_H

#include <mutex>
#include <pigpio.h>

namespace lupus::gpio {

enum GpioPinMode
{
  InputPin = PI_INPUT,
  OutputPin = PI_OUTPUT
};

class GpioDriver
{
private:
  static int instanceCount;
  static std::mutex countMutex;

public:
  GpioDriver ();
  virtual ~GpioDriver ();
  
  void setMode(int pin, GpioPinMode mode);
  void write(int pin, bool value);
  bool read(int pin);
};

} // namespace lupus::gpio
#endif /* GPIO_GPIO_DRIVER_H */
