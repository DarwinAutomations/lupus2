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
}

float HallRpsSensor::getRps()
{
  return 1000000.0 / sensor->getNormalisedPeriodTime();
}

} // namespace lupus::sensors
