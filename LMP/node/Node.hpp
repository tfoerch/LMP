#ifndef LIBS_Node_HPP_
#define LIBS_Node_HPP_
/*
 * Node.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "node/NodeApplicationIF.hpp"

#include <map>

namespace lmp
{
  namespace node
  {
    class Node : public NodeApplicationIF
    {
    public:
      Node(
        lmp::DWORD                       nodeId);
      virtual ~Node(){}
    private:
      typedef std::map<lmp::DWORD, // nodeId
                       neighbor::NeighborApplicationIF*>  NeighborNodes;
      // implement NeighbordjacencyObserverIF
      virtual neighbor::NeighborApplicationIF const* do_getNeighbor(
        lmp::DWORD  neighborNodeId) const;
      virtual void do_neighborAdjacencyAdded(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc);
      virtual void do_neighborAdjacencyRemoved(
        lmp::DWORD              neighborNodeId,
        cc::IpccApplicationIF&  ipcc);
      // implement NodeApplicationIF
      virtual void do_enable();
      virtual void do_disable();
      virtual lmp::DWORD do_getNodeId() const;

      lmp::DWORD                  m_nodeId;
      NeighborNodes               m_neighborNodes;
    };
  } // namespace node
} // namespace lmp

#endif /* LIBS_Node_HPP_ */
