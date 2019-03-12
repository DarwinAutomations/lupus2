#include <stdexcept>
#include <functional>
#include <limits>
#include <chrono>

#include "hall_sensor.h"
#include "gpio_driver.h"

namespace lupus::construction::rpsSensor
{

HallSensor::HallSensor(std::shared_ptr<drivers::gpio::GpioDriver> gpio, int sensorPin)
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }
  this->gpio = std::move(gpio);
  this->sensorPin = sensorPin;
  this->gpio->setMode(sensorPin, drivers::gpio::PinMode::Input);
  this->gpio->setPull(sensorPin, drivers::gpio::PinPull::Up);
  callbackId = this->gpio->registerOnChange(
    sensorPin,
    std::bind(
      &HallSensor::callback, this,
      std::placeholders::_1,
      std::placeholders::_2,
      std::placeholders::_3,
      std::placeholders::_4));
}

HallSensor::~HallSensor()
{
  gpio->deregisterOnChange(callbackId);
}

HallSensorState HallSensor::getState()
{
  return state;
}

void HallSensor::callback(
  int id,
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
    callback.second(state, timePoint);
  }
}

int HallSensor::registerOnChange(
  std::function<void(HallSensorState, std::chrono::high_resolution_clock::time_point)> func)
{
  std::lock_guard<std::mutex> lock(callbackMutex);
  int id = callbacksCount++;
  callbacks[id] = func;
  return id;
}

void HallSensor::deregisterOnChange(int id)
{
  std::lock_guard<std::mutex> lock(callbackMutex);
  if (callbacks.count(id))
  {
    callbacks.erase(id);
  }
}

}
