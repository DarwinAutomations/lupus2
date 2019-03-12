#ifndef PROFILES_GRANNY_h
#define PROFILES_GRANNY_h

#include "profile.h"

namespace lupus::application::profiles
{

class GrannyProfile : public IProfile
{
  public:
    GrannyProfile () = default;
    virtual ~GrannyProfile () = default;
    float computeAcceleration(float acceleration) override;
};

}

#endif /* PROFILES_GRANNY_h */
