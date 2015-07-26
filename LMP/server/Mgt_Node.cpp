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
  ::CORBA::Long            nodeId,
  ::lmp_node_registry::NodeRegistry_ptr  aNodeRegistry)
: theORB(CORBA::ORB::_duplicate(orb)),
  thePOA(PortableServer::POA::_duplicate(poa)),
  theNodeId(nodeId),
  theNodeRegistry(::lmp_node_registry::NodeRegistry::_duplicate(aNodeRegistry))
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
  ::CORBA::Long remoteAddress,
  ::CORBA::Short localPortNumber,
  ::CORBA::Short remotePortNumber)
{
  if (theIPCCByCCId.find(localCCId) == theIPCCByCCId.end())
  {
	lmp_ipcc::IPCC_i* servant = new lmp_ipcc::IPCC_i(thePOA, this->_this(), localCCId, localAddress, localPortNumber);
    PortableServer::ObjectId *oid=thePOA->activate_object(servant);  delete oid;
    lmp_ipcc::IPCC_ptr ipcc = servant->_this();
    return theIPCCByCCId.insert(IPCCByCCIdMap::value_type(localCCId, lmp_ipcc::IPCC::_duplicate(ipcc))).first->second;
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
  PortableServer::ObjectId *oid=thePOA->servant_to_id(this);
  std::cout << "before deactivate_object" << std::endl;
  thePOA->deactivate_object(*oid);  delete oid;
  std::cout << "after deactivate_object" << std::endl;
  // _remove_ref(); // delete this;
  // std::cout << "after _remove_ref" << std::endl;
  // Shutdown the ORB (but do not wait for completion).  This also
  // causes the main thread to unblock from CORBA::ORB::run().
  theORB->shutdown(0);

}

} // end namespace lmp_node
