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

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace cc
  {
    class IpccMsgReceiveIF
    {
    public:
      inline void processReceivedMessage(
    	const msg::ConfigMsg&   configMsg) { do_processReceivedMessage(configMsg); }
      inline void processReceivedMessage(
    	const msg::ConfigAckMsg&   configAckMsg) { do_processReceivedMessage(configAckMsg); }
      inline void processReceivedMessage(
    	const msg::ConfigNackMsg&  configNackMsg) { do_processReceivedMessage(configNackMsg); }
      inline void processReceivedMessage(
    	const msg::HelloMsg&       helloMsg) { do_processReceivedMessage(helloMsg); }
      virtual ~IpccMsgReceiveIF(){}
    private:
      virtual void do_processReceivedMessage(
    	const msg::ConfigMsg&   configMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ConfigAckMsg&   configAckMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ConfigNackMsg&  configNackMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::HelloMsg&       helloMsg) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_MSG_RECEIVEIF_HPP_ */
