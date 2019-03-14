#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H

#include <libconfig.h++>
#include <memory>

#include "distance_sensor_config.h"

namespace lupus::construction
{

struct SteeringConfiguration
{
  int pin;
  int min;
  int max;
};

struct PropulsionUnitConfiguration
{
  int pin;
  int forwardMin;
  int forwardMax;
  int backwardMin;
  int backwardMax;
};

struct HallSensorConfiguration
{
  int pin;
};

struct MotorConfiguration
{
  PropulsionUnitConfiguration propulsionUnit;
  HallSensorConfiguration hallSensor;
};

class LupusConfiguration
{
public:
  SteeringConfiguration steeringLeft;
  SteeringConfiguration steeringRight;

  MotorConfiguration motorFrontLeft;
  MotorConfiguration motorFrontRight;
  MotorConfiguration motorBackLeft;
  MotorConfiguration motorBackRight;

  distanceSensor::DistanceSensorConfiguration* ultrasonicFrontLeft;
  distanceSensor::DistanceSensorConfiguration* ultrasonicFrontLeftCenter;
  distanceSensor::DistanceSensorConfiguration* ultrasonicFrontRightCenter;
  distanceSensor::DistanceSensorConfiguration* ultrasonicFrontRight;
  distanceSensor::DistanceSensorConfiguration* ultrasonicBackLeft;
  distanceSensor::DistanceSensorConfiguration* ultrasonicBackLeftCenter;
  distanceSensor::DistanceSensorConfiguration* ultrasonicBackRightCenter;
  distanceSensor::DistanceSensorConfiguration* ultrasonicBackRight;
};

class LupusConfigurationRepository
{
private:
  static void getSteering(
      libconfig::Setting& config,
      SteeringConfiguration& steering);
  static void getMotor(
      libconfig::Setting& config,
      MotorConfiguration& motor);

  static void setSteering(
      libconfig::Setting& config,
      SteeringConfiguration& steering);
  static void setMotor(
      libconfig::Setting& config,
      MotorConfiguration& motor);
public:
  static std::shared_ptr<LupusConfiguration> fromFile(
      const char* file);
  static void toFile(
      const char* file,
      std::shared_ptr<LupusConfiguration>);
};

}

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H */
