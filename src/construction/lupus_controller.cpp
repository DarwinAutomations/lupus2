#include <stdexcept>
#include <memory>
#include <chrono>
#include <thread>
#include <cmath>

#include "lupus_controller.h"
#include "lupus.h"

namespace lupus::construction
{

LupusController::LupusController(
  std::shared_ptr<construction::Lupus> lupus)
{
  if (!lupus)
  {
    throw std::invalid_argument("lupus cannot be null");
  }

  this->lupus = std::move(lupus);
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

    update(deltatime);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void LupusController::update(float deltatime)
{
  float power = this->getPower();
  float maxChange = MAGIC_MAX_PER_MILLISECOND * deltatime;

  if (!isDecelerating)
  {
    float newPower = power + maxChange * acceleration;
    if(power > 1) power = 1;
    else if(power < -1) power = -1;

    setPower(newPower);
    return;
  }

  if(power > 0) maxChange *= -1;
  float newPower = power + maxChange;
  if(std::abs(power) < std::abs(maxChange)) newPower = 0;

  this->setPower(newPower);
}

void LupusController::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }

  this->power = power;

  this->lupus->setPower(motor::MotorPosition::FrontLeft, power);
  this->lupus->setPower(motor::MotorPosition::FrontRight, power);
  this->lupus->setPower(motor::MotorPosition::BackLeft, power);
  this->lupus->setPower(motor::MotorPosition::BackRight, power);
}

float LupusController::getPower()
{
  return power;
}

void LupusController::setDirection(float direction)
{
  if(direction > 1 || direction < -1)
  {
    throw std::invalid_argument("direction not in range -1, +1");
  }

  this->lupus->setDirection(steeringUnit::SteeringUnitPosition::Left, direction);
  this->lupus->setDirection(steeringUnit::SteeringUnitPosition::Right, direction);
}

float LupusController::getDirection()
{
  float direction = 0;
  direction += this->lupus->getDirection(steeringUnit::SteeringUnitPosition::Left);
  direction += this->lupus->getDirection(steeringUnit::SteeringUnitPosition::Right);
  direction /= 2;
  return direction;
}

void LupusController::setAcceleration(float acceleration)
{
  this->isDecelerating = false;
  this->acceleration = acceleration;
}

void LupusController::decelerate()
{
  this->isDecelerating = true;
}

}
