#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H

#include <libconfig.h++>
#include <memory>

namespace lupus::constructions
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

class LocalConstructionConfiguration
{
private:
  static void steering(
      libconfig::Setting& config,
      SteeringConfiguration& steering);

  static void motor(
      libconfig::Setting& config,
      MotorConfiguration& motor);

  static void distanceSensor(
      libconfig::Setting& config,
      UltrasonicSensorConfiguration& sensor);

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

  static std::shared_ptr<LocalConstructionConfiguration> fromFile(const char* file);
};

} // namespace lupus::consturctions

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H */
