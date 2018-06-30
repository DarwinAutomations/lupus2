#ifndef CONSTRUCTIONS_SIMULATED_CONSTRUCTION_FACTORY_H
#define CONSTRUCTIONS_SIMULATED_CONSTRUCTION_FACTORY_H

#include "local_construction.h"

namespace lupus::constructions
{

class SimulatedConstructionFactory
{
  public:
    static std::shared_ptr<LocalConstruction> create(
      /* pins etc */ );
};

} // namespace lupus::consturctions

#endif /* CONSTRUCTIONS_SIMULATED_CONSTRUCTION_FACTORY_H */
