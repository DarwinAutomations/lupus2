#include <stdexcept>
#include <math.h>

#include "propulsion_service.h"

namespace lupus::navigation::propulsion
{

PropulsionService::PropulsionService (
  std::shared_ptr<constructions::IConstruction> construction,
  std::shared_ptr<profiles::IProfile> profile)
{
  if(!construction)
  {
    throw std::invalid_argument("construction must not be null");
  }
  if(!profile)
  {
    throw std::invalid_argument("profile must not be null");
  }
  this->construction = std::move(construction);
  this->profile = std::move(profile);
}

void PropulsionService::setConstruction(std::shared_ptr<constructions::IConstruction> construction)
{
  if(!construction)
  {
    throw std::invalid_argument("construction must not be null");
  }
  this->construction = std::move(construction);
}

void PropulsionService::setProfile(std::shared_ptr<profiles::IProfile> profile)
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
  float power = this->construction->getPropulsionFrontLeftPower();
  power += this->construction->getPropulsionFrontRightPower();
  power += this->construction->getPropulsionBackLeftPower();
  power += this->construction->getPropulsionBackRightPower();
  power /= 4;
  return power;
}

void PropulsionService::setPower(float power)
{
  if(power > 1 || power < -1)
  {
    throw std::invalid_argument("power not in range -1, +1");
  }

  this->construction->setPropulsionFrontLeftPower(power);
  this->construction->setPropulsionFrontRightPower(power);
  this->construction->setPropulsionBackLeftPower(power);
  this->construction->setPropulsionBackRightPower(power);
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

} // namespace lupus::navigation::propulsion
