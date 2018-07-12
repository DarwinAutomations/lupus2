#include <memory>
#include "local_construction_configuration.h"

namespace lupus::constructions
{
std::shared_ptr<LocalConstructionConfiguration>
LocalConstructionConfiguration::fromFile(
    const char* file)
{
  libconfig::Config configFile;
  configFile.readFile(file);
  std::shared_ptr<LocalConstructionConfiguration> config = std::make_shared<LocalConstructionConfiguration>();

  LocalConstructionConfiguration::steering(
    configFile.lookup("construction.steeringLeft"),
    config->steeringLeft);
  LocalConstructionConfiguration::steering(
    configFile.lookup("construction.steeringRight"),
    config->steeringRight);

  LocalConstructionConfiguration::motor(
    configFile.lookup("construction.motorFrontLeft"),
    config->motorFrontLeft);
  LocalConstructionConfiguration::motor(
    configFile.lookup("construction.motorFrontRight"),
    config->motorFrontRight);
  LocalConstructionConfiguration::motor(
    configFile.lookup("construction.motorBackLeft"),
    config->motorBackLeft);
  LocalConstructionConfiguration::motor(
    configFile.lookup("construction.motorBackRight"),
    config->motorBackRight);

  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicFrontLeft"),
    config->ultrasonicFrontLeft);
  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicFrontLeftCenter"),
    config->ultrasonicFrontLeftCenter);
  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicFrontRightCenter"),
    config->ultrasonicFrontRightCenter);
  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicFrontRight"),
    config->ultrasonicFrontRight);

  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicBackLeft"),
    config->ultrasonicBackLeft);
  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicBackLeftCenter"),
    config->ultrasonicBackLeftCenter);
  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicBackRightCenter"),
    config->ultrasonicBackRightCenter);
  LocalConstructionConfiguration::distanceSensor(
    configFile.lookup("construction.ultrasonicBackRight"),
    config->ultrasonicBackRight);

  return config;
}

void LocalConstructionConfiguration::steering(
    libconfig::Setting& config,
    SteeringConfiguration& steering)
{
  steering.pin = config.lookup("pin");
  steering.min = config.lookup("min");
  steering.max = config.lookup("max");
}

void LocalConstructionConfiguration::motor(
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

void LocalConstructionConfiguration::distanceSensor(
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

} // namespace lupus::constructions
