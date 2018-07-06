#include <stdexcept>
#include <functional>
#include <algorithm>

#include "hall_sensor.h"
#include "gpio_driver.h"

namespace lupus::sensors
{

HallSensor::HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int pin)
  : periods(3,0)
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }
  this->gpio = std::move(gpio);
  this->pin = pin;

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

float HallSensor::getNormalisedRps()
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
  if(level == 0)
    return;

  std::lock_guard<std::mutex> guard(mutex);
  std::rotate(periods.begin(), periods.begin() + 1, periods.end());

  uint32_t period;
  if(lastTick <= tick)
    period = tick - lastTick;
  else
    period = tick - lastTick + std::numeric_limits<uint32_t>::max();

  periods[2] = period;
  lastTick = tick;
}

} // namespace lupus::sensors
