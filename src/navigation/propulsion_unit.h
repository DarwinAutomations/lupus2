#ifndef PROPULSION_UNIT_H
#define PROPULSION_UNIT_H

#include <memory>
#include "control_unit.h"

namespace lupus::navigation
{

class PropulsionUnit
{
  private:
    std::shared_ptr<IControlUnit> controlUnit;

  public:
    PropulsionUnit (std::shared_ptr<IControlUnit> controlUnit);
    virtual ~PropulsionUnit () = default;
    void setPower(float power);
    float getPower();
};

} // namespace lupus::navigation

#endif /* PROPULSION_UNIT_H */
