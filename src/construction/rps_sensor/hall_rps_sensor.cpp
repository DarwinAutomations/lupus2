#include <stdexcept>
#include <functional>
#include <algorithm>

#include "hall_rps_sensor_config.h"
#include "hall_rps_sensor.h"

namespace lupus::construction::rpsSensor
{

HallRpsSensor::HallRpsSensor(
  std::shared_ptr<drivers::gpio::GpioDriver> gpio,
  HallRpsSensorConfiguration config) : configuration(config)
{
  if(!gpio)
  {
    throw std::invalid_argument("gpio driver must not be null");
  }

  this->gpio = std::move(gpio);
  this->rps = 0;
  this->lastMeasurement = std::chrono::high_resolution_clock::now();

  this->gpio->setMode(configuration.pin, drivers::gpio::PinMode::Input);
  this->gpio->setPull(configuration.pin, drivers::gpio::PinPull::Up);

  callbackId = this->gpio->registerOnChange(
    configuration.pin,
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
  auto ifNowMeasured = std::chrono::high_resolution_clock::now();
  float maxRps = 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(
    ifNowMeasured - lastMeasurement).count();

  return std::min(rps, maxRps);
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
