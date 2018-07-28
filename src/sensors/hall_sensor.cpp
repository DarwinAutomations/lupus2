#include <stdexcept>
#include <functional>
#include <algorithm>
#include <limits>

#include "hall_sensor.h"
#include "gpio_driver.h"

namespace lupus::sensors
{

HallSensor::HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int sensorPin)
  : measurements(3, std::chrono::high_resolution_clock::time_point())
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }
  this->gpio = std::move(gpio);
  this->sensorPin = sensorPin;
  gpio->setMode(sensorPin, gpio::PinMode::Input);
  gpio->setPull(sensorPin, gpio::PinPull::Up);
  callbackId = gpio->registerOnChange(
    sensorPin,
    std::bind(
      &HallSensor::callback, this,
      std::placeholders::_1,
      std::placeholders::_2,
      std::placeholders::_3));
}

HallSensor::~HallSensor()
{
  gpio->deregisterOnChange(callbackId);
}

HallSensorState getState()
{
  return state;
}

void HallRpsSensor::callback(
  int pin,
  int level,
  std::chrono::high_resolution_clock::time_point timePoint)
{
  switch(level)
  {
      case 0:
        state = HallSensorState::NoMagnet;
        break;
      case 1:
        state = HallSensorState::Magnet;
        break;
      default:
        return;
  }

  std::lock_guard<std::mutex> lock(callbackMutex);
  for(auto &callback: callbacks)
  {
    callback(state, timePoint);
  }
}

int HallRpsSensor::registerOnChange(
  std::function<void(int, std::chrono::high_resolution_clock::time_point)> func)
{
  std::lock_guard<std::mutex> lock(callbackMutex);
  int id = callbacksCount++;
  callbacks[id] = func;
  return id;
}

void HallRpsSensor::deregisterOnChange(int id)
{
  std::lock_guard<std::mutex> lock(GpioDriver::callbackMutex);
  if (GpioDriver::callbacks.count(id))
  {
    GpioDriver::callbacks.erase(id);
  }
}

} // namespace lupus::sensors
