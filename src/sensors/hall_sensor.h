#ifndef SENSORS_HALL_SENSOR_H
#define SENSORS_HALL_SENSOR_H

#include <memory>
#include <vector>

#include "distance_sensor.h"
#include "gpio_driver.h"

namespace lupus::sensors
{

enum HallSensorState
{
  Magnet,
  NoMagnet
};

class HallSensor
{
  private:
    std::shared_ptr<gpio::GpioDriver> gpio;
    int sensorPin;
    HallSensorState state;

    static std::mutex callbackMutex;
    static std::map<
      int,
      std::function<void(
        int, int,
        std::chrono::high_resolution_clock::time_point)>> callbacks;
    static int callbacksCount;
    void callback(int pin, int level, std::chrono::high_resolution_clock::time_point timePoint);
    int callbackId;

  public:
    HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int sensorPin);
    virtual ~HallSensor();

    HallSensorState getState();
    int registerOnChange(
      std::function<void(int, std::chrono::high_resolution_clock::time_point)>);
    void deregisterOnChange(int id);
};

} // namespace lupus::sensors

#endif /* SENSORS_HALL_SENSOR_H */
