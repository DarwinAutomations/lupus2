#ifndef PROPULSION_MOTOR_H
#define PROPULSION_MOTOR_H

namespace lupus::propulsion
{

class IMotor
{

public:
  virtual ~IMotor () = default;

  virtual void setPower(float power) = 0;
  virtual float getPower() = 0;
  virtual float getRps() = 0;

};

} // namespace lupus::propulsion

#endif /* PROPULSION_MOTOR_H */
