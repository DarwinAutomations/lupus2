#ifndef PROPULSION_PROPULSION_SERVICE_H
#define PROPULSION_PROPULSION_SERVICE_H

#include <memory>

#include "lupus.h"
#include "profile.h"

namespace lupus::construction::motor
{

class PropulsionService
{
private:
  std::shared_ptr<construction::Lupus> lupus;
  std::shared_ptr<application::profiles::IProfile> profile;
  float const MAGIC_MAX_PER_MILLISECOND = 0.0005;
  bool isDecelerating = false;
  float acceleration = 0;

  void setPower(float power);
  float getPower();

public:
  PropulsionService (
  	std::shared_ptr<construction::Lupus> lupus,
      std::shared_ptr<application::profiles::IProfile> profile);
  virtual ~PropulsionService () = default;

  void setConstruction(std::shared_ptr<construction::Lupus> lupus);
  void setProfile(std::shared_ptr<application::profiles::IProfile> profile);

  void update(float deltaTime);

  void setAcceleration(float acceleration);
  void decelerate();
};

}

#endif /* PROPULSION_PROPULSION_SERVICE_H */
