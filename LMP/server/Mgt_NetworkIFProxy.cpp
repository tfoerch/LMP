#include <Mgt_NetworkIFProxy.hpp>
#include <iostream>

namespace lmp_netif
{
  NetworkIFProxy::NetworkIFProxy(
    ::lmp_netif::NetworkIF_ptr     netifPtr)
  : m_netifPtr(lmp_netif::NetworkIF::_duplicate(netifPtr))
  {
  }

  lmp::DWORD NetworkIFProxy::do_getLocalCCId() const
  {
    return m_netifPtr->getLocalCCId();
  }

  void NetworkIFProxy::do_send(
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      boost::asio::mutable_buffers_1&        messageBuffer)
  {
  }

} // end namespace lmp_netif
