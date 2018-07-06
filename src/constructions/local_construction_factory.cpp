#include <stdexcept>

#include "local_construction.h"
#include "local_construction_factory.h"
#include "pwm_control_unit.h"
#include "steering_unit.h"
#include "propulsion_unit.h"
#include "distance_sensor.h"
#include "ultrasonic_sensor.h"
#include "ultrasonic_service.h"

#define ULTRASONIC_TRIGGER 18

namespace lupus::constructions
{

std::shared_ptr<LocalConstruction> LocalConstructionFactory::create(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    std::shared_ptr<sensors::UltrasonicService> ultrasonicService)
{
  // navigation units:
  // navigation unit left:
  auto controlUnitLeft 
    = std::make_shared<pwm::PwmControlUnit>(pwmDriver, 14, 220, 565);
  auto steeringUnitLeft 
    = std::make_shared<navigation::SteeringUnit>(controlUnitLeft);

  // navigation unit right:
  auto controlUnitRight 
    = std::make_shared<pwm::PwmControlUnit>(pwmDriver, 15, 565, 220);
  auto steeringUnitRight 
    = std::make_shared<navigation::SteeringUnit>(controlUnitRight);

  // propulsion units:
  // propulsion unit front left:
  auto cuPropulsionFrontLeft = std::make_shared<pwm::PwmControlUnit>(
      pwmDriver, 0, 240, 460);
  auto hallSensorFrontLeft = std::make_shared<sensors::HallSensor>(
      gpioDriver, 0);
  auto propulsionUnitFrontLeft = std::make_shared<navigation::PropulsionUnit>(
      cuPropulsionFrontLeft,
      hallSensorFrontLeft);

  // propulsion unit front right:
  auto cuPropulsionFrontRight = std::make_shared<pwm::PwmControlUnit>(
      pwmDriver, 1, 240, 460);
  auto hallSensorFrontRight = std::make_shared<sensors::HallSensor>(
      gpioDriver, 0);
  auto propulsionUnitFrontRight = std::make_shared<navigation::PropulsionUnit>(
      cuPropulsionFrontRight,
      hallSensorFrontRight);

  // propulsion unit back left:
  auto cuPropulsionBackLeft = std::make_shared<pwm::PwmControlUnit>(
      pwmDriver, 2, 240, 460);
  auto hallSensorBackLeft = std::make_shared<sensors::HallSensor>(
      gpioDriver, 0);
  auto propulsionUnitBackLeft = std::make_shared<navigation::PropulsionUnit>(
      cuPropulsionBackLeft,
      hallSensorBackLeft);

  // propulsion unit back right:
  auto cuPropulsionBackRight = std::make_shared<pwm::PwmControlUnit>(
      pwmDriver, 3, 240, 460);
  auto hallSensorBackRight = std::make_shared<sensors::HallSensor>(
      gpioDriver, 0);
  auto propulsionUnitBackRight = std::make_shared<navigation::PropulsionUnit>(
      cuPropulsionBackRight,
      hallSensorBackRight);

  // sensors:
  // ultrasnoic sensor front left:
  auto ultrasonicSensorFrontLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */,
      ULTRASONIC_TRIGGER, 19);

  // ultrasnoic sensor front center left:
  auto ultrasonicSensorFrontCenterLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, 13);

  // ultrasnoic sensor front center right:
  auto ultrasonicSensorFrontCenterRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      16, 6);

  // ultrasnoic sensor front right:
  auto ultrasonicSensorFrontRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      12, 5);

  // ultrasnoic sensor back left:
  auto ultrasonicSensorBackLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */,
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 1);

  // ultrasnoic sensor back center left:
  auto ultrasonicSensorBackCenterLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 2);

  // ultrasnoic sensor back center right:
  auto ultrasonicSensorBackCenterRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 3);

  // ultrasnoic sensor back right:
  auto ultrasonicSensorBackRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService, 
      4000, 10, 0.2617993878 /* PI / 12 */, 
      ULTRASONIC_TRIGGER, ULTRASONIC_TRIGGER + 4);


  // consutruction:
  auto construction = std::make_shared<constructions::LocalConstruction>(
    steeringUnitLeft,
    steeringUnitRight,

    propulsionUnitFrontLeft,
    propulsionUnitFrontRight,
    propulsionUnitBackLeft,
    propulsionUnitBackRight,

    ultrasonicSensorFrontLeft,
    ultrasonicSensorFrontCenterLeft,
    ultrasonicSensorFrontCenterRight,
    ultrasonicSensorFrontRight,
    ultrasonicSensorBackLeft,
    ultrasonicSensorBackCenterLeft,
    ultrasonicSensorBackCenterRight,
    ultrasonicSensorBackRight
  );

  return construction;
}

} // namespace lupus::constructions
