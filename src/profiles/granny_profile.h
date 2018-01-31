#ifndef PROFILES_GRANNY_h
#define PROFILES_GRANNY_h

#include "profile.h"

namespace lupus::profiles
{

class GrannyProfile : public IProfile
{
  public:
    GrannyProfile () = default;
    virtual ~GrannyProfile () = default;
    float computeAcceleration(float acceleration) override;
};

} // namespace lupus::profiles

#endif /* PROFILES_GRANNY_h */
