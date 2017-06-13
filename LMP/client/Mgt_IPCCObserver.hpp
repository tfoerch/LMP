#include <lmp_mgtif_ipcc_observer.hpp>

#include <omniORB4/CORBA.h>              // for ORB_ptr
#include <omniORB4/poa.h>                    // for POA_ptr, etc

namespace lmp_ipcc_observer
{

class IPCCObserver_i : public POA_lmp_ipcc_observer::IPCCObserver,
                       public virtual PortableServer::RefCountServantBase
{
public:
  IPCCObserver_i(
    CORBA::ORB_ptr           orb,
    PortableServer::POA_ptr  poa);
  virtual ~IPCCObserver_i();
  virtual void destroy();
  virtual void stateHasChanged(
    ::CORBA::Long                   localCCId,
    ::lmp_ipcc_observer::IPCC_State newState);
  virtual void peerIpccDiscovered(
    ::CORBA::Long    localCCId,
    ::CORBA::Long    remoteCCId,
    ::CORBA::Long    remoteNodeId);
private:

  CORBA::ORB_ptr           theORB;
  PortableServer::POA_ptr  thePOA;
};

} // end namespace lmp_ipcc_observer
