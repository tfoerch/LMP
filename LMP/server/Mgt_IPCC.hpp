#include <lmp_mgtif_ipcc.hpp>
#include <lmp_mgtif_ipcc_observer.hpp>
#include <lmp_mgtif_node.hpp>
#include <Mgt_NodeApplProxy.hpp>
#include <Mgt_NetworkIFProxy.hpp>
#include "cc/UDP_Msg_Handler.hpp"
#include "cc/IPCC_Impl.hpp"

#include <omniORB4/CORBA.h>  // for Long, Short
#include <omniORB4/poa.h>    // for POA_ptr

namespace lmp_node
{
  class NodeApplProxy;
}

namespace lmp_ipcc
{
  class IPCC_i : public POA_lmp_ipcc::IPCC
  {
  public:
    IPCC_i(
      PortableServer::POA_ptr                poa,
      lmp_node::NodeApplProxy&               node,
      ::lmp_netif::NetworkIF_ptr             networkIfPtr,
      const boost::asio::ip::udp::endpoint&  sender_endpoint);
    virtual ~IPCC_i();
    virtual void destroy();
    virtual void enable();
    virtual void disable();
    virtual void registerObserver(
      ::lmp_ipcc_observer::IPCCObserver_ptr  observer);
    virtual void deregisterObserver(
      ::lmp_ipcc_observer::IPCCObserver_ptr  observer);
  private:
    PortableServer::POA_ptr    thePOA;
    lmp_node::NodeApplProxy&   m_node;
    lmp_netif::NetworkIFProxy  m_metworkIf;
    lmp::cc::IpccImpl          m_IPCCImpl;
  };

} // end namespace LMP
