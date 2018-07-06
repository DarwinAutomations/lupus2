#ifndef PROPULSION_UNIT_H
#define PROPULSION_UNIT_H

#include <memory>

#include "control_unit.h"
#include "hall_sensor.h"

namespace lupus::navigation
{

class PropulsionUnit
{
  private:
    std::shared_ptr<IControlUnit> controlUnit;
    std::shared_ptr<sensors::HallSensor> hallSensor;

  public:
    PropulsionUnit (
      std::shared_ptr<IControlUnit> controlUnit,
      std::shared_ptr<sensors::HallSensor> hallSensor);
    virtual ~PropulsionUnit () = default;

    void setPower(float power);
    float getPower();
    float getRps();
};

} // namespace lupus::navigation

#endif /* PROPULSION_UNIT_H */
