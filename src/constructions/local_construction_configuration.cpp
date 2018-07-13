#include <memory>
#include "local_construction_configuration.h"

namespace lupus::constructions
{
std::shared_ptr<LocalConstructionConfiguration>
LocalConstructionConfigurationRepository::fromFile(
    const char* file)
{
  libconfig::Config configFile;
  configFile.readFile(file);
  std::shared_ptr<LocalConstructionConfiguration> config = std::make_shared<LocalConstructionConfiguration>();

  LocalConstructionConfigurationRepository::getSteering(
    configFile.lookup("construction.steeringLeft"),
    config->steeringLeft);
  LocalConstructionConfigurationRepository::getSteering(
    configFile.lookup("construction.steeringRight"),
    config->steeringRight);

  LocalConstructionConfigurationRepository::getMotor(
    configFile.lookup("construction.motorFrontLeft"),
    config->motorFrontLeft);
  LocalConstructionConfigurationRepository::getMotor(
    configFile.lookup("construction.motorFrontRight"),
    config->motorFrontRight);
  LocalConstructionConfigurationRepository::getMotor(
    configFile.lookup("construction.motorBackLeft"),
    config->motorBackLeft);
  LocalConstructionConfigurationRepository::getMotor(
    configFile.lookup("construction.motorBackRight"),
    config->motorBackRight);

  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicFrontLeft"),
    config->ultrasonicFrontLeft);
  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicFrontLeftCenter"),
    config->ultrasonicFrontLeftCenter);
  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicFrontRightCenter"),
    config->ultrasonicFrontRightCenter);
  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicFrontRight"),
    config->ultrasonicFrontRight);

  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicBackLeft"),
    config->ultrasonicBackLeft);
  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicBackLeftCenter"),
    config->ultrasonicBackLeftCenter);
  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicBackRightCenter"),
    config->ultrasonicBackRightCenter);
  LocalConstructionConfigurationRepository::getDistanceSensor(
    configFile.lookup("construction.ultrasonicBackRight"),
    config->ultrasonicBackRight);

  return config;
}

void LocalConstructionConfigurationRepository::toFile(
    const char* file,
    std::shared_ptr<LocalConstructionConfiguration> config)
{
  libconfig::Config configFile;
  libconfig::Setting& root = configFile.getRoot();
  libconfig::Setting& consturction = root.add(
    "construciton", libconfig::Setting::Type::TypeGroup);


  LocalConstructionConfigurationRepository::setSteering(
    consturction.add("steeringLeft", libconfig::Setting::Type::TypeGroup),
    config->steeringLeft);
  LocalConstructionConfigurationRepository::setSteering(
    consturction.add("steeringRight", libconfig::Setting::Type::TypeGroup),
    config->steeringRight);

  LocalConstructionConfigurationRepository::setMotor(
    consturction.add("motorFrontLeft", libconfig::Setting::Type::TypeGroup),
    config->motorFrontLeft);
  LocalConstructionConfigurationRepository::setMotor(
    consturction.add("motorFrontRight", libconfig::Setting::Type::TypeGroup),
    config->motorFrontRight);
  LocalConstructionConfigurationRepository::setMotor(
    consturction.add("motorBackLeft", libconfig::Setting::Type::TypeGroup),
    config->motorBackLeft);
  LocalConstructionConfigurationRepository::setMotor(
    consturction.add("motorBackRight", libconfig::Setting::Type::TypeGroup),
    config->motorBackRight);

  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicFrontLeft", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontLeft);
  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicFrontLeftCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontLeftCenter);
  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicFrontRightCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontRightCenter);
  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicFrontRight", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicFrontRight);

  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicBackLeft", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackLeft);
  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicBackLeftCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackLeftCenter);
  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicBackRightCenter", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackRightCenter);
  LocalConstructionConfigurationRepository::setDistanceSensor(
    consturction.add("ultrasonicBackRight", libconfig::Setting::Type::TypeGroup),
    config->ultrasonicBackRight);

  configFile.writeFile(file);
}

void LocalConstructionConfigurationRepository::getSteering(
    libconfig::Setting& config,
    SteeringConfiguration& steering)
{
  steering.pin = config.lookup("pin");
  steering.min = config.lookup("min");
  steering.max = config.lookup("max");
}

void LocalConstructionConfigurationRepository::getMotor(
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

void LocalConstructionConfigurationRepository::getDistanceSensor(
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

void LocalConstructionConfigurationRepository::setSteering(
    libconfig::Setting& config,
    SteeringConfiguration& steering)
{
  config.add("pin", libconfig::Setting::Type::TypeInt) = steering.pin;
  config.add("min", libconfig::Setting::Type::TypeInt) = steering.min;
  config.add("max", libconfig::Setting::Type::TypeInt) = steering.max;
}

void LocalConstructionConfigurationRepository::setMotor(
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

void LocalConstructionConfigurationRepository::setDistanceSensor(
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

} // namespace lupus::constructions
