#include <libconfig.h++>

#include "lupus_repository.h"
#include "ultrasonic_service.h"
#include "ultrasonic_sensor.h"
#include "distance_sensor_config.h"
#include "propulsion_unit.h"
#include "propulsion_unit_config.h"
#include "hall_rps_sensor.h"
#include "hall_rps_sensor_config.h"
#include "steering_unit.h"
#include "steering_unit_config.h"


namespace lupus::construction
{

LupusRepository::LupusRepository(
  std::shared_ptr<drivers::gpio::GpioDriver> gpioDriver,
  std::shared_ptr<drivers::pwm::PwmDriver> pwmDriver,
  std::shared_ptr<distanceSensor::UltrasonicService> ultrasonicService
)
{
  if(!gpioDriver)
  {
    throw std::invalid_argument("gpio dirver must not be null");
  }
  if(!pwmDriver)
  {
    throw std::invalid_argument("pwm dirver must not be null");
  }
  if(!ultrasonicService)
  {
    throw std::invalid_argument("ultrasonic service must not be null");
  }

  this->gpioDriver = gpioDriver;
  this->pwmDriver = pwmDriver;
  this->ultrasonicService = ultrasonicService;
}

std::shared_ptr<Lupus> LupusRepository::readFromFile(const char* fileName)
{
  libconfig::Config config;
  config.readFile(fileName);

  // steering units
  auto steeringUnitLeft = std::make_shared<steeringUnit::SteeringUnit>(
      pwmDriver,
      steeringUnit::SteeringUnitConfiguration::fromSetting(
        config.lookup("lupus.steeringUnitLeft")));

  auto steeringUnitRight = std::make_shared<steeringUnit::SteeringUnit>(
      pwmDriver,
      steeringUnit::SteeringUnitConfiguration::fromSetting(
        config.lookup("lupus.steeringUnitRight")));

  // motors
  auto motorFrontLeft = std::make_shared<motor::Motor>(
    std::make_shared<motor::propulsionUnit::PropulsionUnit>(
      pwmDriver,
      motor::propulsionUnit::PropulsionUnitConfiguration::fromSetting(
        config.lookup("lupus.motorFrontLeft.propulsionUnit"))),
    std::make_shared<motor::rpsSensor::HallRpsSensor>(
      gpioDriver,
      motor::rpsSensor::HallRpsSensorConfiguration::fromSetting(
        config.lookup("lupus.motorFrontLeft.hallSensor"))));

  auto motorFrontRight = std::make_shared<motor::Motor>(
    std::make_shared<motor::propulsionUnit::PropulsionUnit>(
      pwmDriver,
      motor::propulsionUnit::PropulsionUnitConfiguration::fromSetting(
        config.lookup("lupus.motorFrontRight.propulsionUnit"))),
    std::make_shared<motor::rpsSensor::HallRpsSensor>(
      gpioDriver,
      motor::rpsSensor::HallRpsSensorConfiguration::fromSetting(
        config.lookup("lupus.motorFrontRight.hallSensor"))));

  auto motorBackLeft = std::make_shared<motor::Motor>(
    std::make_shared<motor::propulsionUnit::PropulsionUnit>(
      pwmDriver,
      motor::propulsionUnit::PropulsionUnitConfiguration::fromSetting(
        config.lookup("lupus.motorBackLeft.propulsionUnit"))),
    std::make_shared<motor::rpsSensor::HallRpsSensor>(
      gpioDriver,
      motor::rpsSensor::HallRpsSensorConfiguration::fromSetting(
        config.lookup("lupus.motorBackLeft.hallSensor"))));

  auto motorBackRight = std::make_shared<motor::Motor>(
    std::make_shared<motor::propulsionUnit::PropulsionUnit>(
      pwmDriver,
      motor::propulsionUnit::PropulsionUnitConfiguration::fromSetting(
        config.lookup("lupus.motorBackRight.propulsionUnit"))),
    std::make_shared<motor::rpsSensor::HallRpsSensor>(
      gpioDriver,
      motor::rpsSensor::HallRpsSensorConfiguration::fromSetting(
        config.lookup("lupus.motorBackRight.hallSensor"))));

  // distance sensors
  auto ultrasonicSensorFrontLeft = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicFrontLeft")));
  ultrasonicService->registerSensor(ultrasonicSensorFrontLeft);
  auto ultrasonicSensorFrontCenterLeft = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicFrontCenterLeft")));
  ultrasonicService->registerSensor(ultrasonicSensorFrontCenterLeft);
  auto ultrasonicSensorFrontCenterRight = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicFrontCenterRight")));
  ultrasonicService->registerSensor(ultrasonicSensorFrontCenterRight);
  auto ultrasonicSensorFrontRight = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicFrontRight")));
      ultrasonicService->registerSensor(ultrasonicSensorFrontRight);
  auto ultrasonicSensorBackLeft = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicBackLeft")));
  ultrasonicService->registerSensor(ultrasonicSensorBackLeft);
  auto ultrasonicSensorBackCenterLeft = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicBackCenterLeft")));
  ultrasonicService->registerSensor(ultrasonicSensorBackCenterLeft);
  auto ultrasonicSensorBackCenterRight = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicBackCenterRight")));
  ultrasonicService->registerSensor(ultrasonicSensorBackCenterRight);
  auto ultrasonicSensorBackRight = std::make_shared<distanceSensor::UltrasonicSensor>(
    distanceSensor::DistanceSensorConfiguration::fromSetting(
      config.lookup("lupus.ultrasonicBackRight")));
  ultrasonicService->registerSensor(ultrasonicSensorBackRight);

  // TODO: deregisterSensor with retruned id

 return std::make_shared<Lupus>(
    steeringUnitLeft,
    steeringUnitRight,

    motorFrontLeft, motorFrontRight,
    motorBackLeft, motorBackRight,

    ultrasonicSensorFrontLeft,
    ultrasonicSensorFrontCenterLeft,
    ultrasonicSensorFrontCenterRight,
    ultrasonicSensorFrontRight,
    ultrasonicSensorBackLeft,
    ultrasonicSensorBackCenterLeft,
    ultrasonicSensorBackCenterRight,
    ultrasonicSensorBackRight
  );
}

void LupusRepository::writeIntoFile(std::shared_ptr<Lupus> lupus)
{
  throw "LupusRepository::writeIntoFile not implemented.";
}

}
