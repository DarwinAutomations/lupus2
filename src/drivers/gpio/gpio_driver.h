#ifndef GPIO_GPIO_DRIVER_H
#define GPIO_GPIO_DRIVER_H

#include <mutex>
#include <map>
#include <tuple>
#include <functional>
#include <chrono>
#include <pigpiod_if2.h>

namespace lupus::drivers::gpio
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

public:
  GpioDriver (char* address, char* port);
  virtual ~GpioDriver ();

  void setMode(int pin, PinMode mode);
  void setPull(int pin, PinPull mode);
  void write(int pin, bool value);
  bool read(int pin);
  int registerOnChange(
    int pin,
    std::function<void(int, int, int, std::chrono::high_resolution_clock::time_point)>);
  void deregisterOnChange(int id);


private:
  static void pinChangeEventHandler(
    int pi,
    unsigned int pin,
    unsigned int level,
    unsigned int tick,
    void* _this);

  int pi;
  std::mutex callbackMutex;
  std::map<
    int,
    std::tuple<
      int,
      std::function<void(int, int, int, std::chrono::high_resolution_clock::time_point)>>> callbacks;
  int callbacksCount;
};

}
#endif /* GPIO_GPIO_DRIVER_H */
