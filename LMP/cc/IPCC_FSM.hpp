#ifndef LIBS_IPCC_FSM_HPP_
#define LIBS_IPCC_FSM_HPP_
/*
 * IPCC_FSM.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "cc/IPCC_ObserverIF.hpp"

#include <boost/optional/optional.hpp>     // for optional
#include <boost/smart_ptr/shared_ptr.hpp>  // for shared_ptr

namespace lmp
{
  namespace msg
  {
    class Config;
  }
  namespace cc
  {
    class IpccFsmInvokeIF;
	struct SomeVisitor
	{
	  template <class T>
	  void visit_state(const T& astate)
	  {
		// std::cout << "visiting state:" << astate.getApplState() << std::endl;
		theActiveState = boost::optional<const lmp::cc::appl::State&>(astate.getApplState());
	  }
	  boost::optional<const lmp::cc::appl::State&>  theActiveState;
	};
    class EvBringUp
    {
	public:
      static lmp::cc::appl::EvBringUp  theApplEvent;
    };
    class EvCCDn
    {
	public:
      static lmp::cc::appl::EvCCDn  theApplEvent;
    };
    class EvConfDone
    {
	public:
      static lmp::cc::appl::EvConfDone  theApplEvent;
    };
    class EvConfErr
    {
	public:
      static lmp::cc::appl::EvConfErr  theApplEvent;
    };
    class EvNewConfOK
    {
	public:
      static lmp::cc::appl::EvNewConfOK  theApplEvent;
    };
    class EvNewConfErr
    {
	public:
      static lmp::cc::appl::EvNewConfErr  theApplEvent;
    };
    class EvContenWin
    {
	public:
      static lmp::cc::appl::EvContenWin  theApplEvent;
    };
    class EvContenLost
	{
	public:
      explicit EvContenLost(const msg::Config&  configMsg)
	  : theConfigMsg(configMsg)
	  {}
      const msg::Config&  theConfigMsg;
      static lmp::cc::appl::EvContenLost  theApplEvent;
	};
    class EvAdminDown
    {
	public:
      static lmp::cc::appl::EvAdminDown  theApplEvent;
    };
    class EvNbrGoesDn
    {
	public:
      static lmp::cc::appl::EvNbrGoesDn  theApplEvent;
    };
   class EvHelloRcvd
   {
	public:
     static lmp::cc::appl::EvHelloRcvd  theApplEvent;
   };
    class EvHoldTimer
    {
	public:
      static lmp::cc::appl::EvHoldTimer  theApplEvent;
    };
    class EvSeqNumErr
    {
	public:
      static lmp::cc::appl::EvSeqNumErr  theApplEvent;
    };
   class EvReconfig
   {
	public:
     static lmp::cc::appl::EvReconfig  theApplEvent;
   };
    class EvConfRet
    {
	public:
      static lmp::cc::appl::EvConfRet  theApplEvent;
    };
    class EvHelloRet
    {
	public:
      static lmp::cc::appl::EvHelloRet  theApplEvent;
    };
    class EvDownTimer
    {
	public:
      static lmp::cc::appl::EvDownTimer  theApplEvent;
    };
    class FSM_IPCC
    {
    public:
      explicit FSM_IPCC(
        IpccFsmInvokeIF&  ipcc);
      // forward-declare nested type. This will inherit msm::back::state_machine<...>
      bool start();
      bool stop();
      boost::optional<const lmp::cc::appl::State&> getActiveState() const;
      template <class Event>
      bool process_event(const Event& e);
      struct FsmIpccImpl;
      // with shared_ptr, you don't need the complete type yet.
      boost::shared_ptr<FsmIpccImpl> theFSMImpl;
    };
  } // namespace cc
} // namespace lmp

#endif /* LIBS_IPCC_FSM_HPP_ */
