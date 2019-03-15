#include <memory>

#include "lupus_configuration.h"

namespace lupus::construction
{

std::shared_ptr<LupusConfiguration>
LupusConfigurationRepository::fromFile(
    const char* file)
{
  libconfig::Config configFile;
  configFile.readFile(file);
  std::shared_ptr<LupusConfiguration> config = std::make_shared<LupusConfiguration>();

  auto steeringUnitLeft = std::move(
    steeringUnit::SteeringUnitConfiguration::fromSetting(
      configFile.lookup("lupus.steeringUnitLeft")));
  config->steeringLeft = &steeringUnitLeft;
    auto steeringRUnitight = std::move(
      steeringUnit::SteeringUnitConfiguration::fromSetting(
        configFile.lookup("lupus.steeringUnitRight")));
    config->steeringRight = &steeringRUnitight;

  LupusConfigurationRepository::getMotor(
    configFile.lookup("lupus.motorFrontLeft"),
    config->motorFrontLeft);
  LupusConfigurationRepository::getMotor(
    configFile.lookup("lupus.motorFrontRight"),
    config->motorFrontRight);
  LupusConfigurationRepository::getMotor(
    configFile.lookup("lupus.motorBackLeft"),
    config->motorBackLeft);
  LupusConfigurationRepository::getMotor(
    configFile.lookup("lupus.motorBackRight"),
    config->motorBackRight);

  auto ultrasonicFrontLeft = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicFrontLeft")));
  config->ultrasonicFrontLeft = &ultrasonicFrontLeft;
  auto ultrasonicFrontLeftCenter = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicFrontLeftCenter")));
  config->ultrasonicFrontLeftCenter = &ultrasonicFrontLeftCenter;
  auto ultrasonicFrontRightCenter = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicFrontRightCenter")));
  config->ultrasonicFrontRightCenter = &ultrasonicFrontRightCenter;
  auto ultrasonicFrontRight = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicFrontRight")));
  config->ultrasonicFrontRight = &ultrasonicFrontRight;

  auto ultrasonicBackLeft = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicBackLeft")));
  config->ultrasonicBackLeft = &ultrasonicBackLeft;
  auto ultrasonicBackLeftCenter = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicBackLeftCenter")));
  config->ultrasonicBackLeftCenter = &ultrasonicBackLeftCenter;
  auto ultrasonicBackRightCenter = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicBackRightCenter")));
  config->ultrasonicBackRightCenter = &ultrasonicBackRightCenter;
  auto ultrasonicBackRight = std::move(distanceSensor::DistanceSensorConfiguration::fromSetting(configFile.lookup("lupus.ultrasonicBackRight")));
  config->ultrasonicBackRight = &ultrasonicBackRight;

  return config;
}

void LupusConfigurationRepository::toFile(
    const char* file,
    std::shared_ptr<LupusConfiguration> config)
{
  libconfig::Config configFile;
  libconfig::Setting& root = configFile.getRoot();
  libconfig::Setting& construction = root.add(
    "construciton", libconfig::Setting::Type::TypeGroup);


  config->steeringLeft->intoSetting(
    construction.add("steeringLeft", libconfig::Setting::Type::TypeGroup));
  config->steeringRight->intoSetting(
    construction.add("steeringRight", libconfig::Setting::Type::TypeGroup));

  LupusConfigurationRepository::setMotor(
    construction.add("motorFrontLeft", libconfig::Setting::Type::TypeGroup),
    config->motorFrontLeft);
  LupusConfigurationRepository::setMotor(
    construction.add("motorFrontRight", libconfig::Setting::Type::TypeGroup),
    config->motorFrontRight);
  LupusConfigurationRepository::setMotor(
    construction.add("motorBackLeft", libconfig::Setting::Type::TypeGroup),
    config->motorBackLeft);
  LupusConfigurationRepository::setMotor(
    construction.add("motorBackRight", libconfig::Setting::Type::TypeGroup),
    config->motorBackRight);

  config->ultrasonicFrontLeft->intoSetting(
    construction.add(
      "ultrasonicFrontLeft",
      libconfig::Setting::Type::TypeGroup));
  config->ultrasonicFrontLeftCenter->intoSetting(
    construction.add(
      "ultrasonicFrontLeftCenter",
      libconfig::Setting::Type::TypeGroup));
  config->ultrasonicFrontRightCenter->intoSetting(
    construction.add(
      "ultrasonicFrontRightCenter",
      libconfig::Setting::Type::TypeGroup));
  config->ultrasonicFrontRight->intoSetting(
    construction.add(
      "ultrasonicFrontRight",
      libconfig::Setting::Type::TypeGroup));

  config->ultrasonicBackLeft->intoSetting(
    construction.add(
      "ultrasonicBackLeft",
      libconfig::Setting::Type::TypeGroup));
  config->ultrasonicBackLeftCenter->intoSetting(
    construction.add(
      "ultrasonicBackLeftCenter",
      libconfig::Setting::Type::TypeGroup));
  config->ultrasonicBackRightCenter->intoSetting(
    construction.add(
      "ultrasonicBackRightCenter",
      libconfig::Setting::Type::TypeGroup));
  config->ultrasonicBackRight->intoSetting(
    construction.add(
      "ultrasonicBackRight",
      libconfig::Setting::Type::TypeGroup));

  configFile.writeFile(file);
}

void LupusConfigurationRepository::getMotor(
    libconfig::Setting& config,
    MotorConfiguration& motor)
{
  motor.propulsionUnit.pin = config.lookup("propulsionUnit.pin");
  motor.propulsionUnit.forwardMin = config.lookup("propulsionUnit.forwardMin");
  motor.propulsionUnit.backwardMin = config.lookup("propulsionUnit.backwardMin");
  motor.propulsionUnit.forwardMax = config.lookup("propulsionUnit.forwardMax");
  motor.propulsionUnit.backwardMax = config.lookup("propulsionUnit.backwardMax");

  auto sensor = rpsSensor::HallRpsSensorConfiguration::fromSetting(config.lookup("hallSensor"));
  motor.hallSensor = &sensor;
}

void LupusConfigurationRepository::setMotor(
    libconfig::Setting& config,
    MotorConfiguration& motor)
{
  libconfig::Setting& propulsionUnit = config.add("propulsionUnit", libconfig::Setting::Type::TypeGroup);
  propulsionUnit.add("pin", libconfig::Setting::Type::TypeInt) = motor.propulsionUnit.pin;
  propulsionUnit.add("forwardMin", libconfig::Setting::Type::TypeInt) = motor.propulsionUnit.forwardMin;
  propulsionUnit.add("backwardMin", libconfig::Setting::Type::TypeInt) = motor.propulsionUnit.backwardMin;
  propulsionUnit.add("forwardMax", libconfig::Setting::Type::TypeInt) = motor.propulsionUnit.forwardMax;
  propulsionUnit.add("backwardMax", libconfig::Setting::Type::TypeInt) = motor.propulsionUnit.backwardMax;

  libconfig::Setting& sensor = config.add("hallSensor", libconfig::Setting::Type::TypeGroup);
  motor.hallSensor->intoSetting(sensor);
}

}
