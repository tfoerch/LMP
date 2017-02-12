/*
 * UDP_Msg_Handler.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "UDP_Msg_Handler.hpp"

namespace lmp
{
  namespace cc
  {
    void UDPMsgHandler::registerNetIFSocket(
      NetworkIFSocketIF&  netIfSocket)
    {
      m_networkInterfaces.insert(NetworkInterfaceMap::value_type(netIfSocket.getLocalCCId(),
                                                                 &netIfSocket));
    }
    void UDPMsgHandler::do_processReceivedMessage(
      lmp::DWORD                             localCCId,
      const boost::asio::ip::udp::endpoint&  sender_endpoint,
      boost::asio::const_buffers_1&          messageBuffer)
    {
    }
    void UDPMsgHandler::do_sendMessage(
      lmp::DWORD                             localCCId,
      const boost::asio::ip::udp::endpoint&  destination_endpoint,
      const msg::Message&                    message)
    {
    }
  } // namespace cc
} // namespace lmp
