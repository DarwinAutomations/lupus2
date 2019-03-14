#include <stdexcept>
#include <functional>

#include "hall_rps_sensor.h"

namespace lupus::construction::rpsSensor
{

HallRpsSensor::HallRpsSensor(
  std::shared_ptr<drivers::gpio::GpioDriver> gpio,
  int sensorPin)
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }

  this->gpio = std::move(gpio);
  this->rps = 0;
  this->lastMeasurement = std::chrono::high_resolution_clock::now();

  this->gpio->setMode(sensorPin, drivers::gpio::PinMode::Input);
  this->gpio->setPull(sensorPin, drivers::gpio::PinPull::Up);

  callbackId = this->gpio->registerOnChange(
    sensorPin,
    std::bind(
      &HallRpsSensor::callback, this,
      std::placeholders::_1,
      std::placeholders::_2,
      std::placeholders::_3,
      std::placeholders::_4));
}

HallRpsSensor::~HallRpsSensor()
{
  gpio->deregisterOnChange(callbackId);
}

float HallRpsSensor::getRps()
{
  return rps;
}

void HallRpsSensor::callback(
  int id,
  int pin,
  int level,
  std::chrono::high_resolution_clock::time_point timePoint)
{
  if(level != HallSensorState::Magnet)
    return;

  setRps(timePoint);
  }

void HallRpsSensor::setRps(
  std::chrono::high_resolution_clock::time_point thisMeasurement)
{
  rps = 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(
    thisMeasurement - lastMeasurement).count();

  lastMeasurement = thisMeasurement;
}

}
