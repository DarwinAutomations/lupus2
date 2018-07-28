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
  int callbackId;
  std::mutex dataMutex;
  std::vector<std::chrono::high_resolution_clock::time_point> measurements;
  void callback(
    HallSensorState state,
    std::chrono::high_resolution_clock::time_point timePoint);
  std::chrono::microseconds getPeriodTime()



public:
  HallRpsSensor(std::shared_ptr<HallSensor> sensor);
  virtual ~HallRpsSensor() = default;
  float getRps();
};

} // namespace lupus::sensors

#endif /* SENSORS_HALL_RPS_SENSOR_H */
