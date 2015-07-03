#include <Mgt_IPCC.hpp>

namespace lmp_ipcc
{

IPCC_i::IPCC_i(
  PortableServer::POA_ptr  poa,
  lmp_node::Node_ptr       nodePtr,
  ::CORBA::Long            localCCId,
  ::CORBA::Long            localAddress,
  ::CORBA::Short           localPortNumber)
  : thePOA(PortableServer::POA::_duplicate(poa)),
    theNodePtr(nodePtr),
    theLocalCCId(localCCId),
    theLocalAddress(localAddress),
    theLocalPortNumber(localPortNumber)
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
}

void IPCC_i::disable()
{
}

void IPCC_i::registerObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
}

void IPCC_i::deregisterObserver(
  ::lmp_ipcc_observer::IPCCObserver_ptr observer)
{
}

} // end namespace lmp_ipcc
