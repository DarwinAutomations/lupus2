#include <stdexcept>

#include "local_construction.h"
#include "local_construction_factory.h"
#include "servo.h"
#include "rc_steering.h"
#include "hall_sensor.h"
#include "hall_rps_sensor.h"
#include "propulsion_unit.h"
#include "rc_motor.h"
#include "ultrasonic_sensor.h"
#include "ultrasonic_service.h"

namespace lupus::constructions
{

std::shared_ptr<LocalConstruction> LocalConstructionFactory::create(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    std::shared_ptr<sensors::UltrasonicService> ultrasonicService)
{
  // navigation units:
  // navigation unit left:
  auto steeringL = std::make_shared<navigation::RCSteering>(
    std::make_shared<navigation::Servo>(
      pwmDriver, 4, 220, 565));

  // navigation unit right:
  auto steeringR = std::make_shared<navigation::RCSteering>(
    std::make_shared<navigation::Servo>(
      pwmDriver, 5, 220, 565));

  // propulsion units:
  // propulsion unit front left:
  auto motorFL = std::make_shared<propulsion::RCMotor>(
    std::make_shared<propulsion::PropulsionUnit>(
      pwmDriver, 0, 350, 460, 350, 240),
    std::make_shared<sensors::HallRpsSensor>(
      std::make_shared<sensors::HallSensor>(
        gpioDriver, 12)));

  // propulsion unit front right:
  auto motorFR = std::make_shared<propulsion::RCMotor>(
    std::make_shared<propulsion::PropulsionUnit>(
      pwmDriver, 1, 350, 460, 350, 240),
    std::make_shared<sensors::HallRpsSensor>(
      std::make_shared<sensors::HallSensor>(
        gpioDriver, 16)));

  // propulsion unit back left:
  auto motorBL = std::make_shared<propulsion::RCMotor>(
    std::make_shared<propulsion::PropulsionUnit>(
      pwmDriver, 2, 350, 460, 350, 240),
    std::make_shared<sensors::HallRpsSensor>(
      std::make_shared<sensors::HallSensor>(
        gpioDriver, 20)));

  // propulsion unit back right:
  auto motorBR = std::make_shared<propulsion::RCMotor>(
    std::make_shared<propulsion::PropulsionUnit>(
      pwmDriver, 3, 350, 460, 350, 240),
    std::make_shared<sensors::HallRpsSensor>(
      std::make_shared<sensors::HallSensor>(
        gpioDriver, 21)));

  // sensors:
  // ultrasnoic sensor front left:
  auto ultrasonicSensorFrontLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      18, 17);

  // ultrasnoic sensor front center left:
  auto ultrasonicSensorFrontCenterLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      23, 27);

  // ultrasnoic sensor front center right:
  auto ultrasonicSensorFrontCenterRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      24, 22);

  // ultrasnoic sensor front right:
  auto ultrasonicSensorFrontRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      25, 5);

  // ultrasnoic sensor back left:
  auto ultrasonicSensorBackLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      18, 6);

  // ultrasnoic sensor back center left:
  auto ultrasonicSensorBackCenterLeft = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      23, 13);

  // ultrasnoic sensor back center right:
  auto ultrasonicSensorBackCenterRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      24, 19);

  // ultrasnoic sensor back right:
  auto ultrasonicSensorBackRight = std::make_shared<sensors::UltrasonicSensor>(
      ultrasonicService,
      4000, 10, 0.2617993878 /* PI / 12 */,
      25, 26);


  // consutruction:
  auto construction = std::make_shared<constructions::LocalConstruction>(
    steeringL,
    steeringR,

    motorFL, motorFR,
    motorBL, motorBR,

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
