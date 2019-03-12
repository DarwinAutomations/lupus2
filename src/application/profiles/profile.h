#ifndef PROFILES_PROFILE_H
#define PROFILES_PROFILE_H

namespace lupus::application::profiles
{

class IProfile
{
  public:
    virtual ~IProfile () = default;
    virtual float computeAcceleration(float acceleration) = 0;
};

}

#endif /* PROFILES_PROFILE_H */
