#ifndef SENSORS_HALL_RPS_SENSOR_H
#define SENSORS_HALL_RPS_SENSOR_H

#include <memory>
#include <chrono>

#include "gpio_driver.h"
#include "hall_rps_sensor_config.h"

namespace lupus::construction::rpsSensor
{
  enum HallSensorState
  {
    Magnet = 1,
    NoMagnet = 0
  };

class HallRpsSensor
{
public:
  HallRpsSensor(
    std::shared_ptr<drivers::gpio::GpioDriver> gpio,
    HallRpsSensorConfiguration config);
  virtual ~HallRpsSensor();
  float getRps();

private:
  std::shared_ptr<drivers::gpio::GpioDriver> gpio;
  HallRpsSensorConfiguration configuration;
  float rps;
  std::chrono::high_resolution_clock::time_point lastMeasurement;
  int callbackId;

  void callback(
    int id,
    int pin,
    int level,
    std::chrono::high_resolution_clock::time_point timePoint);

  void setRps(std::chrono::high_resolution_clock::time_point timePoint);

};

}

#endif /* SENSORS_HALL_RPS_SENSOR_H */
