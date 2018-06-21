#ifndef CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H
#define CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H

#include "local_construction.h"
#include "ultrasonic_service.h"

namespace lupus::constructions
{

class LocalConstructionFactory
{
  public:
    static LocalConstruction* create(
      sensors::UltrasonicService* ultrasonicService 
      /* pins etc */ );
};

} // namespace lupus::consturctions

#endif /* CONSTRUCTIONS_LOCAL_CONSTRUCTION_FACTORY_H */
