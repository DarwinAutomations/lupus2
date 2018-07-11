#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H

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
  float triggerPin;
  float echoPin;
};

struct LocalConstructionConfiguration
{
  SteeringConfiguration servoLeft;
  SteeringConfiguration servoRight;

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

} // namespace lupus::consturctions

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_CONFIGURATION_H */
