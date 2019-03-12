#ifndef PROPULSION_MOTOR_H
#define PROPULSION_MOTOR_H

namespace lupus::construction::motor
{
enum Motor
{
  FrontLeft,
  FrontRight,
  BackLeft,
  BackRight
};
class IMotor
{

public:
  virtual ~IMotor () = default;

  virtual void setPower(float power) = 0;
  virtual float getPower() = 0;
  virtual float getRawPower() = 0;
  virtual float getRps() = 0;

};

}

#endif /* PROPULSION_MOTOR_H */
