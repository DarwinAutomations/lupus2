#ifndef NAVIGATION_RC_STEERING_H
#define NAVIGATION_RC_STEERING_H

#include <memory>

#include "steering.h"
#include "servo.h"

namespace lupus::construction::steeringUnit
{

class RCSteering final: public ISteering
{
private:
  std::shared_ptr<Servo> servo;

public:
  RCSteering (std::shared_ptr<Servo> servo);
  virtual ~RCSteering () = default;

  void setDirection(float direction);
  float getDirection();
  float getRawDirection();
};

}

#endif /* NAVIGATION_RC_STEERING_H */
