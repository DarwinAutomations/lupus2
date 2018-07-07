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
    int id;
    std::mutex mutex;
    int pin;
    uint32_t lastTick;
    std::vector<int> periods;
    void callback(int pin, int level, uint32_t tick);

  public:
    HallSensor(std::shared_ptr<gpio::GpioDriver> gpio, int pin);
    virtual ~HallSensor();
    float getLatestPeriodTime();
    float getNormalisedPeriodTime();
};

} // namespace lupus::sensors

#endif /* SENSORS_HALL_SENSOR_H */
