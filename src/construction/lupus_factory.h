#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H

#include <memory>

#include "lupus.h"
#include "lupus_configuration.h"
#include "pwm_driver.h"
#include "gpio_driver.h"
#include "ultrasonic_service.h"
#include "steering_unit.h"
#include "motor.h"
#include "distance_sensor.h"
#include "distance_sensor_config.h"

namespace lupus::construction
{

class LupusFactory
{
private:
  static std::shared_ptr<construction::steeringUnit::SteeringUnit> createSteering(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    steeringUnit::SteeringUnitConfiguration configuration);
  static std::shared_ptr<construction::motor::Motor> createMotor(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    MotorConfiguration configuration);
  static std::shared_ptr<construction::distanceSensor::IDistanceSensor> createUltrasonicSensor(
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    std::shared_ptr<construction::distanceSensor::UltrasonicService> ultrasonicService,
    distanceSensor::DistanceSensorConfiguration configuration);

public:
  static std::shared_ptr<Lupus> create(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    std::shared_ptr<construction::distanceSensor::UltrasonicService> ultrasonicService,
    LupusConfiguration configuration);
};

}

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H */
