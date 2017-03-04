#ifndef LIBS_Neighbor_HPP_
#define LIBS_Neighbor_HPP_
/*
 * IPCC_Neighbor.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "NeighborApplicationIF.hpp"
#include "cc/IPCCAdjacencyObserverIF.hpp"
#include "base/ProtocolTypes.hpp"                  // for DWORD

namespace lmp
{
  namespace neighbor
  {
    class Neighbor : public NeighborApplicationIF,
                            cc::IpccAdjacencyObserverIF
    {
    public:
      Neighbor(
        lmp::DWORD                       nodeId);
      virtual ~Neighbor(){}
    private:
      // implement NeighborApplicationIF
      virtual void do_enable();
      virtual void do_disable();
      virtual lmp::DWORD do_getNodeId() const;
      // implement IpccAdjacencyObserverIF
      virtual void do_ipccAdjacencyAdded(
        cc::IpccApplicationIF&   ipcc);
      virtual void do_ipccAdjacencyRemoved(
        cc::IpccApplicationIF&   ipcc);
      lmp::DWORD                  m_nodeId;
    };
  } // namespace neighbor
} // namespace lmp

#endif /* LIBS_Neighbor_HPP_ */
