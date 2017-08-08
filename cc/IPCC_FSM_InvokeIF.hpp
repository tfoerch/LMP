#ifndef LIBS_IPCC_FSM_INVOKE_IF_HPP_
#define LIBS_IPCC_FSM_INVOKE_IF_HPP_
/*
 * IPCC_FSM_InvokeIF.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for WORD
#include "msg/Config.hpp"

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      class State;
      class Event;
      class Action;
    }
    class IpccFsmInvokeIF
    {
    public:
      inline bool hasActiveSetupRole() const
      { return do_hasActiveSetupRole(); }
      inline bool isConntentionWinning(
        lmp::DWORD  remoteNodeId) const
      { return do_isConntentionWinning(remoteNodeId); }
      inline bool isConfigAcceptable(
        const msg::ConfigMsg&  configMsg) const
      { return do_isConfigAcceptable(configMsg); }
      inline void sendConfig()
      { do_sendConfig(); }
      inline void resendConfig()
      { do_resendConfig(); }
      inline void stopSendConfig()
      { do_stopSendConfig(); }
      inline void sendConfigAck(
        const msg::ConfigMsg&  configMsg)
      { do_sendConfigAck(configMsg); }
      inline void sendConfigNack(
        const msg::ConfigMsg&  configMsg)
      { do_sendConfigNack(configMsg); }
      inline void reportTransition(
        const appl::State&   sourceState,
        const appl::Event&   event,
        const appl::State&   targetState,
        const appl::Action&  action)
      {  do_reportTransition(sourceState, event, targetState, action); }
      inline void sendHello()
      { do_sendHello(); }
      inline void stopSendHello()
      { do_stopSendHello(); }
      virtual ~IpccFsmInvokeIF(){}
    private:
      virtual bool do_hasActiveSetupRole() const = 0;
      virtual bool do_isConntentionWinning(
        lmp::DWORD  remoteNodeId) const = 0;
      virtual bool do_isConfigAcceptable(
        const msg::ConfigMsg&  configMsg) const = 0;
      virtual void do_sendConfig() = 0;
      virtual void do_resendConfig() = 0;
      virtual void do_stopSendConfig() = 0;
      virtual void do_sendConfigAck(
        const msg::ConfigMsg&  configMsg) = 0;
      virtual void do_sendConfigNack(
        const msg::ConfigMsg&  configMsg) = 0;
      virtual void do_reportTransition(
    	const appl::State&   sourceState,
    	const appl::Event&   event,
    	const appl::State&   targetState,
    	const appl::Action&  action) = 0;
      virtual void do_sendHello() = 0;
      virtual void do_stopSendHello() = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_FSM_INVOKE_IF_HPP_ */