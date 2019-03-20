#include <stdexcept>

#include "lupus.h"
#include "lupus_factory.h"
#include "steering_unit.h"
#include "hall_rps_sensor.h"
#include "propulsion_unit.h"
#include "rc_motor.h"
#include "distance_sensor_config.h"
#include "ultrasonic_sensor.h"
#include "ultrasonic_service.h"

namespace lupus::construction
{

std::shared_ptr<Lupus> LupusFactory::create(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    std::shared_ptr<distanceSensor::UltrasonicService> ultrasonicService,
    LupusConfiguration configuration)
{
  // navigation units:
  // navigation unit left:
  auto steeringL = LupusFactory::createSteering(
    pwmDriver,
    *configuration.steeringLeft);

  // navigation unit right:
  auto steeringR = LupusFactory::createSteering(
    pwmDriver,
    *configuration.steeringRight);

  // propulsion units:
  // propulsion unit front left:
  auto motorFL = LupusFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorFrontLeft);

  // propulsion unit front right:
  auto motorFR = LupusFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorFrontRight);

  // propulsion unit back left:
  auto motorBL = LupusFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorBackLeft);

  // propulsion unit back right:
  auto motorBR = LupusFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorBackRight);

  // sensors:
  // ultrasnoic sensor front left:
  auto ultrasonicSensorFrontLeft = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicFrontLeft);

  // ultrasnoic sensor front center left:
  auto ultrasonicSensorFrontCenterLeft = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicFrontLeftCenter);

  // ultrasnoic sensor front center right:
  auto ultrasonicSensorFrontCenterRight = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicFrontRightCenter);

  // ultrasnoic sensor front right:
  auto ultrasonicSensorFrontRight = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicFrontRight);

  // ultrasnoic sensor back left:
  auto ultrasonicSensorBackLeft = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicBackLeft);

  // ultrasnoic sensor back center left:
  auto ultrasonicSensorBackCenterLeft = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicBackLeftCenter);

  // ultrasnoic sensor back center right:
  auto ultrasonicSensorBackCenterRight = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicBackRightCenter);

  // ultrasnoic sensor back right:
  auto ultrasonicSensorBackRight = LupusFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      *configuration.ultrasonicBackRight);

  // consutruction:
  auto lupus = std::make_shared<Lupus>(
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

  return lupus;
}

std::shared_ptr<steeringUnit::SteeringUnit> LupusFactory::createSteering(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    steeringUnit::SteeringUnitConfiguration configuration)
{
  return std::make_shared<steeringUnit::SteeringUnit>(
      pwmDriver,
      configuration);
}

std::shared_ptr<motor::RCMotor> LupusFactory::createMotor(
    std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    MotorConfiguration configuration)
{
  return std::make_shared<motor::RCMotor>(
    std::make_shared<motor::propulsionUnit::PropulsionUnit>(
      pwmDriver,
      configuration.propulsionUnit->pin,
      configuration.propulsionUnit->forwardMin,
      configuration.propulsionUnit->forwardMax,
      configuration.propulsionUnit->backwardMin,
      configuration.propulsionUnit->backwardMax),
    std::make_shared<motor::rpsSensor::HallRpsSensor>(
      gpioDriver,
      *configuration.hallSensor));
}

std::shared_ptr<distanceSensor::IDistanceSensor> LupusFactory::createUltrasonicSensor(
    std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
    std::shared_ptr<distanceSensor::UltrasonicService> ultrasonicService,
    distanceSensor::DistanceSensorConfiguration configuration)
{
  auto sensor = std::make_shared<distanceSensor::UltrasonicSensor>(
    configuration);

  ultrasonicService->registerSensor(sensor);
  // TODO: deregisterSensor with retruned id

  return sensor;
}

}
