#ifndef CONTROLLERS_INTELLIGENT_CONTROLLER_H
#define CONTROLLERS_INTELLIGENT_CONTROLLER_H

#include <memory>
#include <thread>

#include "controller.h"
#include "lupus.h"
#include "propulsion_service.h"

namespace lupus::construction
{

class LupusController : public IController
{
  private:
    std::shared_ptr<construction::Lupus> lupus;
    std::shared_ptr<construction::motor::PropulsionService> propulsionService;
    std::thread updateThread;
    bool isRunning = false;

    void updateLoop();
    void setPower(float power);
    float getPower();

  public:
    LupusController(
      std::shared_ptr<construction::Lupus> lupus,
      std::shared_ptr<construction::motor::PropulsionService> propulsionService);
    ~LupusController ();

    void setAcceleration(float accleration);
    void decelerate();

    void setDirection(float direction);
    float getDirection();
};

}

#endif /* CONTROLLERS_INTELLIGENT_CONTROLLER_H */
