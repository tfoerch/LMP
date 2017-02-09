#ifndef LMP_CC_UDP_MSG_RECEIVEIF_HPP_
#define LMP_CC_UDP_MSG_RECEIVEIF_HPP_
/*
 * UDP_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"             // for DWORD

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>

namespace lmp
{
  namespace cc
  {
    class UDPMsgReceiveIF
    {
    public:
      inline void processReceivedMessage(
        lmp::DWORD                             localCCId,
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	boost::asio::const_buffers_1&          messageBuffer)
      { do_processReceivedMessage(localCCId, sender_endpoint, messageBuffer); }
      virtual ~UDPMsgReceiveIF(){}
    private:
      virtual void do_processReceivedMessage(
        lmp::DWORD                             localCCId,
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        boost::asio::const_buffers_1&          messageBuffer) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_UDP_MSG_RECEIVEIF_HPP_ */
