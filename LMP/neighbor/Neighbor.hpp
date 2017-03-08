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
#include "cc/IPCC_ObserverIF.hpp"

namespace lmp
{
  namespace neighbor
  {
    class Neighbor : public NeighborApplicationIF,
                     public cc::IpccAdjacencyObserverIF,
                     public cc::appl::IpccObserverIF
    {
    public:
      Neighbor(
        lmp::DWORD                       nodeId);
      virtual ~Neighbor(){}
    private:
      class NeighborIpccObserveProxy : public cc::appl::IpccObserverProxyIF
      {
      public:
        NeighborIpccObserveProxy(
          cc::appl::IpccObserverIF&  ipccbserver);
        virtual ~NeighborIpccObserveProxy(){}
      private:
        virtual void do_notifyTransition(
          const cc::IpccApplicationIF&  ipcc,
          const cc::appl::State&        sourceState,
          const cc::appl::Event&        event,
          const cc::appl::State&        targetState,
          const cc::appl::Action&       action);
        virtual bool is_equal(
          const IpccObserverProxyIF& other) const;
        virtual IpccObserverProxyIF* do_clone() const;
        cc::appl::IpccObserverIF&  m_ipccbserver;
      };
      // implement NeighborApplicationIF
      virtual void do_enable();
      virtual void do_disable();
      virtual lmp::DWORD do_getNodeId() const;
      // implement IpccAdjacencyObserverIF
      virtual void do_ipccAdjacencyAdded(
        cc::IpccApplicationIF&   ipcc);
      virtual void do_ipccAdjacencyRemoved(
        cc::IpccApplicationIF&   ipcc);
      // implement IpccObserverIF
      virtual void do_notifyTransition(
        const cc::IpccApplicationIF&  ipcc,
        const cc::appl::State&        sourceState,
        const cc::appl::Event&        event,
        const cc::appl::State&        targetState,
        const cc::appl::Action&       action);
      lmp::DWORD                    m_nodeId;
    };
  } // namespace neighbor
} // namespace lmp

#endif /* LIBS_Neighbor_HPP_ */
