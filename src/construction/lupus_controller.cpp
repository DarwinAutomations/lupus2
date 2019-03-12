#include <stdexcept>
#include <memory>
#include <chrono>
#include <thread>

#include "lupus_controller.h"
#include "lupus.h"

namespace lupus::construction
{

LupusController::LupusController(
  std::shared_ptr<construction::Lupus> lupus,
  std::shared_ptr<construction::motor::PropulsionService> propulsionService
)
{
  if (!lupus)
  {
    throw std::invalid_argument("lupus cannot be null");
  }

  if (!propulsionService)
  {
    throw std::invalid_argument("propulsion service cannot be null");
  }

  this->lupus = std::move(lupus);
  this->propulsionService = std::move(propulsionService);

  this->isRunning = true;
  this->updateThread = std::thread(
    &LupusController::updateLoop, this);
}

LupusController::~LupusController()
{
  this->isRunning = false;
  this->updateThread.join();
}

void LupusController::updateLoop()
{
  auto last = std::chrono::high_resolution_clock::now();
  while(this->isRunning)
  {
    auto current = std::chrono::high_resolution_clock::now();
    float deltatime = std::chrono::duration_cast<std::chrono::milliseconds>(current - last).count();
    last = current;
    this->propulsionService->update(deltatime);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void LupusController::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  this->lupus->setDirection(construction::steeringUnit::SteeringUnit::Left, direction);
  this->lupus->setDirection(construction::steeringUnit::SteeringUnit::Right, direction);
}

float LupusController::getDirection()
{
  float direction = 0;
  direction += this->lupus->getDirection(construction::steeringUnit::SteeringUnit::Left);
  direction += this->lupus->getDirection(construction::steeringUnit::SteeringUnit::Right);
  direction /= 2;
  return direction;
}

void LupusController::setAcceleration(float acceleration)
{
  this->propulsionService->setAcceleration(acceleration);
}

void LupusController::decelerate()
{
  this->propulsionService->decelerate();
}

}
