#ifndef LIBS_Neighbor_ADJACENCYOBSERVERIF_HPP_
#define LIBS_Neighbor_ADJACENCYOBSERVERIF_HPP_
/*
 * NeighborAdjacencyObserverIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp
{
  namespace cc
  {
    class IpccApplicationIF;
  }
  namespace neighbor
  {
    class NeighborApplicationIF;

    class NeighborAdjacencyObserverIF
    {
    public:
      inline NeighborApplicationIF const* getNeighbor(
        lmp::DWORD  neighborNodeId) const
      { return do_getNeighbor(neighborNodeId); }
      inline NeighborApplicationIF const* neighborAdjacencyAdded(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc)
      { return do_neighborAdjacencyAdded(neighborNodeId, ipcc); }
      inline bool neighborAdjacencyRemoved(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc)
      { return do_neighborAdjacencyRemoved(neighborNodeId, ipcc); }
      virtual ~NeighborAdjacencyObserverIF(){}
    private:
      virtual NeighborApplicationIF const* do_getNeighbor(
        lmp::DWORD  neighborNodeId) const = 0;
      virtual NeighborApplicationIF const* do_neighborAdjacencyAdded(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc) = 0;
      virtual bool do_neighborAdjacencyRemoved(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc) = 0;
    };
  } // namespace neighbor
} // namespace lmp


#endif /* LIBS_Neighbor_ADJACENCYOBSERVERIF_HPP_ */
