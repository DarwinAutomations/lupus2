#ifndef SENSORS_HALL_SENSOR_H
#define SENSORS_HALL_SENSOR_H

#include <memory>
#include <vector>

#include "distance_sensor.h"
#include "gpio_driver.h"

namespace lupus::construction::rpsSensor
{

enum HallSensorState
{
  Magnet,
  NoMagnet
};

class HallSensor
{
public:
  HallSensor(std::shared_ptr<drivers::gpio::GpioDriver> gpio, int sensorPin);
  virtual ~HallSensor();

  HallSensorState getState();
  int registerOnChange(
    std::function<void(HallSensorState, std::chrono::high_resolution_clock::time_point)>);
  void deregisterOnChange(int id);

private:
  std::shared_ptr<drivers::gpio::GpioDriver> gpio;
  int sensorPin;
  HallSensorState state;

  std::mutex callbackMutex;
  std::map<
    int,
    std::function<void(
      HallSensorState,
      std::chrono::high_resolution_clock::time_point)>> callbacks;
  int callbacksCount;
  void callback(int id, int pin, int level, std::chrono::high_resolution_clock::time_point timePoint);
  int callbackId;
};

}

#endif /* SENSORS_HALL_SENSOR_H */
