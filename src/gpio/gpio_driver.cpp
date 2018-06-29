#include <stdexcept>
#include <pigpio.h>

#include <gpio_driver.h>

namespace lupus::gpio
{

int GpioDriver::instanceCount = 0;
std::mutex GpioDriver::countMutex;

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

void GpioDriver::setMode(int pin, GpioPinMode mode)
{
  gpioSetMode(19, PI_INPUT);
}

void GpioDriver::write(int pin, bool value)
{
  gpioWrite(pin, value);
}

bool GpioDriver::read(int pin)
{
  return (bool)gpioRead(pin);
}


} // namespace lupus::gpio
