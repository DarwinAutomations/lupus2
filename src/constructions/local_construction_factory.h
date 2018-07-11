#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H

#include <memory>

#include "local_construction.h"
#include "local_construction_configuration.h"
#include "pwm_driver.h"
#include "gpio_driver.h"
#include "ultrasonic_service.h"
#include "steering.h"
#include "motor.h"
#include "distance_sensor.h"

namespace lupus::constructions
{

class LocalConstructionFactory
{
private:
  static std::shared_ptr<navigation::ISteering> createSteering(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    SteeringConfiguration configuration);
  static std::shared_ptr<propulsion::IMotor> createMotor(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    MotorConfiguration configuration);
  static std::shared_ptr<sensors::IDistanceSensor> createUltrasonicSensor(
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    std::shared_ptr<sensors::UltrasonicService> ultrasonicService,
    UltrasonicSensorConfiguration configuration);

public:
  static std::shared_ptr<LocalConstruction> create(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    std::shared_ptr<sensors::UltrasonicService> ultrasonicService,
    LocalConstructionConfiguration configuration);
};

} // namespace lupus::consturctions

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H */
