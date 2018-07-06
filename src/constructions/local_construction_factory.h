#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H

#include "local_construction.h"
#include "ultrasonic_service.h"
#include "pwm_driver.h"

namespace lupus::constructions
{

class LocalConstructionFactory
{
  public:
    static std::shared_ptr<LocalConstruction> create(
      std::shared_ptr<pwm::PwmDriver> pwmDriver,
      std::shared_ptr<gpio::GpioDriver> gpioDriver,
      std::shared_ptr<sensors::UltrasonicService> ultrasonicService 
      /* pins etc */ );
};

} // namespace lupus::consturctions

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H */
