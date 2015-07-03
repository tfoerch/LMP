#include <lmp_mgtif_ipcc.hpp>
#include <lmp_mgtif_ipcc_observer.hpp>
#include <lmp_mgtif_node.hpp>

#include <iostream>
using namespace std;

namespace lmp_ipcc
{

class IPCC_i : public POA_lmp_ipcc::IPCC
{
public:
  IPCC_i(
    PortableServer::POA_ptr  poa,
	::lmp_node::Node_ptr     nodePtr,
    ::CORBA::Long            localCCId,
    ::CORBA::Long            localAddress,
    ::CORBA::Short           localPortNumber);
  virtual ~IPCC_i();
  virtual void destroy();
  virtual void enable();
  virtual void disable();
  virtual void registerObserver(::lmp_ipcc_observer::IPCCObserver_ptr observer);
  virtual void deregisterObserver(::lmp_ipcc_observer::IPCCObserver_ptr observer);
private:
  PortableServer::POA_ptr thePOA;
  ::lmp_node::Node_ptr    theNodePtr;
  ::CORBA::Long           theLocalCCId;
  ::CORBA::Long           theLocalAddress;
  ::CORBA::Short          theLocalPortNumber;
};

} // end namespace LMP
