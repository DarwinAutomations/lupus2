#ifndef SENSORS_HALL_SENSOR_H
#define SENSORS_HALL_SENSOR_H

#include <memory>
#include <vector>

#include "distance_sensor.h"
#include "gpio_driver.h"

namespace lupus::sensors
{

class HallSensor
{
  private:
    std::shared_ptr<gpio::GpioDriver> gpio;
    std::mutex mutex;
    int id;
    int pin;
    std::vector<std::chrono::high_resolution_clock::time_point> measurements;
    void callback(int pin, int level, std::chrono::high_resolution_clock::time_point timePoint);

  public:
    HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int pin);
    virtual ~HallSensor();
    std::chrono::microseconds getPeriodTime();
};

} // namespace lupus::sensors

#endif /* SENSORS_HALL_SENSOR_H */
