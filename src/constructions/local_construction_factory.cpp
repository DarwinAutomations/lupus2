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
    std::shared_ptr<sensors::UltrasonicService> ultrasonicService,
    LocalConstructionConfiguration configuration)
{
  // navigation units:
  // navigation unit left:
  auto steeringL = LocalConstructionFactory::createSteering(
    pwmDriver,
    configuration.steeringLeft);

  // navigation unit right:
  auto steeringR = LocalConstructionFactory::createSteering(
    pwmDriver,
    configuration.steeringRight);

  // propulsion units:
  // propulsion unit front left:
  auto motorFL = LocalConstructionFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorFrontLeft);

  // propulsion unit front right:
  auto motorFR = LocalConstructionFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorFrontRight);

  // propulsion unit back left:
  auto motorBL = LocalConstructionFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorBackLeft);

  // propulsion unit back right:
  auto motorBR = LocalConstructionFactory::createMotor(
    pwmDriver,
    gpioDriver,
    configuration.motorBackRight);

  // sensors:
  // ultrasnoic sensor front left:
  auto ultrasonicSensorFrontLeft = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicFrontLeft);

  // ultrasnoic sensor front center left:
  auto ultrasonicSensorFrontCenterLeft = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicFrontLeftCenter);

  // ultrasnoic sensor front center right:
  auto ultrasonicSensorFrontCenterRight = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicFrontRightCenter);

  // ultrasnoic sensor front right:
  auto ultrasonicSensorFrontRight = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicFrontRight);

  // ultrasnoic sensor back left:
  auto ultrasonicSensorBackLeft = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicBackLeft);

  // ultrasnoic sensor back center left:
  auto ultrasonicSensorBackCenterLeft = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicBackLeftCenter);

  // ultrasnoic sensor back center right:
  auto ultrasonicSensorBackCenterRight = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicBackRightCenter);

  // ultrasnoic sensor back right:
  auto ultrasonicSensorBackRight = LocalConstructionFactory::createUltrasonicSensor(
      gpioDriver,
      ultrasonicService,
      configuration.ultrasonicBackRight);

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

std::shared_ptr<navigation::ISteering> LocalConstructionFactory::createSteering(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    SteeringConfiguration configuration)
{
  return std::make_shared<navigation::RCSteering>(
    std::make_shared<navigation::Servo>(
      pwmDriver,
      configuration.pin,
      configuration.min,
      configuration.max));
}

std::shared_ptr<propulsion::IMotor> LocalConstructionFactory::createMotor(
    std::shared_ptr<pwm::PwmDriver> pwmDriver,
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    MotorConfiguration configuration)
{
  return std::make_shared<propulsion::RCMotor>(
    std::make_shared<propulsion::PropulsionUnit>(
      pwmDriver,
      configuration.propulsionUnit.pin,
      configuration.propulsionUnit.forwardMin,
      configuration.propulsionUnit.forwardMax,
      configuration.propulsionUnit.backwardMin,
      configuration.propulsionUnit.backwardMax),
    std::make_shared<sensors::HallRpsSensor>(
      std::make_shared<sensors::HallSensor>(
        gpioDriver,
	      configuration.hallSensor.pin)));
}

std::shared_ptr<sensors::IDistanceSensor> LocalConstructionFactory::createUltrasonicSensor(
    std::shared_ptr<gpio::GpioDriver> gpioDriver,
    std::shared_ptr<sensors::UltrasonicService> ultrasonicService,
    UltrasonicSensorConfiguration configuration)
{
  auto sensor = std::make_shared<sensors::UltrasonicSensor>(
    configuration.measurementRangeMin,
    configuration.measurementRangeMax,
    configuration.measurementAccuracy,
    configuration.measurementAngle,
    configuration.triggerPin,
    configuration.echoPin);

  ultrasonicService->registerSensor(sensor);
  // TODO: deregisterSensor with retruned id

  return sensor;
}

} // namespace lupus::constructions
