#ifndef LMP_CC_UDP_MSG_HANDLER_HPP_
#define LMP_CC_UDP_MSG_HANDLER_HPP_
/*
 * UDP_Msg_Handler.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "UDP_Msg_ReceiveIF.hpp"
#include "NetworkIFSocketIF.hpp"
#include "base/ProtocolTypes.hpp"             // for DWORD

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>
#include <map>

namespace lmp
{
  namespace cc
  {
    class IpccMsgReceiveIF;

    class UDPMsgHandler : public UDPMsgReceiveIF
    {
    public:
      virtual ~UDPMsgHandler(){}
      void registerNetIFSocket(
        NetworkIFSocketIF&  netIfSocket);
    private:
      typedef std::map<lmp::DWORD, NetworkIFSocketIF*>  NetworkInterfaceMap;
      virtual void do_processReceivedMessage(
        lmp::DWORD                             localCCId,
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        boost::asio::const_buffers_1&          messageBuffer);
      NetworkInterfaceMap                    m_networkInterfaces;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_NETIFSOCKET_HPP_ */
