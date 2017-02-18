#ifndef LMP_CC_MSG_RECEIVEIF_HPP_
#define LMP_CC_MSG_RECEIVEIF_HPP_
/*
 * IPCC_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "msg/Config.hpp"
#include "msg/ConfigAck.hpp"
#include "msg/ConfigNack.hpp"
#include "msg/Hello.hpp"
#include "msg/UnknownMessage.hpp"

#include <boost/asio/ip/udp.hpp>

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace cc
  {
    class IpccMsgReceiveIF
    {
    public:
      inline void processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigMsg&                  configMsg)
      { do_processReceivedMessage(sender_endpoint, configMsg); }
      inline void processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigAckMsg&               configAckMsg)
      { do_processReceivedMessage(sender_endpoint, configAckMsg); }
      inline void processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigNackMsg&              configNackMsg)
      { do_processReceivedMessage(sender_endpoint, configNackMsg); }
      inline void processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::HelloMsg&                   helloMsg)
      { do_processReceivedMessage(sender_endpoint, helloMsg); }
      inline void processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        const msg::UnknownMessage&             unknownMessage)
      { do_processReceivedMessage(sender_endpoint, unknownMessage); }
      virtual ~IpccMsgReceiveIF(){}
    private:
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigMsg&                  configMsg) = 0;
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigAckMsg&               configAckMsg) = 0;
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::ConfigNackMsg&              configNackMsg) = 0;
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
    	const msg::HelloMsg&                   helloMsg) = 0;
      virtual void do_processReceivedMessage(
        const boost::asio::ip::udp::endpoint&  sender_endpoint,
        const msg::UnknownMessage&             unknownMessage) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_MSG_RECEIVEIF_HPP_ */
