#ifndef STEERING_UNIT_H
#define STEERING_UNIT_H

#include <memory>
#include "control_unit.h"

namespace lupus::navigation
{

class SteeringUnit
{
  private:
    std::shared_ptr<IControlUnit> controlUnit;

  public:
    SteeringUnit(std::shared_ptr<IControlUnit> controlUnit);
    virtual ~SteeringUnit () = default;
    void setDirection(float direction);
    float getDirection();
};

} // namespace lupus::navigation

#endif /* STEERING_UNIT_H */
