#ifndef PROPULSION_UNIT_H
#define PROPULSION_UNIT_H

#include "control_unit.h"

namespace lupus::navigation
{

class PropulsionUnit
{
  private:
    IControlUnit* controlUnit;

  public:
    PropulsionUnit (IControlUnit* controlUnit);
    virtual ~PropulsionUnit () = default;
    void setPower(float power);
    float getPower();
};

} // namespace lupus::navigation

#endif /* PROPULSION_UNIT_H */
