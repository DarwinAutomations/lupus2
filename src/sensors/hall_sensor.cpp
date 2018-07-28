#include <stdexcept>
#include <functional>
#include <algorithm>
#include <limits>

#include "hall_sensor.h"
#include "gpio_driver.h"

namespace lupus::sensors
{

HallSensor::HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int pin)
  : measurements(3, std::chrono::high_resolution_clock::time_point())
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }
  this->gpio = std::move(gpio);
  this->pin = pin;
  gpio->setMode(pin, gpio::PinMode::Input);
  gpio->setPull(pin, gpio::PinPull::Up);
  id = gpio->registerOnChange(
    pin,
    std::bind(
      &HallSensor::callback, this,
      std::placeholders::_1,
      std::placeholders::_2,
      std::placeholders::_3));
}

HallSensor::~HallSensor()
{
  gpio->deregisterOnChange(id);
}


std::chrono::microseconds HallSensor::getPeriodTime()
{
  std::lock_guard<std::mutex> guard(mutex);

  auto lastPeriodTime = std::chrono::duration_cast<std::chrono::microseconds> (measurements[0] - measurements[1]);
  auto currentMinPeriodTime = std::chrono::duration_cast<std::chrono::microseconds> (std::chrono::high_resolution_clock::now() - measurements[0]);
  if(lastPeriodTime < currentMinPeriodTime)
    return currentMinPeriodTime;
  return lastPeriodTime;
}

void HallSensor::callback(int pin, int level, std::chrono::high_resolution_clock::time_point timePoint)
{
  if(level != 1)
    return;

  std::lock_guard<std::mutex> guard(mutex);

  std::rotate(
    measurements.rbegin(),
    measurements.rbegin() + 1,
    measurements.rend());

  measurements[0] = timePoint;
}

} // namespace lupus::sensors
