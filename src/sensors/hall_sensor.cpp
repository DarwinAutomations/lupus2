#include <stdexcept>
#include <functional>
#include <algorithm>
#include <limits>

#include "hall_sensor.h"
#include "gpio_driver.h"

namespace lupus::sensors
{

HallSensor::HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int pin)
  : periods(3, std::numeric_limits<int>::infinity())
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

float HallSensor::getLatestPeriodTime()
{
  return periods[2];
}

float HallSensor::getNormalisedPeriodTime()
{
  std::lock_guard<std::mutex> guard(mutex);

  if(periods[0] >= periods[1] && periods[0] >= periods[2])
  {
    return periods[1] > periods[2] ? periods[1] : periods[2];
  }
  if ( periods[0] <= periods[1] && periods[0] <= periods[2])
  {
    return periods[1] < periods[2] ? periods[1] : periods[2];
  }
  return periods[0];
}

void HallSensor::callback(int pin, int level, uint32_t tick)
{
  if(level != 1)
    return;

  std::lock_guard<std::mutex> guard(mutex);
  std::rotate(periods.begin(), periods.begin() + 1, periods.end());

  if(lastTick > tick)
    tick += std::numeric_limits<uint32_t>::max();
  auto period = tick - lastTick;

  periods[2] = period;
  lastTick = tick;
}

} // namespace lupus::sensors
