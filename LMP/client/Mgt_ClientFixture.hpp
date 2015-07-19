#ifndef MGT_CLIENT_FIXTURE_HPP_
#define MGT_CLIENT_FIXTURE_HPP_

#include <omniORB4/CORBA.h>
#include <boost/optional.hpp>
#include <sys/types.h>

namespace lmp_node_registry
{
  class NodeRegistry_i;
}

class LaunchServer
{
public:
  LaunchServer();
  ~LaunchServer();
  lmp_node_registry::NodeRegistry_i*  theNodeRegistry;
  boost::optional<CORBA::ORB_var>     theOrb;
  pid_t                               theChildPid;
};
#endif /* MGT_CLIENT_FIXTURE_HPP_ */
