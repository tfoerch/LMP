#include <Mgt_IPCC.hpp>
#include <IPCCObserverProxy.hpp>

#include <iostream>                     // for operator<<, etc

namespace lmp_ipcc
{

IPCC_i::IPCC_i(
  PortableServer::POA_ptr     poa,
  lmp_node::NodeApplProxy&    node,
  lmp_netif::NetworkIFProxy&  metworkIf,
  lmp::cc::IpccApplicationIF&  ipcc)
  : thePOA(PortableServer::POA::_duplicate(poa)),
    m_node(node),
    m_metworkIf(metworkIf),
    m_ipcc(ipcc)
{
  std::cout << "IPCC(localCCId = " << m_metworkIf.getLocalCCId()
//	   << ", localAddress = " << localAddress
//	   << ", localPortNumber = " << localPortNumber
	   << ')' << std::endl;
}

IPCC_i::~IPCC_i()
{
}

void IPCC_i::destroy()
{
  // TODO theNodePtr->deleteIPCC(theLocalCCId);
  PortableServer::ObjectId *oid=thePOA->servant_to_id(this);
  thePOA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
}

void IPCC_i::enable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_metworkIf.getLocalCCId() << ") enable" << std::endl;
  m_ipcc.enable();
}

void IPCC_i::disable()
{
  std::cout << "Node(" << m_node.getNodeId() << ").IPCC(localCCId = " << m_metworkIf.getLocalCCId() << ") disable" << std::endl;
  m_ipcc.disable();
}

void IPCC_i::registerObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
  // std::cout << "registerObserver" << std::endl;
  //lmp::cc::appl::IpccObserverProxy  observerProxy(theIPCCImpl, observer);
  //theIPCCImpl.registerObserver(observerProxy);
  // std::cout << "registerObserver finished" << std::endl;
}

void IPCC_i::deregisterObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
  //lmp::cc::appl::IpccObserverProxy  observerProxy(theIPCCImpl, observer);
  //theIPCCImpl.deregisterObserver(observerProxy);
}

} // end namespace lmp_ipcc
