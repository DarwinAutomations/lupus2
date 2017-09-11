#ifndef CONSTRUCTION_LUPUS_H
#define CONSTRUCTION_LUPUS_H

#include "steering_unit.h"
#include "propulsion_unit.h"

namespace lupus::construction
{

class Lupus
{
  private:
    navigation::SteeringUnit *steeringLeft;
    navigation::SteeringUnit *steeringRight;
    navigation::PropulsionUnit *propulsionFrontLeft;
    navigation::PropulsionUnit *propulsionFrontRight;
    navigation::PropulsionUnit *propulsionBackLeft;
    navigation::PropulsionUnit *propulsionBackRight;

  public:
    Lupus (
      navigation::SteeringUnit *steeringLeft,
      navigation::SteeringUnit *steeringRight,
      navigation::PropulsionUnit *propulsionFrontLeft,
      navigation::PropulsionUnit *propulsionFrontRight,
      navigation::PropulsionUnit *propulsionBackLeft,
      navigation::PropulsionUnit *propulsionBackRight
    );
    virtual ~Lupus () = default;

    void setPower(float power);
    void setDirection(float direction);
};

} // namespace lupus::navigation

#endif /* CONSTRUCTION_LUPUS_H */
