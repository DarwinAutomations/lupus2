#ifndef ULTRASONIC_SERVICE_H
#define ULTRASONIC_SERVICE_H

#include <thread>
#include <mutex>
#include <map>
#include <tuple>
#include <memory>

#include "gpio_driver.h"

namespace lupus::sensors
{

class UltrasonicService
{
  private:
    bool isRunning;
    std::chrono::high_resolution_clock::time_point lastMassTrigger;
    std::shared_ptr<gpio::GpioDriver> gpio;
    std::mutex registryMutex;
    std::thread measuringThread;
    std::map<int, float> data;
    std::map<int, std::tuple<int, int>> registry;

    void measuringLoop(int frequency);
    void onEchoChange(
      int id, int pin, int level,
      std::chrono::high_resolution_clock::time_point echo_time);

  public:
    UltrasonicService (std::shared_ptr<gpio::GpioDriver> gpio, int frequency);
    virtual ~UltrasonicService ();
    int registerSensor(int trigger, int echo);
    void deregisterSensor(int id);
    float getDistance(int id);
};

} // namespace lupus::sensors

#endif /* ULTRASONIC_SERVICE_H */
