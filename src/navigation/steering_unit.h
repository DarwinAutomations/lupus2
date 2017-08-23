#ifndef STEERING_UNIT_H
#define STEERING_UNIT_H

#include "control_unit.h"

namespace lupus::navigation
{

class SteeringUnit
{
  private:
    IControlUnit* controlUnit;

  public:
    SteeringUnit (IControlUnit* controlUnit);
    virtual ~SteeringUnit () = default;
    void setDirection(float direction);
};

} // namespace lupus::navigation

#endif /* STEERING_UNIT_H */
