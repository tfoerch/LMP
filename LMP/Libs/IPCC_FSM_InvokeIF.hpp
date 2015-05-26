#ifndef LIBS_IPCC_FSM_INVOKE_IF_HPP_
#define LIBS_IPCC_FSM_INVOKE_IF_HPP_
/*
 * IPCC_FSM_InvokeIF.hpp
 *
 *  Created on: 16.02.2015
 *      Author: tom
 */

#include <ProtocolTypes.hpp>

// http://www.boost.org/doc/libs/1_57_0/libs/ptr_container/doc/guidelines.html
namespace lmp
{
  namespace msg
  {
  	class Config;
  }
  namespace cc
  {
    namespace appl
    {
	  class State;
	  class Event;
    }
    class IpccFsmInvokeIF
    {
    public:
      inline bool hasActiveSetupRole() const { return do_hasActiveSetupRole(); }
      inline bool isConntentionWinning(
        lmp::DWORD  remoteNodeId) const { return do_isConntentionWinning(remoteNodeId); }
      inline bool isConfigAcceptable(
        const msg::Config&  configMsg) const { return do_isConfigAcceptable(configMsg); }
      inline void reportTransition(
        const appl::State&   sourceState,
		const appl::Event&   event,
		const appl::State&   targetState,
		const appl::Action&  action) const {  do_reportTransition(sourceState, event, targetState, action); }
      inline void sendHelloMsg() { do_sendHelloMsg(); }
      virtual ~IpccFsmInvokeIF(){}
    private:
      virtual bool do_hasActiveSetupRole() const = 0;
      virtual bool do_isConntentionWinning(
        lmp::DWORD  remoteNodeId) const = 0;
      virtual bool do_isConfigAcceptable(
        const msg::Config&  configMsg) const = 0;
      virtual void do_reportTransition(
    	const appl::State&   sourceState,
		const appl::Event&   event,
		const appl::State&   targetState,
		const appl::Action&  action) const = 0;
      virtual void do_sendHelloMsg() = 0;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_FSM_INVOKE_IF_HPP_ */
