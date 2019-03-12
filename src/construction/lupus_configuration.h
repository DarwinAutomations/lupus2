#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H

#include <libconfig.h++>
#include <memory>

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

struct UltrasonicSensorConfiguration
{
  float measurementRangeMin;
  float measurementRangeMax;
  float measurementAccuracy;
  float measurementAngle;
  int triggerPin;
  int echoPin;
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

  UltrasonicSensorConfiguration ultrasonicFrontLeft;
  UltrasonicSensorConfiguration ultrasonicFrontLeftCenter;
  UltrasonicSensorConfiguration ultrasonicFrontRightCenter;
  UltrasonicSensorConfiguration ultrasonicFrontRight;
  UltrasonicSensorConfiguration ultrasonicBackLeft;
  UltrasonicSensorConfiguration ultrasonicBackLeftCenter;
  UltrasonicSensorConfiguration ultrasonicBackRightCenter;
  UltrasonicSensorConfiguration ultrasonicBackRight;
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
  static void getDistanceSensor(
      libconfig::Setting& config,
      UltrasonicSensorConfiguration& sensor);

  static void setSteering(
      libconfig::Setting& config,
      SteeringConfiguration& steering);
  static void setMotor(
      libconfig::Setting& config,
      MotorConfiguration& motor);
  static void setDistanceSensor(
      libconfig::Setting& config,
      UltrasonicSensorConfiguration& sensor);
public:
  static std::shared_ptr<LupusConfiguration> fromFile(
      const char* file);
  static void toFile(
      const char* file,
      std::shared_ptr<LupusConfiguration>);
};

}

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H */
