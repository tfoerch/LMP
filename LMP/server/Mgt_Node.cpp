#include <Mgt_Node.hpp>
#include <Mgt_Neighbor.hpp>
#include <Mgt_NetIF.hpp>
#include "lmp_mgtif_node.hpp"           // for No_Such_Entity, etc
#include "lmp_mgtif_node_registry.hpp"  // for NodeRegistry_var, etc
#include <iostream>

namespace lmp_node
{

Node_i::Node_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa,
  ::CORBA::Long            nodeId,
  ::lmp_node_registry::NodeRegistry_ptr  aNodeRegistry)
: theORB(CORBA::ORB::_duplicate(orb)),
  m_POA(PortableServer::POA::_duplicate(poa)),
  m_node(nodeId),
  theNodeRegistry(::lmp_node_registry::NodeRegistry::_duplicate(aNodeRegistry)),
  m_netIFByLocalCCI(),
  m_neighborAdjacencyObserver(),
  theNeighborByNodeIdMap(),
  m_neighborAdjAddedFtor(m_neighborAdjacencyObserver),
  m_neighborAdjRemovedFtor(m_neighborAdjacencyObserver),
  m_nodeProxy(m_node,
              m_neighborAdjAddedFtor,
              m_neighborAdjRemovedFtor)
{
//  std::cout << "ctor activate object" << std::endl;
//  PortableServer::ObjectId_var myNodeId = m_POA->activate_object(this);
//  std::cout << "ctor object activated" << std::endl;
  //this->_remove_ref();
  //PortableServer::ObjectId *oid=m_POA->activate_object(this); delete oid;
}

Node_i::~Node_i()
{
  CORBA::release(m_POA);
  CORBA::release(theORB);
}

::CORBA::Long Node_i::getNodeId()
{
  return m_node.getNodeId();
}

lmp_netif::NetworkIF_ptr Node_i::createNetIF(
  ::CORBA::Long localCCId,
  ::CORBA::Long localAddress,
  ::CORBA::Short localPortNumber)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").createNetIF(localCCId = "
            << localCCId << ")" << std::endl;
  if (m_netIFByLocalCCI.find(localCCId) == m_netIFByLocalCCI.end())
  {
    boost::asio::ip::address_v4  ipv4(localAddress);
    boost::asio::ip::udp::endpoint local_endpoint(ipv4, localPortNumber);
    lmp_netif::NetworkIF_i* servant =
      new lmp_netif::NetworkIF_i(m_POA, m_nodeProxy, localCCId, m_io_service, local_endpoint);
    PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
    lmp_netif::NetworkIF_ptr netif = servant->_this();
    return m_netIFByLocalCCI.insert(NetIFByLocalCCIdMap::value_type(localCCId, lmp_netif::NetworkIF::_duplicate(netif))).first->second;
  }
  throw lmp_node::Entity_Already_Exists();

}

lmp_netif::NetworkIF_ptr Node_i::getNetIF(
  ::CORBA::Long localCCId)
{
  NetIFByLocalCCIdMap::const_iterator netIfIter = m_netIFByLocalCCI.find(localCCId);
  if (netIfIter != m_netIFByLocalCCI.end())
  {
    return netIfIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::deleteNetIF(
 ::CORBA::Long localCCId)
{
  NetIFByLocalCCIdMap::iterator netIfIter = m_netIFByLocalCCI.find(localCCId);
  if (netIfIter != m_netIFByLocalCCI.end())
  {
    m_netIFByLocalCCI.erase(netIfIter);
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::registerNeighborAdjacencyObserver(
  ::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").registerNeighborAdjacencyObserver()" << std::endl;
  m_neighborAdjacencyObserver.insert(lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver::_duplicate(observer));
}

void Node_i::deregisterNeighborAdjacencyObserver(
  ::lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").deregisterNeighborAdjacencyObserver()" << std::endl;
  m_neighborAdjacencyObserver.erase(lmp_neighbor_adjacency_observer::NeighborAdjacencyObserver::_duplicate(observer));
}

lmp_neighbor::Neighbor_ptr Node_i::createNeighbor(
  ::CORBA::Long remoteNodeId)
{
  if (theNeighborByNodeIdMap.find(remoteNodeId) == theNeighborByNodeIdMap.end())
  {
    lmp_neighbor::Neighbor_i* servant = new lmp_neighbor::Neighbor_i(m_POA, this->_this(), remoteNodeId);
    PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
    lmp_neighbor::Neighbor_ptr neighbor = servant->_this();
    return theNeighborByNodeIdMap.insert(NeighborByNodeIdMap::value_type(remoteNodeId, lmp_neighbor::Neighbor::_duplicate(neighbor))).first->second;
  }
  throw lmp_node::Entity_Already_Exists();
}

lmp_neighbor::Neighbor_ptr Node_i::getNeighbor(
  ::CORBA::Long remoteNodeId)
{
  NeighborByNodeIdMap::const_iterator neighborIter = theNeighborByNodeIdMap.find(remoteNodeId);
  if (neighborIter != theNeighborByNodeIdMap.end())
  {
    return neighborIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::deleteNeighbor(
 ::CORBA::Long remoteNodeId)
{
  NeighborByNodeIdMap::iterator neighborIter = theNeighborByNodeIdMap.find(remoteNodeId);
  if (neighborIter != theNeighborByNodeIdMap.end())
  {
    theNeighborByNodeIdMap.erase(neighborIter);
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::destroy()
{
  if (!CORBA::is_nil(theNodeRegistry))
  {
    theNodeRegistry->deregisterNode(this->_this());
  }
  PortableServer::ObjectId *oid = m_POA->servant_to_id(this);
  std::cout << "before deactivate_object" << std::endl;
  m_POA->deactivate_object(*oid);  delete oid;
  std::cout << "after deactivate_object" << std::endl;
  // _remove_ref(); // delete this;
  // std::cout << "after _remove_ref" << std::endl;
  // Shutdown the ORB (but do not wait for completion).  This also
  // causes the main thread to unblock from CORBA::ORB::run().
  theORB->shutdown(0);
}

Node_i::NeighborAdjAddedFtor::NeighborAdjAddedFtor(
  NeighborAdjacencyObserverContainer&  observers)
: m_observers(observers)
{
}

void Node_i::NeighborAdjAddedFtor::do_process(
  lmp::DWORD                   neighborNodeId,
  lmp::cc::IpccApplicationIF&  ipcc)
{
}

Node_i::NeighborAdjRemovedFtor::NeighborAdjRemovedFtor(
  NeighborAdjacencyObserverContainer&  observers)
: m_observers(observers)
{
}

void Node_i::NeighborAdjRemovedFtor::do_process(
  lmp::DWORD                   neighborNodeId,
  lmp::cc::IpccApplicationIF&  ipcc)
{
}



} // end namespace lmp_node
