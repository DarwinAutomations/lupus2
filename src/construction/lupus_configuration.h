#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H

#include <libconfig.h++>
#include <memory>

#include "hall_rps_sensor_config.h"
#include "propulsion_unit_config.h"
#include "distance_sensor_config.h"
#include "steering_unit_config.h"

namespace lupus::construction
{

struct MotorConfiguration
{
  motor::propulsionUnit::PropulsionUnitConfiguration* propulsionUnit;
  motor::rpsSensor::HallRpsSensorConfiguration* hallSensor;
};

class LupusConfiguration
{
public:
  steeringUnit::SteeringUnitConfiguration* steeringLeft;
  steeringUnit::SteeringUnitConfiguration* steeringRight;

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
  static void getMotor(
      libconfig::Setting& config,
      MotorConfiguration& motor);
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
