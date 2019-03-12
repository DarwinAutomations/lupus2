#include <stdexcept>
#include <memory>
#include <chrono>
#include <thread>

#include "intelligent_controller.h"
#include "construction.h"

namespace lupus::controllers
{

IntelligentController::IntelligentController(
  std::shared_ptr<constructions::IConstruction> construction,
  std::shared_ptr<propulsion::PropulsionService> propulsionService
)
{
  if (!construction)
  {
    throw std::invalid_argument("construction cannot be null");
  }

  if (!propulsionService)
  {
    throw std::invalid_argument("propulsion service cannot be null");
  }

  this->construction = std::move(construction);
  this->propulsionService = std::move(propulsionService);

  this->isRunning = true;
  this->updateThread = std::thread(
    &IntelligentController::updateLoop, this);
}

IntelligentController::~IntelligentController()
{
  this->isRunning = false;
  this->updateThread.join();
}

void IntelligentController::updateLoop()
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

void IntelligentController::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  this->construction->setDirection(navigation::SteeringUnit::Left, direction);
  this->construction->setDirection(navigation::SteeringUnit::Right, direction);
}

float IntelligentController::getDirection()
{
  float direction = 0;
  direction += this->construction->getDirection(navigation::SteeringUnit::Left);
  direction += this->construction->getDirection(navigation::SteeringUnit::Right);
  direction /= 2;
  return direction;
}

void IntelligentController::setAcceleration(float acceleration)
{
  this->propulsionService->setAcceleration(acceleration);
}

void IntelligentController::decelerate()
{
  this->propulsionService->decelerate();
}

} // namespace lupus::controllers
