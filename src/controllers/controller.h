#ifndef CONTROLLERS_CONTROLLER_H
#define CONTROLLERS_CONTROLLER_H

namespace lupus::controllers
{

class IController
{
  public:
    virtual ~IController () = default;

    virtual void setAcceleration(float acceleration) = 0;
    virtual void decelerate() = 0;
    virtual void setDirection(float direction) = 0;
    virtual float getDirection() = 0;
};

} // namespace lupus::controllers

#endif /* CONTROLLERS_CONTROLLER_H */
