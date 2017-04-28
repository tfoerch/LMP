#include <Mgt_UDPMsgReceiveIFProxy.hpp>
#include <Mgt_NodeApplProxy.hpp>
#include <lmp_mgtif_ipcc.hpp>

#include "base/ProtocolTypes.hpp"                  // for DWORD

#include <iostream>

namespace lmp_netif
{
  UDPMsgReceiveIFProxy::UDPMsgReceiveIFProxy(
    lmp_node::NodeApplProxy&    node)
  : m_node(node),
    m_udpMsgHandler(m_node),
    m_netifPtr(lmp_netif::NetworkIF::_nil())
  {
  }

  void UDPMsgReceiveIFProxy::do_processReceivedMessage(
    lmp::cc::NetworkIFSocketIF&            networkIFSocket,
    const boost::asio::ip::udp::endpoint&  sender_endpoint,
    boost::asio::const_buffers_1&          messageBuffer)
  {
    lmp::DWORD  ipAddr = sender_endpoint.address().to_v4().to_ulong();
    ::lmp_ipcc::IPCC_ptr ipccPtr = m_netifPtr->getIPCC(ipAddr, sender_endpoint.port());
    if (CORBA::is_nil(ipccPtr))
    {
      std::cout << "need to create new IPCC" << std::endl;
      ipccPtr = m_netifPtr->createIPCC(ipAddr, sender_endpoint.port());
    }
    if (!CORBA::is_nil(ipccPtr))
    {
      std::cout << "IPCC exists" << std::endl;
    }
  }
  void UDPMsgReceiveIFProxy::setNetworkIFObjRef(
    ::lmp_netif::NetworkIF_ptr  networkIfPtr)
  {
    m_netifPtr = lmp_netif::NetworkIF::_duplicate(networkIfPtr);
  }
  void UDPMsgReceiveIFProxy::clearNetworkIFObjRef()
  {
    m_netifPtr = lmp_netif::NetworkIF::_nil();
  }

} // end namespace lmp_netif
