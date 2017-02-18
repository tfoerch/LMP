#ifndef LMP_CC_UDP_MSG_HANDLER_HPP_
#define LMP_CC_UDP_MSG_HANDLER_HPP_
/*
 * UDP_Msg_Handler.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "UDP_Msg_ReceiveIF.hpp"
#include "IPCC_Msg_SendIF.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>
#include <map>

namespace lmp
{
  namespace node
  {
    class Node;
  }
  namespace cc
  {
    class IpccMsgReceiveIF;
    class NetworkIFSocketIF;

    class UDPMsgHandler : public UDPMsgReceiveIF
    {
    public:
      UDPMsgHandler(
        node::Node&           node);
      virtual ~UDPMsgHandler(){}
      inline const node::Node& getNode() const
      { return m_node; }
      static void sendMessage(
        NetworkIFSocketIF&                     networkIFSocket,
        const boost::asio::ip::udp::endpoint&  destination_endpoint,
        const msg::Message&                    message);
    private:
      typedef std::map<boost::asio::ip::udp::endpoint, IpccMsgReceiveIF*>  IPCCMap;
      // implement UDPMsgReceiveIF
      virtual void do_processReceivedMessage(
        NetworkIFSocketIF&                     networkIFSocket,
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        boost::asio::const_buffers_1&          messageBuffer);
      node::Node&         m_node;
      IPCCMap             m_IPCCs;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_NETIFSOCKET_HPP_ */
