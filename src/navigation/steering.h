#ifndef NAVIGATION_STEERING_H
#define NAVIGATION_STEERING_H

namespace lupus::navigation
{

enum Steering
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
};

} // namespace lupus::navigation

#endif /* NAVIGATION_STEERING_H */
