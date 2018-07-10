#ifndef NAVIGATION_PROPULSION_MOTOR_H
#define NAVIGATION_PROPULSION_MOTOR_H

namespace lupus::navigation::propulsion
{

class IMotor
{

public:
  virtual ~IMotor () = default;

  virtual void setPower(float power) = 0;
  virtual float getPower() = 0;
  virtual float getRps() = 0;

};

} // namespace lupus::navigation::propulsion

#endif /* NAVIGATION_PROPULSION_MOTOR_H */
