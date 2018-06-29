#ifndef CONTROLLERS_RAW_CONTROLLER_H
#define CONTROLLERS_RAW_CONTROLLER_H

#include <memory>
#include <thread>

#include "controller.h"
#include "construction.h"
#include "propulsion_service.h"

namespace lupus::controllers
{

class IntelligentController : public IController
{
  private:
    std::shared_ptr<constructions::IConstruction> construction;
    std::shared_ptr<navigation::PropulsionService> propulsionService;
    std::thread updateThread;
    bool isRunning = false;

    void updateLoop();
    void setPower(float power);
    float getPower();

  public:
    IntelligentController(
      std::shared_ptr<constructions::IConstruction> construction,
      std::shared_ptr<navigation::PropulsionService> propulsionService);
    virtual ~IntelligentController ();

    void setAcceleration(float accleration);
    void decelerate();

    void setDirection(float direction);
    float getDirection();
};

} // namespace lupus::controllers

#endif /* CONTROLLERS_RAW_CONTROLLER_H */
