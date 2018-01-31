#ifndef NAVIGATION_ACCELERATION_SERVICE_H
#define NAVIGATION_ACCELERATION_SERVICE_H

#include "lupus.h"
#include "profile.h"

namespace lupus::navigation
{

class AccelerationService
{
  private:
    construction::Lupus* construction;
    profiles::IProfile* profile;
    float const MAGIC_MAX_PER_MILLISECOND = 0.0005;


  public:
    AccelerationService (
        construction::Lupus* construction,
        profiles::IProfile* profile);
    virtual ~AccelerationService () = default;

    void setConstruction(construction::Lupus* construction);
    void setProfile(profiles::IProfile* profile);

    void setAcceleration(float acceleration, float delattime);
    void decelerate(float deltatime);
};

} // namespace lupus::navigation

#endif /* NAVIGATION_ACCELERATION_SERVICE_H */
