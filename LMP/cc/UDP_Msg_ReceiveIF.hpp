#ifndef LMP_CC_UDP_MSG_RECEIVEIF_HPP_
#define LMP_CC_UDP_MSG_RECEIVEIF_HPP_
/*
 * UDP_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/asio/ip/udp.hpp>
#include <boost/asio/buffer.hpp>

namespace lmp
{
  namespace cc
  {
    class NetworkIFSocketIF;
    class UDPMsgReceiveIF
    {
    public:
      inline void processReceivedMessage(
        NetworkIFSocketIF&                     networkIFSocket,
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	boost::asio::const_buffers_1&          messageBuffer)
      { do_processReceivedMessage(networkIFSocket, sender_endpoint, messageBuffer); }
      virtual ~UDPMsgReceiveIF(){}
    private:
      virtual void do_processReceivedMessage(
        NetworkIFSocketIF&                     networkIFSocket,
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        boost::asio::const_buffers_1&          messageBuffer) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_UDP_MSG_RECEIVEIF_HPP_ */
