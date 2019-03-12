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

  LupusConfigurationRepository::getSteering(
    configFile.lookup("lupus.steeringLeft"),
    config->steeringLeft);
  LupusConfigurationRepository::getSteering(
    configFile.lookup("lupus.steeringRight"),
    config->steeringRight);

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

  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicFrontLeft"),
    config->ultrasonicFrontLeft);
  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicFrontLeftCenter"),
    config->ultrasonicFrontLeftCenter);
  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicFrontRightCenter"),
    config->ultrasonicFrontRightCenter);
  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicFrontRight"),
    config->ultrasonicFrontRight);

  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicBackLeft"),
    config->ultrasonicBackLeft);
  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicBackLeftCenter"),
    config->ultrasonicBackLeftCenter);
  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicBackRightCenter"),
    config->ultrasonicBackRightCenter);
  LupusConfigurationRepository::getDistanceSensor(
    configFile.lookup("lupus.ultrasonicBackRight"),
    config->ultrasonicBackRight);

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


  LupusConfigurationRepository::setSteering(
    construction.add("steeringLeft", libconfig::Setting::Type::TypeGroup),
    config->steeringLeft);
  LupusConfigurationRepository::setSteering(
    construction.add("steeringRight", libconfig::Setting::Type::TypeGroup),
    config->steeringRight);

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

  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicFrontLeft", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontLeft);
  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicFrontLeftCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontLeftCenter);
  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicFrontRightCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontRightCenter);
  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicFrontRight", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontRight);

  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicBackLeft", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackLeft);
  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicBackLeftCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackLeftCenter);
  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicBackRightCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackRightCenter);
  LupusConfigurationRepository::setDistanceSensor(
    construction.add("ultrasonicBackRight", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackRight);

  configFile.writeFile(file);
}

void LupusConfigurationRepository::getSteering(
    libconfig::Setting& config,
    SteeringConfiguration& steering)
{
  steering.pin = config.lookup("pin");
  steering.min = config.lookup("min");
  steering.max = config.lookup("max");
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

  motor.hallSensor.pin = config.lookup("hallSensor.pin");
}

void LupusConfigurationRepository::getDistanceSensor(
    libconfig::Setting& config,
    UltrasonicSensorConfiguration& sensor)
{
  sensor.measurementRangeMin = config.lookup("measurementRangeMin");
  sensor.measurementRangeMax = config.lookup("measurementRangeMax");
  sensor.measurementAccuracy = config.lookup("measurementAccuracy");
  sensor.measurementAngle = config.lookup("measurementAngle");
  sensor.triggerPin = config.lookup("triggerPin");
  sensor.echoPin = config.lookup("echoPin");
}

void LupusConfigurationRepository::setSteering(
    libconfig::Setting& config,
    SteeringConfiguration& steering)
{
  config.add("pin", libconfig::Setting::Type::TypeInt) = steering.pin;
  config.add("min", libconfig::Setting::Type::TypeInt) = steering.min;
  config.add("max", libconfig::Setting::Type::TypeInt) = steering.max;
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
  sensor.add("pin", libconfig::Setting::Type::TypeInt) = motor.hallSensor.pin;
}

void LupusConfigurationRepository::setDistanceSensor(
    libconfig::Setting& config,
    UltrasonicSensorConfiguration& sensor)
{
  config.add("measurementRangeMin", libconfig::Setting::Type::TypeFloat) = sensor.measurementRangeMin;
  config.add("measurementRangeMax", libconfig::Setting::Type::TypeFloat) = sensor.measurementRangeMax;
  config.add("measurementAccuracy", libconfig::Setting::Type::TypeFloat) = sensor.measurementAccuracy;
  config.add("measurementAngle", libconfig::Setting::Type::TypeFloat) = sensor.measurementAngle;
  config.add("triggerPin", libconfig::Setting::Type::TypeInt) = sensor.triggerPin;
  config.add("echoPin", libconfig::Setting::Type::TypeInt) = sensor.echoPin;
}

}
