#ifndef Server_NetworkIF_Proxy_HPP_
#define Server_NetworkIF_Proxy_HPP_
/*
 * Mgt_NetworkIFProxy.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/NetworkIFSocketIF.hpp"
#include <lmp_mgtif_netif.hpp>

namespace lmp_netif
{

  class NetworkIFProxy : public lmp::cc::NetworkIFSocketIF
  {
  public:
    NetworkIFProxy(
      ::lmp_netif::NetworkIF_ptr     netifPtr);
    virtual ~NetworkIFProxy(){}
  private:
    // implement NetworkIFSocketIF
    virtual lmp::DWORD do_getLocalCCId() const;
    virtual void do_send(
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      boost::asio::mutable_buffers_1&        messageBuffer);
    ::lmp_netif::NetworkIF_var    m_netifPtr;
  };

} // end namespace lmp_netif

#endif /* Server_NetworkIF_Proxy_HPP_ */
