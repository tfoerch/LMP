/*
 * Neighbor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Neighbor.hpp"
#include "cc/IPCCApplicationIF.hpp"
#include "cc/IPCC_State.hpp"
#include "cc/IPCC_Event.hpp"
#include "cc/IPCC_Action.hpp"
#include <typeinfo>             // for bad_cast

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
      std::cout << "Neighbor[" << m_nodeId << "].ipccAdjacencyAdded("
                << ipcc.getLocalCCId() << ")" << std::endl;
      NeighborIpccObserveProxy  observerProxy(*this);
      ipcc.registerObserver(observerProxy);
    }
    void Neighbor::do_ipccAdjacencyRemoved(
      cc::IpccApplicationIF&   ipcc)
    {
      std::cout << "Neighbor[" << m_nodeId << "].ipccAdjacencyRemoved("
                << ipcc.getLocalCCId() << ")" << std::endl;
      NeighborIpccObserveProxy  observerProxy(*this);
      ipcc.deregisterObserver(observerProxy);
    }
    void Neighbor::do_notifyTransition(
      const cc::IpccApplicationIF&  ipcc,
      const cc::appl::State&        sourceState,
      const cc::appl::Event&        event,
      const cc::appl::State&        targetState,
      const cc::appl::Action&       action)
    {
      std::cout << "Neighbor[" << m_nodeId << "].IPCC[" << ipcc.getLocalCCId() << "]."
                << event << ": " << sourceState << " -> " << targetState
                << " executing " << action << std::endl;

    }
    Neighbor::NeighborIpccObserveProxy::NeighborIpccObserveProxy(
      cc::appl::IpccObserverIF&  ipccbserver)
    : m_ipccbserver(ipccbserver)
    {
    }
    void Neighbor::NeighborIpccObserveProxy::do_notifyTransition(
      const cc::IpccApplicationIF&  ipcc,
      const cc::appl::State&        sourceState,
      const cc::appl::Event&        event,
      const cc::appl::State&        targetState,
      const cc::appl::Action&       action)
    {
      m_ipccbserver.notifyTransition(ipcc, sourceState, event, targetState, action);
    }
    bool Neighbor::NeighborIpccObserveProxy::is_equal(
      const IpccObserverProxyIF& other) const
    {
      try
      {
        const NeighborIpccObserveProxy&  otherProxy = dynamic_cast<const NeighborIpccObserveProxy&>(other);
        return (&m_ipccbserver == &otherProxy.m_ipccbserver);
      }
      catch  (std::bad_cast&)
      {
        return false;
      }
    }
    cc::appl::IpccObserverProxyIF* Neighbor::NeighborIpccObserveProxy::do_clone() const
    {
      return new NeighborIpccObserveProxy(*this);
    }
  } // namespace neighbor
} // namespace lmp
