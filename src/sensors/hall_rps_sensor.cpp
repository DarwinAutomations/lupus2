#include <stdexcept>
#include "hall_rps_sensor.h"

namespace lupus::sensors
{

HallRpsSensor::HallRpsSensor(
    std::shared_ptr<HallSensor> sensor)
{
  if(!sensor)
  {
    throw std::invalid_argument("hall sensor must not be null");
  }

  this->sensor = std::move(sensor);
  callbackId = sensor->registerOnChange(
    std::bind(
      &HallRpsSensor::callback, this,
      std::placeholders::_1,
      std::placeholders::_2)
  )
}

HallRpsSensor::~HallRpsSensor()
{
  sensor->deregisterOnChange(callbackId);
}

float HallRpsSensor::getRps()
{
  return 1000000.0 / getPeriodTime().count();
}

std::chrono::microseconds HallRpsSensor::getPeriodTime()
{
  std::lock_guard<std::mutex> guard(dataMutex);

  auto lastPeriodTime
    = std::chrono::duration_cast<std::chrono::microseconds> (
      measurements[0] - measurements[1]);
  auto currentMinPeriodTime
    = std::chrono::duration_cast<std::chrono::microseconds> (
      std::chrono::high_resolution_clock::now() - measurements[0]);

  if(lastPeriodTime < currentMinPeriodTime)
    return currentMinPeriodTime;
  return lastPeriodTime;
}

void HallRpsSensor::callback(
  int level,
  std::chrono::high_resolution_clock::time_point timePoint)
{
  if(level != 1)
    return;

  std::lock_guard<std::mutex> guard(dataMutex);

  std::rotate(
    measurements.rbegin(),
    measurements.rbegin() + 1,
    measurements.rend());

  measurements[0] = timePoint;
}

} // namespace lupus::sensors
