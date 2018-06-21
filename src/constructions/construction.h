#ifndef CONSTRUCTIONS_CONSTRUCTION_H
#define CONSTRUCTIONS_CONSTRUCTION_H

#include <memory>

namespace lupus::constructions
{

class IConstruction
{
  public:
    virtual ~IConstruction () = default;

    virtual void setPower(float power) = 0;
    virtual float getPower() = 0;
    virtual void setDirection(float direction) = 0;
    virtual float getDirection() = 0;
};

} // namespace lupus::constructions

#endif /* CONSTRUCTIONS_CONSTURCTION_H */
