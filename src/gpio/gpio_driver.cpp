#include <stdexcept>
#include <pigpio.h>

#include <gpio_driver.h>

namespace lupus::gpio
{

GpioDriver::GpioDriver(char* address, char* port)
{
  pi = pigpio_start(address, port);
  if(pi < 0)
  {
    throw std::runtime_error("pigpiod: failed to establish connection.");
  }
}

GpioDriver::~GpioDriver()
{
  pigpio_stop(pi);
}

void GpioDriver::setMode(int pin, PinMode mode)
{
  set_mode(pi, pin, mode);
}

void GpioDriver::setPull(int pin, PinPull mode)
{
  set_pull_up_down(pi, pin, mode);
}

bool GpioDriver::read(int pin)
{
  return (bool) gpio_read(pi, pin);
}

void GpioDriver::write(int pin, bool value)
{
  gpio_write(pi, pin, value);
}


int GpioDriver::registerOnChange(
  int pin,
  std::function<void(
    int, int, std::chrono::high_resolution_clock::time_point)> func)
{
  std::lock_guard<std::mutex> lock(callbackMutex);
  int callbackId = callbacksCount++;
  callbacks[callbackId] = std::make_tuple(pin, func);

  callback_ex(
    pi,
    pin,
    EITHER_EDGE,
    [](int pi, unsigned pin, unsigned level, uint32_t tick, void * _this)
    {
      ((GpioDriver*)_this)->callback(pin, level, tick);
    },
    this);

  return callbackId;
}

void GpioDriver::deregisterOnChange(int callbackId)
{
std::lock_guard<std::mutex> lock(callbackMutex);
if (GpioDriver::callbacks.count(callbackId))
{
  GpioDriver::callbacks.erase(callbackId);
}
}

void GpioDriver::callback(int pin, int level, uint32_t tick)
{
  auto now = std::chrono::high_resolution_clock::now();
  auto nowTick = get_current_tick(pi);
  auto timePoint = now - std::chrono::microseconds(nowTick - tick);

  std::lock_guard<std::mutex> lock(callbackMutex);
  for(auto &kv: callbacks)
  {
    std::function<void(int,int,std::chrono::high_resolution_clock::time_point)> callback;
    int callbackPin;
    std::tie(callbackPin, callback) = kv.second;
    if(callbackPin != pin)
      continue;

    callback(pin, level, timePoint);
  }
}

} // namespace lupus::gpio
