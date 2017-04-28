#include <lmp_mgtif_node.hpp>
#include <lmp_mgtif_node_registry.hpp>
#include "lmp_mgtif_netif.hpp"               // for NetworkIF_var, IPCC_ptr
#include "lmp_mgtif_neighbor.hpp"            // for Neighbor_var, etc
#include "lmp_mgtif_neighbor_adjacency_observer.hpp"      // for Neighbor_var, etc
#include <Mgt_NeighborAdjacencyChangeFtorIF.hpp>
#include <Mgt_NodeApplProxy.hpp>

#include "node/Node.hpp"

#include <omniORB4/CORBA.h>                  // for ORB_ptr
#include <omniORB4/poa.h>                    // for POA_ptr

#include <boost/asio/io_service.hpp>

#include <map>
#include <set>

namespace lmp_node
{

class Node_i : public POA_lmp_node::Node
{
public:
  Node_i(
    CORBA::ORB_ptr                         orb,
    PortableServer::POA_ptr                poa,
    ::CORBA::Long                          nodeId,
    ::lmp_node_registry::NodeRegistry_ptr  aNodeRegistry);
  virtual ~Node_i();
  virtual ::CORBA::Long getNodeId();
  virtual lmp_netif::NetworkIF_ptr createNetIF(
    ::CORBA::Long localCCId,
    ::CORBA::Long localAddress,
    ::CORBA::Short localPortNumber);
  virtual lmp_netif::NetworkIF_ptr getNetIF(
    ::CORBA::Long localCCId);
  virtual void deleteNetIF(
   ::CORBA::Long localCCId);
  virtual void registerNeighborAdjacencyObserver(
    ::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr observer);
  virtual void deregisterNeighborAdjacencyObserver(
    ::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr observer);
  virtual ::lmp_neighbor::Neighbor_ptr createNeighbor(
    ::CORBA::Long remoteNodeId);
  virtual ::lmp_neighbor::Neighbor_ptr getNeighbor(
    ::CORBA::Long remoteNodeId);
  virtual void deleteNeighbor(
    ::CORBA::Long remoteNodeId);
  virtual void destroy();
private:
  typedef  std::map<CORBA::Long, ::lmp_netif::NetworkIF_var>    NetIFByLocalCCIdMap;
  typedef  std::set<::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_var>   NeighborAdjacencyObserverContainer;
  typedef  std::map<CORBA::Long, ::lmp_neighbor::Neighbor_var>  NeighborByNodeIdMap;

  class NeighborAdjAddedFtor : public NeighborAdjacencyChangeFtorIF
  {
  public:
    NeighborAdjAddedFtor(
      NeighborAdjacencyObserverContainer&  observers);
  private:
    virtual void do_process(
      lmp::DWORD                   neighborNodeId,
      lmp::cc::IpccApplicationIF&  ipcc);
    NeighborAdjacencyObserverContainer&  m_observers;
  };
  class NeighborAdjRemovedFtor : public NeighborAdjacencyChangeFtorIF
  {
  public:
    NeighborAdjRemovedFtor(
      NeighborAdjacencyObserverContainer&  observers);
  private:
    virtual void do_process(
      lmp::DWORD                   neighborNodeId,
      lmp::cc::IpccApplicationIF&  ipcc);
    NeighborAdjacencyObserverContainer&  m_observers;
  };

  CORBA::ORB_ptr                         theORB;
  PortableServer::POA_ptr                m_POA;
  boost::asio::io_service                m_io_service;
  lmp::node::Node                        m_node;
  ::lmp_node_registry::NodeRegistry_var  theNodeRegistry;
  NetIFByLocalCCIdMap                    m_netIFByLocalCCI;
  NeighborAdjacencyObserverContainer     m_neighborAdjacencyObserver;
  NeighborByNodeIdMap                    theNeighborByNodeIdMap;
  NeighborAdjAddedFtor                   m_neighborAdjAddedFtor;
  NeighborAdjRemovedFtor                 m_neighborAdjRemovedFtor;
  NodeApplProxy                          m_nodeProxy;
};

} // end namespace LMP
