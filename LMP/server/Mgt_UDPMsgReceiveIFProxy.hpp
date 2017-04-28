#ifndef Server_UDPMsgReceiveIF_Proxy_HPP_
#define Server_UDPMsgReceiveIF_Proxy_HPP_
/*
 * Mgt_UDPMsgReceiveIFProxy.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/UDP_Msg_ReceiveIF.hpp"
#include "cc/UDP_Msg_Handler.hpp"
#include <lmp_mgtif_node.hpp>
#include <lmp_mgtif_netif.hpp>

namespace lmp_node
{
  class NodeApplProxy;
}

namespace lmp_netif
{
  class UDPMsgReceiveIFProxy : public lmp::cc::UDPMsgReceiveIF
  {
  public:
    UDPMsgReceiveIFProxy(
      lmp_node::NodeApplProxy&    node);
    virtual ~UDPMsgReceiveIFProxy(){}
    void setNetworkIFObjRef(
      ::lmp_netif::NetworkIF_ptr  networkIfPtr);
    void clearNetworkIFObjRef();
  private:
    // implement UDPMsgReceiveIF
    virtual void do_processReceivedMessage(
      lmp::cc::NetworkIFSocketIF&            networkIFSocket,
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      boost::asio::const_buffers_1&          messageBuffer);

    lmp_node::NodeApplProxy&    m_node;
    lmp::cc::UDPMsgHandler      m_udpMsgHandler;
    ::lmp_netif::NetworkIF_var  m_netifPtr;
  };

} // end namespace LMP

#endif /* Server_UDPMsgReceiveIF_Proxy_HPP_ */
