#include <stdexcept>
#include <math.h>

#include "propulsion_service.h"

namespace lupus::construction::motor
{

PropulsionService::PropulsionService (
  std::shared_ptr<construction::Lupus> lupus,
  std::shared_ptr<application::profiles::IProfile> profile)
{
  if(!lupus)
  {
    throw std::invalid_argument("lupus must not be null");
  }
  if(!profile)
  {
    throw std::invalid_argument("profile must not be null");
  }
  this->lupus = std::move(lupus);
  this->profile = std::move(profile);
}

void PropulsionService::setConstruction(std::shared_ptr<construction::Lupus> lupus)
{
  if(!lupus)
  {
    throw std::invalid_argument("lupus must not be null");
  }
  this->lupus = std::move(lupus);
}

void PropulsionService::setProfile(std::shared_ptr<application::profiles::IProfile> profile)
{
  if(!profile)
  {
    throw std::invalid_argument("profile must not be null");
  }
  this->profile = std::move(profile);
}

void PropulsionService::update(float deltatime)
{
  float power = this->getPower();

  if (this->isDecelerating)
  {
    float change = this->MAGIC_MAX_PER_MILLISECOND * deltatime;

    if(power > 0)
    {
      change *= -1;
    }

    if(std::abs(power) < std::abs(change))
    {
      change = -power;
    }

    power += change;
  }
  else
  {
    float profile_acceleration = this->profile->computeAcceleration(acceleration);
    float change = profile_acceleration * this->MAGIC_MAX_PER_MILLISECOND * deltatime;
    power += change;
  }

  if(power > 1) power = 1;
  if(power < -1) power = -1;

  this->setPower(power);
}

float PropulsionService::getPower()
{
  float power = 0;
  power += this->lupus->getPower(Motor::FrontLeft);
  power += this->lupus->getPower(Motor::FrontRight);
  power += this->lupus->getPower(Motor::BackLeft);
  power += this->lupus->getPower(Motor::BackRight);
  power /= 4;
  return power;
}

void PropulsionService::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }

  this->lupus->setPower(Motor::FrontLeft, power);
  this->lupus->setPower(Motor::FrontRight, power);
  this->lupus->setPower(Motor::BackLeft, power);
  this->lupus->setPower(Motor::BackRight, power);
}

void PropulsionService::setAcceleration(float acceleration)
{
  this->isDecelerating = false;
  this->acceleration = acceleration;
}

void PropulsionService::decelerate()
{
  this->isDecelerating = true;
}

}
