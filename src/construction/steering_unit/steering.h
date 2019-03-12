#ifndef NAVIGATION_STEERING_H
#define NAVIGATION_STEERING_H

namespace lupus::construction::steeringUnit
{

enum SteeringUnit
{
  Left,
  Right
};

class ISteering
{
public:
  virtual ~ISteering () = default;
  virtual void setDirection(float direction) = 0;
  virtual float getDirection() = 0;
  virtual float getRawDirection() = 0;
};

}

#endif /* NAVIGATION_STEERING_H */
