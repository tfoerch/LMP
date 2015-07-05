#include <Mgt_Node.hpp>
#include <Mgt_IPCC.hpp>
#include <Mgt_Neighbor.hpp>
#include <iostream>
#include <iterator>
using namespace std;

namespace lmp_node
{

Node_i::Node_i(
  CORBA::ORB_ptr           orb,
  PortableServer::POA_ptr  poa,
  ::CORBA::Long            nodeId)
: theORB(CORBA::ORB::_duplicate(orb)),
  thePOA(PortableServer::POA::_duplicate(poa)),
  theNodeId(nodeId)
{
  //PortableServer::ObjectId *oid=thePOA->activate_object(this); delete oid;
}

Node_i::~Node_i()
{
  CORBA::release(thePOA);
  CORBA::release(theORB);
}

::CORBA::Long Node_i::getNodeId()
{
  return theNodeId;
}

lmp_ipcc::IPCC_ptr Node_i::createIPCC(
  ::CORBA::Long localCCId,
  ::CORBA::Long localAddress,
  ::CORBA::Short localPortNumber)
{
  if (theIPCCByCCId.find(localCCId) == theIPCCByCCId.end())
  {
	lmp_ipcc::IPCC_i* servant = new lmp_ipcc::IPCC_i(thePOA, this->_this(), localCCId, localAddress, localPortNumber);
    PortableServer::ObjectId *oid=thePOA->activate_object(servant);  delete oid;
    return theIPCCByCCId.insert(IPCCByCCIdMap::value_type(localCCId, servant->_this())).first->second;
  }
  throw lmp_node::Entity_Already_Exists();
}

lmp_ipcc::IPCC_ptr Node_i::getIPCC(
  ::CORBA::Long localCCId)
{
  IPCCByCCIdMap::const_iterator ipccIter = theIPCCByCCId.find(localCCId);
  if (ipccIter != theIPCCByCCId.end())
  {
	return ipccIter->second;
  }
  throw lmp_node::No_Such_Entity();
}

void Node_i::deleteIPCC(
 ::CORBA::Long localCCId)
{
  IPCCByCCIdMap::iterator ipccIter = theIPCCByCCId.find(localCCId);
  if (ipccIter != theIPCCByCCId.end())
  {
	theIPCCByCCId.erase(ipccIter);
  }
  throw lmp_node::No_Such_Entity();
}


lmp_neighbor::Neighbor_ptr Node_i::createNeighbor(
  ::CORBA::Long remoteNodeId)
{
  if (theNeighborByNodeIdMap.find(remoteNodeId) == theNeighborByNodeIdMap.end())
  {
	lmp_neighbor::Neighbor_i* servant = new lmp_neighbor::Neighbor_i(thePOA, this->_this(), remoteNodeId);
	PortableServer::ObjectId *oid=thePOA->activate_object(servant);  delete oid;
	return theNeighborByNodeIdMap.insert(NeighborByNodeIdMap::value_type(remoteNodeId, servant->_this())).first->second;
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
  PortableServer::ObjectId *oid=thePOA->servant_to_id(this);
  thePOA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
}

} // end namespace lmp_node
