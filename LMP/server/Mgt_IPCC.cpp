#include <Mgt_IPCC.hpp>
#include <IPCCObserverProxy.hpp>
#include <Mgt_IPCCInDestructionFtorIF.hpp>

#include <iostream>                     // for operator<<, etc

namespace lmp_ipcc
{

IPCC_i::IPCC_i(
  PortableServer::POA_ptr              poa,
  lmp_node::NodeApplProxy&             node,
  lmp_netif::NetworkIFProxy&           networkIf,
  lmp::cc::IpccApplicationIF&          ipcc,
  lmp_netif::IPCCInDestructionFtorIF&  ipccInDestructionFtor)
  : thePOA(PortableServer::POA::_duplicate(poa)),
    m_node(node),
    m_networkIf(networkIf),
    m_ipcc(ipcc),
    m_ipccObservers(),
    m_ipccObserverProxy(m_ipcc,
                        m_ipccObservers),
    m_ipccInDestructionFtor(ipccInDestructionFtor)
{
  std::cout << "IPCC(localCCId = " << m_networkIf.getLocalCCId()
//	   << ", localAddress = " << localAddress
//	   << ", localPortNumber = " << localPortNumber
	   << ')' << std::endl;
  m_ipcc.registerObserver(m_ipccObserverProxy);
}

IPCC_i::~IPCC_i()
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIf.getLocalCCId() << ") destructor" << std::endl;
  m_ipcc.deregisterObserver(m_ipccObserverProxy);
}

::CORBA::Long IPCC_i::getLocalCCId()
{
  return m_ipcc.getLocalCCId();
}

::CORBA::Long IPCC_i::getRemoteAddress()
{
  return m_ipcc.getRemoteEndpoint().address().to_v4().to_ulong();
}

::CORBA::Short IPCC_i::getRemotePortNumber()
{
  return m_ipcc.getRemoteEndpoint().port();
}

void IPCC_i::destroy()
{
  m_ipccInDestructionFtor(getRemoteAddress(), getRemotePortNumber());
  // TODO theNodePtr->deleteIPCC(theLocalCCId);
  PortableServer::ObjectId *oid=thePOA->servant_to_id(this);
  thePOA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
}

void IPCC_i::enable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIf.getLocalCCId()
            << ", remoteAddress = " << getRemoteAddress()
            << ", remotePortNumber = " << getRemotePortNumber() << ") enable" << std::endl;
  m_ipcc.enable();
}

void IPCC_i::disable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIf.getLocalCCId() << ") disable" << std::endl;
  m_ipcc.disable();
}

void IPCC_i::registerObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIf.getLocalCCId() << ").registerObserver()" << std::endl;
  m_ipccObservers.insert(lmp_ipcc_observer::IPCCObserver::_duplicate(observer));
}

void IPCC_i::deregisterObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_networkIf.getLocalCCId() << ").deregisterObserver()" << std::endl;
  m_ipccObservers.erase(lmp_ipcc_observer::IPCCObserver::_duplicate(observer));
}

} // end namespace lmp_ipcc
