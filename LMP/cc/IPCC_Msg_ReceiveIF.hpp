#ifndef LMP_CC_MSG_RECEIVEIF_HPP_
#define LMP_CC_MSG_RECEIVEIF_HPP_
/*
 * IPCC_Msg_ReceiveIF.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace obj { class HelloConfig; }
  namespace msg
  {
    class Config;
    class ConfigAck;
    class ConfigNack;
    class Hello;
  }
  namespace cc
  {
    class IpccMsgReceiveIF
    {
    public:
      inline void processReceivedMessage(
    	const msg::Config&      configMsg) { do_processReceivedMessage(configMsg); }
      inline void processReceivedMessage(
    	const msg::ConfigAck&   configAckMsg) { do_processReceivedMessage(configAckMsg); }
      inline void processReceivedMessage(
    	const msg::ConfigNack&  configNackMsg) { do_processReceivedMessage(configNackMsg); }
      inline void processReceivedMessage(
    	const msg::Hello&       helloMsg) { do_processReceivedMessage(helloMsg); }
      virtual ~IpccMsgReceiveIF(){}
    private:
      virtual void do_processReceivedMessage(
    	const msg::Config&      configMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ConfigAck&   configAckMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::ConfigNack&  configNackMsg) = 0;
      virtual void do_processReceivedMessage(
    	const msg::Hello&       helloMsg) = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LMP_CC_MSG_RECEIVEIF_HPP_ */
