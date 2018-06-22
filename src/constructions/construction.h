#ifndef CONSTRUCTIONS_CONSTRUCTION_H
#define CONSTRUCTIONS_CONSTRUCTION_H

#include <memory>

namespace lupus::constructions
{

class IConstruction
{
  public:
    virtual ~IConstruction () = default;

    virtual void setPropulsionFrontLeftPower(float power) = 0;
    virtual void setPropulsionFrontRightPower(float power) = 0;
    virtual void setPropulsionBackLeftPower(float power) = 0;
    virtual void setPropulsionBackRightPower(float power) = 0;
    virtual float getPropulsionFrontLeftPower() = 0;
    virtual float getPropulsionFrontRightPower() = 0;
    virtual float getPropulsionBackLeftPower() = 0;
    virtual float getPropulsionBackRightPower() = 0;
    virtual void setSteeringLeftDirection(float direction) = 0;
    virtual void setSteeringRightDirection(float direction) = 0;
    virtual float getSteeringLeftDirection() = 0;
    virtual float getSteeringRightDirection() = 0;
};

} // namespace lupus::constructions

#endif /* CONSTRUCTIONS_CONSTRUCTION_H */
