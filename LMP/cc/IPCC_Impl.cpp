/*
 * IPCC_Impl.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "IPCC_Impl.hpp"
#include "IPCC_ObserverIF.hpp"
#include "msg/Config.hpp"
#include "msg/ConfigAck.hpp"
#include "msg/ConfigNack.hpp"
#include "msg/Hello.hpp"

#include <boost/core/explicit_operator_bool.hpp>
#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <deque>
#include <limits>
#include <ostream>

namespace lmp
{
  namespace cc
  {
    IpccImpl::IpccImpl(
      lmp::DWORD  localNodeId,
      lmp::DWORD  localCCId,
      bool        isActiveSetup)
      : theLocalNodeId(localNodeId),
		theLocalCCId(localCCId),
        theIsActiveSetup(isActiveSetup),
        theFSM(*this),
		theTxSeqNum(0),
		theRcvSeqNum(0),
		theObservers()
    {
      theFSM.start();
    }
    IpccImpl::~IpccImpl()
    {
      theFSM.stop();
    }
    void IpccImpl::enable()
    {
      theFSM.start();
      theFSM.process_event(EvBringUp());
    }
    void IpccImpl::disable()
    {
      theFSM.process_event(EvAdminDown());
    }
    lmp::DWORD  IpccImpl::getLocalNodeId() const
    {
      return theLocalNodeId;
    }
    lmp::DWORD  IpccImpl::getLocalCCId() const
    {
      return theLocalCCId;
    }
    void IpccImpl::reconfigure(
      const obj::HelloConfig&  helloConfig)
    {
      theFSM.process_event(EvReconfig());
    }
    void IpccImpl::evtCCDown()
    {
      theFSM.process_event(EvCCDn());
      theFSM.stop();
    }
    void IpccImpl::evtConfRet()
    {
      theFSM.process_event(EvConfRet());
    }
    void IpccImpl::evtHelloRet()
    {
      theFSM.process_event(EvHelloRet());
    }
    void IpccImpl::evtDownTimer()
    {
      theFSM.process_event(EvDownTimer());
    }
    boost::optional<const lmp::cc::appl::State&> IpccImpl::getActiveState() const
    {
      return theFSM.getActiveState();
    }
    void IpccImpl::registerObserver(
      appl::IpccObserverProxyIF&  observer)
    {
      theObservers.push_back(new_clone(observer));
    }
    void IpccImpl::deregisterObserver(
  	appl::IpccObserverProxyIF&  observer)
    {
      bool found = false;
      boost::ptr_deque<appl::IpccObserverProxyIF>::iterator  iter = theObservers.begin();
      while (!found &&
    		  iter != theObservers.end())
      {
        if (observer == *iter)
        {
          theObservers.erase(iter);
          found = true;
        }
        else
        {
          ++iter;
        }
      }
    }
    bool IpccImpl::do_hasActiveSetupRole() const
    {
      // std::cout << "activeSetupRole = " << (theIsActiveSetup ? "true" : "false") << std::endl;
      return theIsActiveSetup;
    }
    bool IpccImpl::do_isConntentionWinning(
      lmp::DWORD  remoteNodeId) const
    {
      return (theLocalNodeId > remoteNodeId);
    }
    bool IpccImpl::do_isConfigAcceptable(
  	  const msg::ConfigMsg&  configMsg) const
    {
      // remoteNodeId, remoeCCId valid; HelloConfig in acceptable range
      return
        ( ( 3 * configMsg.m_helloConfig.m_data.m_helloIntv ) < configMsg.m_helloConfig.m_data.m_helloDeadIntv);
    }
    void IpccImpl::do_reportTransition(
      const appl::State&   sourceState,
      const appl::Event&   event,
      const appl::State&   targetState,
	  const appl::Action&  action)
    {
      for (boost::ptr_deque<appl::IpccObserverIF>::iterator iter = theObservers.begin(),
    		                                                end_iter = theObservers.end();
    		  iter != end_iter;
    		  ++iter)
      {
    	iter->notifyTransition(sourceState, event, targetState, action);
      }
//    std::cout << "IPCC[" << theLocalCCId << "]." << event << ": " << sourceState << " -> " << targetState
//        		<< " executing " << action << std::endl;
    }
    void IpccImpl::do_sendHelloMsg()
    {
      if (theTxSeqNum == std::numeric_limits<lmp::DWORD>::max())
      {
    	theTxSeqNum = 2;
      }
      else
      {
    	++theTxSeqNum;
      }
      // create an send Hello message and schedule Hello retransmit timer
    }
    void IpccImpl::do_processReceivedMessage(
  	  const msg::ConfigMsg&  configMsg)
    {
      if (canAcceptNewConfig())
      {
      	if (isConfigAcceptable(configMsg))
      	{
      	  theFSM.process_event(EvNewConfOK());
      	}
      	else
      	{
      	  theFSM.process_event(EvNewConfErr());
      	}
      }
      else
      {
        if (isConntentionWinning(configMsg))
        {
          theFSM.process_event(EvContenWin());
        }
        else
        {
          theFSM.process_event(EvContenLost(configMsg));
        }
      }
    }
    void IpccImpl::do_processReceivedMessage(
  	  const msg::ConfigAckMsg&   configAckMsg)
    {
        theFSM.process_event(EvConfDone());
    }
    void IpccImpl::do_processReceivedMessage(
      const msg::ConfigNackMsg&  configNackMsg)
    {
      theFSM.process_event(EvConfErr());
    }
    void IpccImpl::do_processReceivedMessage(
  	  const msg::HelloMsg&       helloMsg)
    {
//      std::cout << "processReceivedMessage helloMsg.theRcvSeqNum = " << helloMsg.theRcvSeqNum
//    	        << ", theTxSeqNum = " << theTxSeqNum << std::endl;
      if (helloMsg.m_hello.m_data.m_rcvSeqNum == theTxSeqNum)
      {
        theFSM.process_event(EvHelloRcvd());
        theRcvSeqNum = helloMsg.m_hello.m_data.m_txSeqNum;
      }
      else
      {
        theFSM.process_event(EvSeqNumErr());
      }
    }
    bool IpccImpl::canAcceptNewConfig() const
    {
      static const lmp::cc::appl::ConfRcv stateConfRcv;
      static const lmp::cc::appl::Active stateActive;
      static const lmp::cc::appl::Up stateUp;
      const boost::optional<const lmp::cc::appl::State&>& activeState = getActiveState();
      return
    	( activeState &&
    	  ( *activeState == stateConfRcv ||
    	    *activeState == stateActive ||
    		*activeState == stateUp ) );
    }
    bool IpccImpl::isConntentionWinning(
  	  const msg::ConfigMsg&  configMsg) const
    {
      return do_isConntentionWinning(configMsg.m_localNodeId.m_data.m_nodeId);
    }
    namespace appl
    {
      std::ostream& operator<<(
       std::ostream&       os,
	    const State&        state)
      {
    	os << state.getType();
    	return os;
      }
      std::ostream& operator<<(
        std::ostream&       os,
	    State::Type         stType)
      {
    	switch(stType)
    	{
          case State::Down:
    		os << "Down";
    		break;
    	  case State::ConfSnd:
    		os << "ConfSnd";
    		break;
    	  case State::ConfRcv:
    		os << "ConfRcv";
    		break;
    	  case State::Active:
    		os << "Active";
    		break;
          case State::Up:
    		os << "Up";
    		break;
          case State::GoingDown:
        	os << "GoingDown";
        	break;
          default:
    		os << "undefined (value = " << static_cast<lmp::DWORD>(stType) << ")";
    		break;
    	}
    	return os;
      }
      std::ostream& operator<<(
        std::ostream&       os,
		const Event&   event)
      {
    	os << event.getType();
    	return os;
      }
      std::ostream& operator<<(
        std::ostream&       os,
		Event::EvType  evType)
      {
    	switch(evType)
    	{
    	  case Event::EvBringUp:
    		os << "EvBringUp";
    		break;
    	  case Event::EvCCDn:
    		os << "EvCCDn";
    		break;
    	  case Event::EvConfDone:
    		os << "EvConfDone";
    		break;
    	  case Event::EvConfErr:
    		os << "EvConfErr";
    		break;
    	  case Event::EvNewConfOK:
    		os << "EvNewConfOK";
    		break;
    	  case Event::EvNewConfErr:
    		os << "EvNewConfErr";
    		break;
    	  case Event::EvContenWin:
    		os << "EvContenWin";
    		break;
    	  case Event::EvContenLost:
    		os << "EvContenLost";
    		break;
    	  case Event::EvAdminDown:
    		os << "EvAdminDown";
    		break;
    	  case Event::EvNbrGoesDn:
    		os << "EvNbrGoesDn";
    		break;
    	  case Event::EvHelloRcvd:
    		os << "EvHelloRcvd";
    		break;
    	  case Event::EvHoldTimer:
    		os << "EvHoldTimer";
    		break;
    	  case Event::EvSeqNumErr:
    		os << "EvSeqNumErr";
    		break;
    	  case Event::EvReconfig:
    		os << "EvReconfig";
    		break;
    	  case Event::EvConfRet:
    		os << "EvConfRet";
    		break;
    	  case Event::EvHelloRet:
    		os << "EvHelloRet";
    		break;
    	  case Event::EvDownTimer:
    		os << "EvDownTimer";
    		break;
    	  default:
    		os << "undefined (value = " << static_cast<lmp::DWORD>(evType) << ")";
    		break;
    	}
    	return os;
      }
      std::ostream& operator<<(
        std::ostream&   os,
		const Action&   action)
      {
    	os << action.getType();
    	return os;
      }
      std::ostream& operator<<(
        std::ostream&       os,
		Action::ActionType  actionType)
      {
    	switch(actionType)
    	{
    	  case Action::ActionSendConfig:
    		os << "SendConfig";
    		break;
    	  case Action::ActionStopSendConfig:
    		os << "StopSendConfig";
    		break;
    	  case Action::ActionResendConfig:
    		os << "ResendConfig";
    		break;
    	  case Action::ActionSendConfigAck:
    		os << "SendConfigAck";
    		break;
    	  case Action::ActionSendConfigNack:
    		os << "SendConfigNack";
    		break;
    	  case Action::ActionSendHello:
    		os << "SendHello";
    		break;
    	  case Action::ActionStopSendHello:
    		os << "StopSendHello";
    		break;
    	  case Action::ActionSetCCDownFlag:
    		os << "SetCCDownFlag";
    		break;
    	  case Action::ActionClearCCDownFlag:
    		os << "ClearCCDownFlag";
    		break;
    	  case Action::ActionNoAction:
    		os << "NoAction";
    		break;
    	  default:
    		os << "undefined (value = " << static_cast<lmp::DWORD>(actionType) << ")";
    		break;
    	}
    	return os;
      }

    }
  } // namespace cc
} // namespace lmp
