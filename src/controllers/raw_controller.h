#ifndef CONTROLLERS_RAW_CONTROLLER_H
#define CONTROLLERS_RAW_CONTROLLER_H

#include <memory>

#include "controller.h"
#include "construction.h"

namespace lupus::controllers
{

class RawController : public IController
{
  private:
    std::shared_ptr<constructions::IConstruction> construction;

  public:
    RawController(std::shared_ptr<constructions::IConstruction> construction);
    virtual ~RawController () = default;

    void setPower(float power);
    float getPower();
    void setDirection(float direction);
    float getDirection();
};

} // namespace lupus::controllers

#endif /* CONTROLLERS_RAW_CONTROLLER_H */
