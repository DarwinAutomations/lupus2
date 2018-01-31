#include <stdexcept>
#include <math.h>

#include "acceleration_service.h"

namespace lupus::navigation
{
AccelerationService::AccelerationService (
  construction::Lupus* construction,
  profiles::IProfile* profile)
{
  if(!construction)
  {
    throw std::invalid_argument("construction must not be null");
  }
  if(!profile)
  {
    throw std::invalid_argument("profile must not be null");
  }
  this->construction = construction;
  this->profile = profile;
}

void AccelerationService::setConstruction(construction::Lupus* construction)
{
  if(!construction)
  {
    throw std::invalid_argument("construction must not be null");
  }
  this->construction = construction;
}

void AccelerationService::setProfile(profiles::IProfile* profile)
{
  if(!profile)
  {
    throw std::invalid_argument("profile must not be null");
  }
  this->profile = profile;
}

void AccelerationService::setAcceleration(float acceleration, float deltatime)
{
  float profile_acceleration = this->profile->computeAcceleration(acceleration);

  float change = profile_acceleration * this->MAGIC_MAX_PER_MILLISECOND * deltatime;

  float power = this->construction->getPower();
  power += change;

  if(power > 1) power = 1;
  if(power < -1) power = -1;

  this->construction->setPower(power);
}

void AccelerationService::decelerate(float deltatime)
{
  float power = this->construction->getPower();
  float change = this->MAGIC_MAX_PER_MILLISECOND * deltatime;
  if(power > 0)
  {
    change *= -1;
  }
  if(std::abs(power) < std::abs(change))
  {
    change = -power;
  }

  this->construction->setPower(power + change);
}

}
