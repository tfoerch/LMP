#ifndef LIBS_IPCC_APPLICATIONIF_HPP_
#define LIBS_IPCC_APPLICATIONIF_HPP_
/*
 * IPCCApplicationIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"             // for DWORD
#include <iostream>

namespace lmp
{
  namespace neighbor
  {
    class NeighborAdjacencyObserverIF;
  }
  namespace cc
  {
    namespace appl
    {
      class IpccObserverProxyIF;
    }
    class IpccApplicationIF
    {
    public:
      inline void enable()
      { do_enable(); }
      inline void disable()
      { do_disable(); }
      inline lmp::DWORD getLocalNodeId() const
      { return do_getLocalNodeId(); }
      inline lmp::DWORD getRemoteNodeId() const
      { return do_getRemoteNodeId(); }
      inline lmp::DWORD getLocalCCId() const
      { return do_getLocalCCId(); }
      inline lmp::DWORD getRemoteCCId() const
      { return do_getRemoteCCId(); }
      inline void registerObserver(
        appl::IpccObserverProxyIF&  observer)
      { do_registerObserver(observer); }
      inline void deregisterObserver(
        appl::IpccObserverProxyIF&  observer)
      { do_deregisterObserver(observer); }
      inline void registerObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer)
      { do_registerObserver(observer); }
      inline void deregisterObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer)
      { do_deregisterObserver(observer); }
      virtual ~IpccApplicationIF(){}
    private:
      virtual void do_enable() = 0;
      virtual void do_disable() = 0;
      virtual lmp::DWORD do_getLocalNodeId() const = 0;
      virtual lmp::DWORD do_getRemoteNodeId() const = 0;
      virtual lmp::DWORD do_getLocalCCId() const = 0;
      virtual lmp::DWORD do_getRemoteCCId() const = 0;
      virtual void do_registerObserver(
        appl::IpccObserverProxyIF&  observer) = 0;
      virtual void do_deregisterObserver(
        appl::IpccObserverProxyIF&  observer) = 0;
      virtual void do_registerObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer) = 0;
      virtual void do_deregisterObserver(
        neighbor::NeighborAdjacencyObserverIF&  observer) = 0;
    };
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_APPLICATIONIF_HPP_ */
