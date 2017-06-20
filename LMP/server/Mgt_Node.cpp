#include <Mgt_Node.hpp>
#include <Mgt_Neighbor.hpp>
#include <Mgt_NetworkIF.hpp>
#include "lmp_mgtif_node.hpp"           // for No_Such_Entity, etc
#include "lmp_mgtif_node_registry.hpp"  // for NodeRegistry_var, etc

#include <boost/bind.hpp>
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
  m_io_service(),
  m_work(m_io_service),
  m_threadPool(),
  m_node(nodeId),
  theNodeRegistry(::lmp_node_registry::NodeRegistry::_duplicate(aNodeRegistry)),
  m_netIFByLocalCCI(),
  m_neighborAdjacencyObserver(),
  theNeighborByNodeIdMap(),
  m_neighborAdjAddedFtor(m_neighborAdjacencyObserver),
  m_neighborAdjRemovedFtor(m_neighborAdjacencyObserver),
  m_networkIFInDestructionFtor(*this),
  m_nodeProxy(m_node,
              m_neighborAdjAddedFtor,
              m_neighborAdjRemovedFtor)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ") ctor " << std::endl;
//  std::cout << "ctor activate object" << std::endl;
//  PortableServer::ObjectId_var myNodeId = m_POA->activate_object(this);
//  std::cout << "ctor object activated" << std::endl;
  //this->_remove_ref();
  //PortableServer::ObjectId *oid=m_POA->activate_object(this); delete oid;

  for(size_t t = 0;
      t < 1; // std::thread::hardware_concurrency();
      ++t)
  {
    m_threadPool.push_back(std::thread(boost::bind(&boost::asio::io_service::run,
                                                   &m_io_service)));
  }

}

Node_i::~Node_i()
{
  std::cout << "Node(" << m_node.getNodeId()
            << ") dtor " << std::endl;
  CORBA::release(m_POA);
  CORBA::release(theORB);
}

::CORBA::Long Node_i::getNodeId()
{
  return m_node.getNodeId();
}

lmp_netif::NetworkIF_ptr Node_i::createNetworkIF(
  ::CORBA::Long   localCCId,
  const char*     interfaceName,
  ::CORBA::Short  localPortNumber)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").createNetworkIF(localCCId = "
            << localCCId << ")" << std::endl;
  if (m_netIFByLocalCCI.find(localCCId) == m_netIFByLocalCCI.end())
  {
    std::string  ifName(interfaceName);
    lmp_netif::NetworkIF_i* servant =
      new lmp_netif::NetworkIF_i(m_POA, m_nodeProxy, m_io_service, localCCId, ifName, localPortNumber, m_networkIFInDestructionFtor);
    PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
    lmp_netif::NetworkIF_ptr netif = servant->_this();
    return m_netIFByLocalCCI.insert(NetworkIFByLocalCCIdMap::value_type(localCCId, lmp_netif::NetworkIF::_duplicate(netif))).first->second;
  }
  throw lmp_node::Entity_Already_Exists();

}

lmp_netif::NetworkIF_ptr Node_i::getNetworkIF(
  ::CORBA::Long localCCId)
{
  NetworkIFByLocalCCIdMap::const_iterator netIfIter = m_netIFByLocalCCI.find(localCCId);
  if (netIfIter != m_netIFByLocalCCI.end())
  {
    return netIfIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::deleteNetworkIF(
 ::CORBA::Long localCCId)
{
  NetworkIFByLocalCCIdMap::iterator netIfIter = m_netIFByLocalCCI.find(localCCId);
  if (netIfIter != m_netIFByLocalCCI.end())
  {
    m_netIFByLocalCCI.erase(netIfIter);
    return;
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
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy before stop" << std::endl;
  m_io_service.stop();
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy after stop" << std::endl;
  for(std::thread& t : m_threadPool)
  {
    t.join();
  }

  if (!CORBA::is_nil(theNodeRegistry))
  {
    theNodeRegistry->deregisterNode(this->_this());
  }
  PortableServer::ObjectId *oid = m_POA->servant_to_id(this);
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy before deactivate_object" << std::endl;
  m_POA->deactivate_object(*oid);  delete oid;
  std::cout << "Node(" << m_node.getNodeId()
            << ") destroy before after deactivate_object" << std::endl;
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

Node_i::NetworkIFInDestructionFtor::NetworkIFInDestructionFtor(
  Node_i&  node)
: m_node(node)
{
}

void Node_i::NetworkIFInDestructionFtor::do_process(
  lmp::DWORD                   localCCId)
{
  try
  {
    m_node.deleteNetworkIF(localCCId);
  }
  catch(lmp_node::No_Such_Entity& nsE)
  {
  }
}


} // end namespace lmp_node
