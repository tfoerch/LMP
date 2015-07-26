#include <lmp_mgtif_node_registry.hpp>
#include <lmp_mgtif_node.hpp>

#include <iostream>
#include <map>
using namespace std;

namespace lmp_node_registry
{

class NodeRegistry_i : public POA_lmp_node_registry::NodeRegistry
{
public:
  NodeRegistry_i(
    CORBA::ORB_ptr           orb,
    PortableServer::POA_ptr  poa);
  virtual ~NodeRegistry_i();
  virtual void registerNode(
    ::lmp_node::Node_ptr  aNode);
  virtual void deregisterNode(
    ::lmp_node::Node_ptr  aNode);
  virtual ::CORBA::Boolean isNodeRegistered(
	::CORBA::Long    nodeId);
  virtual ::lmp_node::Node_ptr getNode(
    ::CORBA::Long    nodeId);
  virtual void shutdown();
private:
  typedef  std::map<CORBA::Long, lmp_node::Node_var>      NodeByNodeIdMap;

  CORBA::ORB_ptr           theORB;
  PortableServer::POA_ptr  thePOA;
  NodeByNodeIdMap          theNodeByNodeIdMap;

};

} // end namespace lmp_node_registry
