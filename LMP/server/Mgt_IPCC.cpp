#include <Mgt_IPCC.hpp>
#include <IPCCObserverProxy.hpp>

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
    theLocalPortNumber(localPortNumber),
	theIPCCImpl(theNodePtr->getNodeId(), theLocalCCId, true)
{
  cout << "IPCC(localCCId = " << localCCId
	   << ", localAddress = " << localAddress
	   << ", localPortNumber = " << localPortNumber << ')' << endl;
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
  cout << "Node(" << theNodePtr->getNodeId() << ").IPCC(localCCId = " << theLocalCCId << ") enable" << endl;
  theIPCCImpl.enable();
}

void IPCC_i::disable()
{
}

void IPCC_i::registerObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
  // cout << "registerObserver" << endl;
  lmp::cc::appl::IpccObserverProxy  observerProxy(theIPCCImpl, observer);
  theIPCCImpl.registerObserver(observerProxy);
  // cout << "registerObserver finished" << endl;
}

void IPCC_i::deregisterObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
  lmp::cc::appl::IpccObserverProxy  observerProxy(theIPCCImpl, observer);
  theIPCCImpl.deregisterObserver(observerProxy);
}

} // end namespace lmp_ipcc
