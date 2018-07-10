#ifndef NAVIGATION_PROPULSION_PROPULSION_SERVICE_H
#define NAVIGATION_PROPULSION_PROPULSION_SERVICE_H

#include <memory>

#include "construction.h"
#include "profile.h"

namespace lupus::navigation::propulsion
{

class PropulsionService
{
private:
  std::shared_ptr<constructions::IConstruction> construction;
  std::shared_ptr<profiles::IProfile> profile;
  float const MAGIC_MAX_PER_MILLISECOND = 0.0005;
  bool isDecelerating = false;
  float acceleration = 0;

  void setPower(float power);
  float getPower();

public:
  PropulsionService (
  	std::shared_ptr<constructions::IConstruction> construction,
      std::shared_ptr<profiles::IProfile> profile);
  virtual ~PropulsionService () = default;

  void setConstruction(std::shared_ptr<constructions::IConstruction> construction);
  void setProfile(std::shared_ptr<profiles::IProfile> profile);

  void update(float deltaTime);

  void setAcceleration(float acceleration);
  void decelerate();
};

} // namespace lupus::navigation::propulsion

#endif /* NAVIGATION_PROPULSION_PROPULSION_SERVICE_H */
