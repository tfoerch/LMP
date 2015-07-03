#include <lmp_mgtif_neighbor.hpp>
#include <lmp_mgtif_node.hpp>

#include <iostream>
using namespace std;

namespace lmp_neighbor
{

class Neighbor_i : public POA_lmp_neighbor::Neighbor
{
public:
  Neighbor_i(
    PortableServer::POA_ptr  poa,
	::lmp_node::Node_ptr     nodePtr,
    ::CORBA::Long            remoteNodeId);
  virtual ~Neighbor_i();
  virtual void destroy();
  virtual void enable();
  virtual void disable();
//  virtual void registerObserver(::LMP::NeighborObserver_ptr observer);
//  virtual void deregisterObserver(::LMP::NeighborObserver_ptr observer);
private:
  PortableServer::POA_ptr thePOA;
  ::lmp_node::Node_ptr    theNodePtr;
  ::CORBA::Long           theRemoteNodeId;
};

} // end namespace LMP
