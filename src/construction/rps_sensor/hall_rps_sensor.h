#ifndef SENSORS_HALL_RPS_SENSOR_H
#define SENSORS_HALL_RPS_SENSOR_H

#include "rps_sensor.h"
#include "hall_sensor.h"

namespace lupus::construction::rpsSensor
{

class HallRpsSensor final: public IRpsSensor
{
public:
  HallRpsSensor(std::shared_ptr<HallSensor> sensor);
  virtual ~HallRpsSensor();
  float getRps();

private:
  std::shared_ptr<HallSensor> sensor;
  int callbackId;
  std::mutex dataMutex;
  std::vector<std::chrono::high_resolution_clock::time_point> measurements;
  void callback(
    HallSensorState state,
    std::chrono::high_resolution_clock::time_point timePoint);
  std::chrono::microseconds getPeriodTime();

};

}

#endif /* SENSORS_HALL_RPS_SENSOR_H */
