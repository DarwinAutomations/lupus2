#ifndef SENSORS_HALL_RPS_SENSOR_H
#define SENSORS_HALL_RPS_SENSOR_H

#include "rps_sensor.h"
#include "hall_sensor.h"

namespace lupus::sensors
{

class HallRpsSensor final: public IRpsSensor
{
private:
  std::shared_ptr<HallSensor> sensor;


public:
  HallRpsSensor(
    std::shared_ptr<HallSensor> sensor
  );
  virtual ~HallRpsSensor() = default;
  float getRps();
};

} // namespace lupus::sensors

#endif /* SENSORS_HALL_RPS_SENSOR_H */
