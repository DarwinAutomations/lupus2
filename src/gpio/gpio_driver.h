#ifndef GPIO_GPIO_DRIVER_H
#define GPIO_GPIO_DRIVER_H

#include <mutex>
#include <map>
#include <tuple>
#include <functional>
#include <chrono>
#include <pigpio.h>

namespace lupus::gpio
{

enum PinMode
{
  Input = PI_INPUT,
  Output = PI_OUTPUT
};

enum PinPull
{
  Up = PI_PUD_UP,
  Down = PI_PUD_DOWN
};

class GpioDriver
{

private:
  static int instanceCount;
  static std::mutex countMutex;

  static std::map<
    int,
    std::tuple<
      int,
      std::function<void(int, int, std::chrono::high_resolution_clock::time_point)>>> callbacks;
  static void callback(int id, int level, uint32_t tick);
  static int callbacksCount;
  static std::mutex callbackMutex;

public:
  GpioDriver ();
  virtual ~GpioDriver ();

  void setMode(int pin, PinMode mode);
  void setPull(int pin, PinPull mode);
  void write(int pin, bool value);
  bool read(int pin);
  int registerOnChange(int pin, std::function<void(int, int, std::chrono::high_resolution_clock::time_point)>);
  void deregisterOnChange(int id);
};

} // namespace lupus::gpio
#endif /* GPIO_GPIO_DRIVER_H */
