/*
 * Neighbor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Neighbor.hpp"

namespace lmp
{
  namespace neighbor
  {
    Neighbor::Neighbor(
      lmp::DWORD                       nodeId)
      : m_nodeId(nodeId)
    {
    }
    void Neighbor::do_enable()
    {
    }
    void Neighbor::do_disable()
    {
    }
    lmp::DWORD Neighbor::do_getNodeId() const
    {
      return m_nodeId;
    }
    void Neighbor::do_ipccAdjacencyAdded(
      cc::IpccApplicationIF&   ipcc)
    {
    }
    void Neighbor::do_ipccAdjacencyRemoved(
      cc::IpccApplicationIF&   ipcc)
    {
    }
  } // namespace neighbor
} // namespace lmp
