#include <Mgt_IPCC.hpp>
#include <IPCCObserverProxy.hpp>

#include <iostream>                     // for operator<<, etc

namespace lmp_ipcc
{

IPCC_i::IPCC_i(
  PortableServer::POA_ptr  poa,
  lmp_node::Node_ptr       nodePtr,
  ::CORBA::Long            localCCId,
  ::CORBA::Long            localAddress,
  ::CORBA::Short           localPortNumber)
  : thePOA(PortableServer::POA::_duplicate(poa)),
    theNodePtr(lmp_node::Node::_duplicate(nodePtr)),
    theLocalCCId(localCCId),
    theLocalAddress(localAddress),
    theLocalPortNumber(localPortNumber)//,
    //theIPCCImpl(theNodePtr->getNodeId(), theLocalCCId, true)
{
  std::cout << "IPCC(localCCId = " << localCCId
	   << ", localAddress = " << localAddress
	   << ", localPortNumber = " << localPortNumber << ')' << std::endl;
}

IPCC_i::~IPCC_i()
{
}

void IPCC_i::destroy()
{
  theNodePtr->deleteIPCC(theLocalCCId);
  PortableServer::ObjectId *oid=thePOA->servant_to_id(this);
  thePOA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
}

void IPCC_i::enable()
{
  std::cout << "Node(" << theNodePtr->getNodeId() << ").IPCC(localCCId = " << theLocalCCId << ") enable" << std::endl;
  //theIPCCImpl.enable();
}

void IPCC_i::disable()
{
  std::cout << "Node(" << theNodePtr->getNodeId() << ").IPCC(localCCId = " << theLocalCCId << ") disable" << std::endl;
  //theIPCCImpl.disable();
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
