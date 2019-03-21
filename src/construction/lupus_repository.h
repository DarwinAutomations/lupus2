#ifndef LUPUS_CONSTRUCTION_LUPUS_REPOSITORY_H
#define LUPUS_CONSTRUCTION_LUPUS_REPOSITORY_H

#include <memory>

#include "gpio_driver.h"
#include "pwm_driver.h"
#include "ultrasonic_service.h"
#include "lupus.h"

namespace lupus::construction
{

class LupusRepository
{
private:
  std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver;
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver;
  std::shared_ptr<distanceSensor::UltrasonicService> ultrasonicService;

public:
  LupusRepository(
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    std::shared_ptr<distanceSensor::UltrasonicService> ultrasonicService
  );

  std::shared_ptr<Lupus> readFromFile(const char* fileName);
  void writeIntoFile(std::shared_ptr<Lupus> lupus);
};

}

#endif /* LUPUS_CONSTRUCTION_LUPUS_REPOSITORY_H */
