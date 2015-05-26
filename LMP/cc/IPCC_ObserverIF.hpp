#ifndef LIBS_IPCC_OBSERVERIF_HPP_
#define LIBS_IPCC_OBSERVERIF_HPP_
/*
 * IPCC_ObserverIF.hpp
 *
 *  Created on: 11.03.2015
 *      Author: tom
 */

#include <iostream>

namespace lmp
{
  namespace cc
  {
    namespace appl
    {
	  class State
	  {
	  public:
		enum Type
		{
		  Down,
		  ConfSnd,
		  ConfRcv,
		  Active,
		  Up,
		  GoingDown
		};
		inline Type getType() const { return do_getType(); }
		inline bool operator==(const State& other) const { return getType() == other.getType(); }
		inline bool operator!=(const State& other) const { return getType() != other.getType(); }
		virtual ~State(){}
	  private:
		virtual Type do_getType() const = 0;
	  };
	  template <State::Type  stateType>
	  class StateTag : public State
	  {
	  public:
		virtual ~StateTag(){}
		StateTag(){}
	  private:
		virtual State::Type do_getType() const { return stateType; };
	  };
	  typedef StateTag<State::Down>       Down;
	  typedef StateTag<State::ConfSnd>    ConfSnd;
	  typedef StateTag<State::ConfRcv>    ConfRcv;
	  typedef StateTag<State::Active>     Active;
	  typedef StateTag<State::Up>         Up;
	  typedef StateTag<State::GoingDown>  GoingDown;
	  class Event
	  {
	  public:
	    enum EvType
	    {
		  EvBringUp,
		  EvCCDn,
		  EvConfDone,
		  EvConfErr,
		  EvNewConfOK,
		  EvNewConfErr,
		  EvContenWin,
		  EvContenLost,
		  EvAdminDown,
		  EvNbrGoesDn,
		  EvHelloRcvd,
		  EvHoldTimer,
		  EvSeqNumErr,
		  EvReconfig,
		  EvConfRet,
		  EvHelloRet,
		  EvDownTimer
	    };
	    inline EvType getType() const { return do_getType(); }
	    virtual ~Event(){}
	  private:
	    virtual EvType do_getType() const = 0;
	  };
	  template <Event::EvType  eventType>
	  class EventTag : public Event
	  {
	  public:
		virtual ~EventTag(){}
		EventTag(){}
	  private:
		virtual Event::EvType do_getType() const { return eventType; };
	  };
	  typedef EventTag<Event::EvBringUp>       EvBringUp;
	  typedef EventTag<Event::EvCCDn>          EvCCDn;
	  typedef EventTag<Event::EvConfDone>      EvConfDone;
	  typedef EventTag<Event::EvConfErr>       EvConfErr;
	  typedef EventTag<Event::EvNewConfOK>     EvNewConfOK;
	  typedef EventTag<Event::EvNewConfErr>    EvNewConfErr;
	  typedef EventTag<Event::EvContenWin>     EvContenWin;
	  typedef EventTag<Event::EvContenLost>    EvContenLost;
	  typedef EventTag<Event::EvAdminDown>     EvAdminDown;
	  typedef EventTag<Event::EvNbrGoesDn>     EvNbrGoesDn;
	  typedef EventTag<Event::EvHelloRcvd>     EvHelloRcvd;
	  typedef EventTag<Event::EvHoldTimer>     EvHoldTimer;
	  typedef EventTag<Event::EvSeqNumErr>     EvSeqNumErr;
	  typedef EventTag<Event::EvReconfig>      EvReconfig;
	  typedef EventTag<Event::EvConfRet>       EvConfRet;
	  typedef EventTag<Event::EvHelloRet>      EvHelloRet;
	  typedef EventTag<Event::EvDownTimer>     EvDownTimer;
	  class Action
	  {
	  public:
		enum ActionType
		{
	      ActionSendConfig,
		  ActionStopSendConfig,
		  ActionResendConfig,
		  ActionSendConfigAck,
		  ActionSendConfigNack,
		  ActionSendHello,
		  ActionStopSendHello,
		  ActionSetCCDownFlag,
		  ActionClearCCDownFlag,
		  ActionNoAction
		};
		inline ActionType getType() const { return do_getType(); }
		virtual ~Action(){}
	  private:
	    virtual ActionType do_getType() const = 0;
	  };
	  template <Action::ActionType  actionType>
	  class ActionTag : public Action
	  {
	  public:
		virtual ~ActionTag(){}
	  private:
		virtual Action::ActionType do_getType() const { return actionType; };
	  };
	  class IpccObserverIF
	  {
	  public:
		inline void notifyTransition(
	   	  const appl::State&   sourceState,
		  const appl::Event&   event,
		  const appl::State&   targetState,
		  const appl::Action&  action) {  do_notifyTransition(sourceState, event, targetState, action); }
		virtual ~IpccObserverIF(){}
	  private:
		virtual void do_notifyTransition(
		  const appl::State&   sourceState,
		  const appl::Event&   event,
		  const appl::State&   targetState,
		  const appl::Action&  action) = 0;
	  };
	  std::ostream& operator<<(
	    std::ostream&       os,
		const Event&        event); // implemented in IPCC_Impl.cpp
	  std::ostream& operator<<(
	    std::ostream&       os,
		Event::EvType       evType); // implemented in IPCC_Impl.cpp
	  std::ostream& operator<<(
	    std::ostream&       os,
		const State&        state); // implemented in IPCC_Impl.cpp
	  std::ostream& operator<<(
	    std::ostream&       os,
		State::Type         stType); // implemented in IPCC_Impl.cpp
	  std::ostream& operator<<(
	    std::ostream&       os,
		const Action&       action); // implemented in IPCC_Impl.cpp
	  std::ostream& operator<<(
	    std::ostream&       os,
		Action::ActionType  actionType); // implemented in IPCC_Impl.cpp
    } // namespace appl
  } // namespace cc
} // namespace lmp


#endif /* LIBS_IPCC_OBSERVERIF_HPP_ */
