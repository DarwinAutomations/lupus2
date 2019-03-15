#ifndef CONTROLLERS_INTELLIGENT_CONTROLLER_H
#define CONTROLLERS_INTELLIGENT_CONTROLLER_H

#include <memory>
#include <thread>

#include "controller.h"
#include "lupus.h"

namespace lupus::construction
{

class LupusController : public IController
{
  private:
    std::shared_ptr<construction::Lupus> lupus;
    std::thread updateThread;
    bool isRunning = false;
    float const MAGIC_MAX_PER_MILLISECOND = 0.0005;
    bool isDecelerating = false;
    float acceleration = 0;
    float power = 0;

    void updateLoop();
    void update(float deltatime);
    void setPower(float power);
    float getPower();

  public:
    LupusController(
      std::shared_ptr<construction::Lupus> lupus);
    ~LupusController ();

    void setAcceleration(float accleration);
    void decelerate();

    void setDirection(float direction);
    float getDirection();
};

}

#endif /* CONTROLLERS_INTELLIGENT_CONTROLLER_H */
