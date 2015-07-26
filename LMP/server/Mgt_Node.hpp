#include <lmp_mgtif_node.hpp>
#include <lmp_mgtif_node_registry.hpp>

#include <iostream>
#include <map>
using namespace std;

namespace lmp_node
{

class Node_i : public POA_lmp_node::Node
{
public:
  Node_i(
    CORBA::ORB_ptr                         orb,
    PortableServer::POA_ptr                poa,
    ::CORBA::Long                          nodeId,
	::lmp_node_registry::NodeRegistry_ptr  aNodeRegistry);
  virtual ~Node_i();
  virtual ::CORBA::Long getNodeId();
  virtual ::lmp_ipcc::IPCC_ptr createIPCC(
    ::CORBA::Long localCCId,
    ::CORBA::Long localAddress,
	::CORBA::Long remoteAddress,
    ::CORBA::Short localPortNumber,
	::CORBA::Short remotePortNumber);
  virtual ::lmp_ipcc::IPCC_ptr getIPCC(
    ::CORBA::Long localCCId);
  virtual void deleteIPCC(
   ::CORBA::Long localCCId);
  virtual ::lmp_neighbor::Neighbor_ptr createNeighbor(
    ::CORBA::Long remoteNodeId);
  virtual ::lmp_neighbor::Neighbor_ptr getNeighbor(
    ::CORBA::Long remoteNodeId);
  virtual void deleteNeighbor(
    ::CORBA::Long remoteNodeId);
  virtual void destroy();
private:
  typedef  std::map<CORBA::Long, ::lmp_ipcc::IPCC_var>          IPCCByCCIdMap;
  typedef  std::map<CORBA::Long, ::lmp_neighbor::Neighbor_var>  NeighborByNodeIdMap;

  CORBA::ORB_ptr                         theORB;
  PortableServer::POA_ptr                thePOA;
  ::CORBA::Long                          theNodeId;
  ::lmp_node_registry::NodeRegistry_var  theNodeRegistry;
  IPCCByCCIdMap                          theIPCCByCCId;
  NeighborByNodeIdMap                    theNeighborByNodeIdMap;
};

} // end namespace LMP
