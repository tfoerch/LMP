/*
 * Node.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Node.hpp"
#include "neighbor/Neighbor.hpp"

#include <iostream>

namespace lmp
{
  namespace node
  {
    Node::Node(
      lmp::DWORD                       nodeId)
      : m_nodeId(nodeId)
    {
    }
    void Node::do_enable()
    {
    }
    void Node::do_disable()
    {
    }
    lmp::DWORD Node::do_getNodeId() const
    {
      return m_nodeId;
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
    neighbor::NeighborApplicationIF* Node::do_accessNeighbor(
      lmp::DWORD  neighborNodeId)
    {
      NeighborNodes::iterator iter = m_neighborNodes.find(neighborNodeId);
      return
        ( iter != m_neighborNodes.end() ?
          iter->second :
          0 );
    }
    neighbor::NeighborApplicationIF* Node::do_createNeighbor(
      lmp::DWORD              neighborNodeId)
    {
      std::cout << "Node[" << m_nodeId << "].createNeighbor(" << neighborNodeId << ")" << std::endl;
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
      return neighborPtr;
    }
    bool Node::do_removeNeighbor(
      lmp::DWORD              neighborNodeId)
    {
      std::cout << "Node[" << m_nodeId << "].removeNeighbor(" << neighborNodeId << ")" << std::endl;
      NeighborNodes::iterator iter = m_neighborNodes.find(neighborNodeId);
      if (iter != m_neighborNodes.end())
      {
        if (iter->second)
        {
          delete iter->second;
        }
        m_neighborNodes.erase(iter);
        return true;
      }
      return false;
    }
    void Node::do_neighborAdjacencyAdded(
      lmp::DWORD              neighborNodeId,
      cc::IpccApplicationIF&  ipcc)
    {
      std::cout << "Node::do_neighborAdjacencyAdded(" << neighborNodeId << ")" << std::endl;
      neighbor::NeighborApplicationIF* neighborPtr = createNeighbor(neighborNodeId);
      if (neighborPtr)
      {
        cc::IpccAdjacencyObserverIF* ipccAdjObservPtr =
          dynamic_cast<cc::IpccAdjacencyObserverIF*>(neighborPtr);
        if (ipccAdjObservPtr)
        {
          ipccAdjObservPtr->ipccAdjacencyAdded(ipcc);
        }
        else
        {
          std::cout << "Node::do_neighborAdjacencyAdded() dynamic_cast failed" << std::endl;
        }
      }
    }
    void Node::do_neighborAdjacencyRemoved(
      lmp::DWORD              neighborNodeId,
      cc::IpccApplicationIF&  ipcc)
    {
      std::cout << "Node::do_neighborAdjacencyRemoved(" << neighborNodeId << ")" << std::endl;
      neighbor::NeighborApplicationIF* neighborPtr = accessNeighbor(neighborNodeId);
      if (neighborPtr)
      {
        cc::IpccAdjacencyObserverIF* ipccAdjObservPtr =
          dynamic_cast<cc::IpccAdjacencyObserverIF*>(neighborPtr);
        if (ipccAdjObservPtr)
        {
          ipccAdjObservPtr->ipccAdjacencyRemoved(ipcc);
        }
        else
        {
          std::cout << "Node::do_neighborAdjacencyRemoved() dynamic_cast failed" << std::endl;
        }
      }
      NeighborNodes::iterator iter = m_neighborNodes.find(neighborNodeId);
      if (iter != m_neighborNodes.end())
      {
        if (iter->second)
        {
          delete iter->second;
        }
        m_neighborNodes.erase(iter);
      }
    }
  } // namespace node
} // namespace lmp
