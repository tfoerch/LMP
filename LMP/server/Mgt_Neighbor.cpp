#include <Mgt_Neighbor.hpp>
#include "lmp_mgtif_node.hpp"  // for Node_ptr, _objref_Node

#include <iostream>

namespace lmp_neighbor
{

Neighbor_i::Neighbor_i(
  PortableServer::POA_ptr  poa,
  ::lmp_node::Node_ptr     nodePtr,
  ::CORBA::Long            remoteNodeId)
: thePOA(PortableServer::POA::_duplicate(poa)),
  theNodePtr(nodePtr),
  theRemoteNodeId(remoteNodeId)
{
  std::cout << "Neighbor(remoteNodeId = " << remoteNodeId << ')' << std::endl;
}

Neighbor_i::~Neighbor_i()
{
}

void Neighbor_i::destroy()
{
  theNodePtr->deleteNeighbor(theRemoteNodeId);
  PortableServer::ObjectId *oid=thePOA->servant_to_id(this);
  thePOA->deactivate_object(*oid);  delete oid;
  _remove_ref(); // delete this;
}

void Neighbor_i::enable()
{
}

void Neighbor_i::disable()
{
}

//void Neighbor_i::registerObserver(
//  ::LMP::NeighborObserver_ptr observer)
//{
//}
//
//void Neighbor_i::deregisterObserver(
//  ::LMP::NeighborObserver_ptr observer)
//{
//}

} // end namespace lmp_neighbor
