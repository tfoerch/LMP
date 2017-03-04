/*
 * Node.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Node.hpp"
#include "neighbor/Neighbor.hpp"

namespace lmp
{
  namespace node
  {
    Node::Node(
      lmp::DWORD                       nodeId)
      : m_nodeId(nodeId)
    {
    }
    void Node::enable()
    {
    }
    void Node::disable()
    {
    }
    neighbor::NeighborApplicationIF const* Node::do_getNeighbor(
      lmp::DWORD  neighborNodeId) const
    {
      NeighborNodes::const_iterator iter = m_neighborNodes.find(neighborNodeId);
      return
        ( iter != m_neighborNodes.end() ?
          iter->second :
          0 );
    }
    neighbor::NeighborApplicationIF const*  Node::do_neighborAdjacencyAdded(
      lmp::DWORD              neighborNodeId,
      cc::IpccApplicationIF&  ipcc)
    {
      std::cout << "Node::do_neighborAdjacencyAdded(" << neighborNodeId << ")" << std::endl;
      NeighborNodes::iterator iter = m_neighborNodes.find(neighborNodeId);
      if (iter == m_neighborNodes.end())
      {
        neighbor::NeighborApplicationIF* neighborPtr = new neighbor::Neighbor(neighborNodeId);
        iter =
          m_neighborNodes.insert(NeighborNodes::value_type(neighborNodeId,
                                                           neighborPtr)).first;
      }
      neighbor::NeighborApplicationIF* neighborPtr =
        ( iter != m_neighborNodes.end() ?
          iter->second :
          0 );
      if (neighborPtr)
      {
        cc::IpccAdjacencyObserverIF* ipccAdjObservPtr =
          dynamic_cast<cc::IpccAdjacencyObserverIF*>(neighborPtr);
        if (ipccAdjObservPtr)
        {
          ipccAdjObservPtr->ipccAdjacencyAdded(ipcc);
        }
      }
      return neighborPtr;
    }
    bool Node::do_neighborAdjacencyRemoved(
      lmp::DWORD              neighborNodeId,
      cc::IpccApplicationIF&  ipcc)
    {
      return false;
    }
  } // namespace node
} // namespace lmp
