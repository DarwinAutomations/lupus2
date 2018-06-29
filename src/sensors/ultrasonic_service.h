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
    std::shared_ptr<gpio::GpioDriver> gpio;
    std::mutex registryMutex;
    std::mutex dataMutex;
    std::thread measuringThread;
    std::map<int, int> data;
    std::map<int, std::tuple<int, int>> registry;
    int idCounter;
    bool isRunning;
    void measuringLoop(int frequency);

  public:
    UltrasonicService (std::shared_ptr<gpio::GpioDriver> gpio, int frequency);
    virtual ~UltrasonicService ();
    int registerSensor(int trigger, int echo);
    void deregisterSensor(int id);
    int getDistance(int id);
    static int measure(
        std::shared_ptr<gpio::GpioDriver> gpio,
        int trigger, int echo,
        std::chrono::time_point<std::chrono::system_clock>* startTime = NULL);


};

} // namespace lupus::sensors

#endif /* ULTRASONIC_SERVICE_H */
