#include <stdexcept>
#include <pigpio.h>

#include <gpio_driver.h>

namespace lupus::gpio
{

int GpioDriver::instanceCount = 0;
int GpioDriver::callbacksCount = 0;
std::mutex GpioDriver::countMutex;
std::map<
  int, 
  std::tuple<
    int, 
    std::function<void(int, int, uint32_t)>>> GpioDriver::callbacks;
std::mutex GpioDriver::callbackMutex;


GpioDriver::GpioDriver ()
{
  GpioDriver::countMutex.lock();
  GpioDriver::instanceCount++;
  if(GpioDriver::instanceCount == 1)
  {
    if(gpioInitialise() < 0)
    {
      GpioDriver::countMutex.unlock();
      throw std::invalid_argument("gpio library initialisation failed");
    }
  }
  GpioDriver::countMutex.unlock();
}

GpioDriver::~GpioDriver ()
{
  GpioDriver::countMutex.lock();
  GpioDriver::instanceCount--;
  if(GpioDriver::instanceCount == 0)
  {
    gpioTerminate();
  }
  GpioDriver::countMutex.unlock();
}

void GpioDriver::setMode(int pin, PinMode mode)
{
  gpioSetMode(pin, mode);
}

void GpioDriver::setPull(int pin, PinPull mode)
{
  gpioSetPullUpDown(pin, mode);
}

void GpioDriver::write(int pin, bool value)
{
  gpioWrite(pin, value);
}

bool GpioDriver::read(int pin)
{
  return (bool)gpioRead(pin);
}

int GpioDriver::registerOnChange(int pin, std::function<void(int, int, uint32_t)> func)
{
  std::lock_guard<std::mutex> lock(GpioDriver::callbackMutex);
  int id = GpioDriver::callbacksCount++;
  GpioDriver::callbacks[id] = std::make_tuple(pin, func);
  gpioSetAlertFunc(pin, GpioDriver::callback);
  return id;
}

void GpioDriver::deregisterOnChange(int id)
{
  std::lock_guard<std::mutex> lock(GpioDriver::callbackMutex);
  if (GpioDriver::callbacks.count(id))
  {
    GpioDriver::callbacks.erase(id);
  }
}

void GpioDriver::callback(int pin, int level, uint32_t tick)
{
  std::lock_guard<std::mutex> lock(GpioDriver::callbackMutex);
  for(auto &kv: GpioDriver::callbacks)
  {
    std::function<void(int,int,uint32_t)> cb;
    int cbPin;
    std::tie(cbPin, cb) = kv.second;
    if(cbPin != pin)
      continue;

    cb(pin, level, tick);
  }
}

} // namespace lupus::gpio
