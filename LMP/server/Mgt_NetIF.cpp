#include <Mgt_NetIF.hpp>
#include <Mgt_IPCC.hpp>

#include <iostream>                     // for operator<<, etc

namespace lmp_netif
{

NetworkIF_i::NetworkIF_i(
  PortableServer::POA_ptr          poa,
  lmp_node::NodeApplProxy&         node,
  ::CORBA::Long                    localCCId,
  boost::asio::io_service&         io_service,
  boost::asio::ip::udp::endpoint&  listen_endpoint)
  : m_POA(PortableServer::POA::_duplicate(poa)),
    m_node(node),
    m_ipccAdjDiscoveredFtor(*this),
    m_msgHandler(m_node, m_ipccAdjDiscoveredFtor),
    m_networkIfSocket(io_service, localCCId, listen_endpoint, m_msgHandler),
    m_networkIfProxy(m_networkIfSocket)
{
  std::cout << "NetworkIF(localCCId = " << localCCId << ')' << std::endl;
}

NetworkIF_i::~NetworkIF_i()
{
}

::CORBA::Long NetworkIF_i::getLocalCCId()
{
  return m_networkIfSocket.getLocalCCId();
}

void NetworkIF_i::destroy()
{
  // TODO theNodePtr->deleteNetworkIF(m_localCCId);
  PortableServer::ObjectId *oid = m_POA->servant_to_id(this);
  m_POA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
}

void NetworkIF_i::enable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(localCCId = " << getLocalCCId() << ") enable" << std::endl;
  //theIPCCImpl.enable();
  // m_msgHandler.setNetworkIFObjRef(this->_this());
}

void NetworkIF_i::disable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").NetworkIF(localCCId = " << getLocalCCId() << ") disable" << std::endl;
  //theIPCCImpl.disable();
  // m_msgHandler.clearNetworkIFObjRef();
}


lmp_ipcc::IPCC_ptr NetworkIF_i::createIPCC(
  ::CORBA::Long   remoteAddress,
  ::CORBA::Short  remotePortNumber)
{
  boost::asio::ip::address_v4  ipv4(remoteAddress);
  boost::asio::ip::udp::endpoint remote_endpoint(ipv4, remotePortNumber);
  if (m_IPCCs.find(remote_endpoint) == m_IPCCs.end())
  {
    lmp::cc::IpccMsgReceiveIF* ipccPtr =
      m_msgHandler.createIpcc(remote_endpoint, m_networkIfProxy);
    if (ipccPtr)
    {
      lmp::cc::IpccApplicationIF* ipccApplPtr =
        dynamic_cast<lmp::cc::IpccApplicationIF*>(ipccPtr);
      if (ipccApplPtr)
      {
        lmp_ipcc::IPCC_i* servant =
          new lmp_ipcc::IPCC_i(m_POA, m_node, m_networkIfProxy, *ipccApplPtr);
        PortableServer::ObjectId *oid = m_POA->activate_object(servant);  delete oid;
        lmp_ipcc::IPCC_ptr ipcc = servant->_this();
        return m_IPCCs.insert(IPCCByRemoteEndPointMap::value_type(remote_endpoint, lmp_ipcc::IPCC::_duplicate(ipcc))).first->second;
      }
    }
  }
  throw lmp_node::Entity_Already_Exists();
}

lmp_ipcc::IPCC_ptr NetworkIF_i::getIPCC(
  ::CORBA::Long remoteAddress,
  ::CORBA::Short remotePortNumber)
{
  boost::asio::ip::address_v4  ipv4(remoteAddress);
  boost::asio::ip::udp::endpoint remote_endpoint(ipv4, remotePortNumber);
  IPCCByRemoteEndPointMap::const_iterator ipccIter = m_IPCCs.find(remote_endpoint);
  if (ipccIter != m_IPCCs.end())
  {
    return ipccIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void NetworkIF_i::deleteIPCC(
  ::CORBA::Long remoteAddress,
  ::CORBA::Short remotePortNumber)
{
  boost::asio::ip::address_v4  ipv4(remoteAddress);
  boost::asio::ip::udp::endpoint remote_endpoint(ipv4, remotePortNumber);
  IPCCByRemoteEndPointMap::iterator ipccIter = m_IPCCs.find(remote_endpoint);
  if (ipccIter != m_IPCCs.end())
  {
    m_IPCCs.erase(ipccIter);
  }
  throw lmp_node::No_Such_Entity();
}

void NetworkIF_i::registerIPCCAdjacencyObserver(
  ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").registerIPCCAdjacencyObserver()" << std::endl;
  m_ipccAdjacencyObservers.insert(lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver::_duplicate(observer));
}

void NetworkIF_i::deregisterIPCCAdjacencyObserver(
  ::lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId()
            << ").deregisterIPCCAdjacencyObserver()" << std::endl;
  m_ipccAdjacencyObservers.erase(lmp_ipcc_adjacency_observer::IPCCAdjacencyObserver::_duplicate(observer));
}

NetworkIF_i::IPCCAdjDiscoveredFtor::IPCCAdjDiscoveredFtor(
  NetworkIF_i&  networkIF)
: m_networkIF(networkIF)
{
}

void NetworkIF_i::IPCCAdjDiscoveredFtor::do_process(
  const boost::asio::ip::udp::endpoint&  sender_endpointl)
{
  if (sender_endpointl.address().is_v4())
  {
    m_networkIF.createIPCC(sender_endpointl.address().to_v4().to_ulong(),
                           sender_endpointl.port());
  }
}


} // end namespace lmp_netif
