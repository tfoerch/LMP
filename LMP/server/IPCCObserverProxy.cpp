
#include <IPCCObserverProxy.hpp>
#include <IPCC_Impl.hpp>
#include "lmp_mgtif_ipcc_observer.hpp"  // for IPCCObserver_var, etc
#include <iostream>                     // for operator<<, ostream, etc
#include <typeinfo>                     // for bad_cast


namespace lmp
{
  namespace cc
  {
    namespace appl
    {
      IpccObserverProxy::IpccObserverProxy(
        IpccImpl&                              ipcc,
        ::lmp_ipcc_observer::IPCCObserver_ptr  observer)
      : theIpcc(ipcc),
        thePeerIPCCObserver(::lmp_ipcc_observer::IPCCObserver::_duplicate(observer)),
        theTransitions()
      {
      }
      IpccObserverProxy::~IpccObserverProxy()
      {
      }
      const IpccObserverProxy::TransistionSequence& IpccObserverProxy::getTransistions() const
      {
        return theTransitions;
      }
      void IpccObserverProxy::reset()
      {
        theTransitions.clear();
      }
      void IpccObserverProxy::do_notifyTransition(
        const IpccApplicationIF&  ipcc,
    	const appl::State&        sourceState,
    	const appl::Event&        event,
    	const appl::State&        targetState,
    	const appl::Action&       action)
      {
    	std::cout << "IPCC[" << theIpcc.getLocalCCId() << "]." << event << ": "
    	          << sourceState << " -> " << targetState
    	          << " executing " << action << std::endl;
    	TransRecord  transRecord(sourceState.getType(),
    	                         event.getType(),
    	                         targetState.getType(),
    	                         action.getType());
    	theTransitions.push_back(transRecord);
    	if (sourceState != targetState)
    	{
    	  ::lmp_ipcc_observer::IPCC_State newState = ::lmp_ipcc_observer::IPCC_Down;
    	  switch(targetState.getType())
    	  {
    	    case appl::State::Down:
    	      newState = ::lmp_ipcc_observer::IPCC_Down;
    	      break;
    	    case appl::State::ConfSnd:
      	      newState = ::lmp_ipcc_observer::IPCC_ConfSend;
      	      break;
    	    case appl::State::ConfRcv:
      	      newState = ::lmp_ipcc_observer::IPCC_ConfRecv;
      	      break;
    	    case appl::State::Active:
      	      newState = ::lmp_ipcc_observer::IPCC_Active;
      	      break;
    	    case appl::State::Up:
      	      newState = ::lmp_ipcc_observer::IPCC_Up;
      	      break;
    	    case appl::State::GoingDown:
      	      newState = ::lmp_ipcc_observer::IPCC_GoingDown;
      	      break;
    	  }
    	  thePeerIPCCObserver->stateHasChanged(theIpcc.getLocalCCId(), newState);
    	}
      }
      bool IpccObserverProxy::is_equal(
        const IpccObserverProxyIF& other) const
      {
        try
        {
          const IpccObserverProxy& otherObsProxy = dynamic_cast<const IpccObserverProxy&>(other);
          return thePeerIPCCObserver->_is_equivalent(otherObsProxy.thePeerIPCCObserver);
        }
        catch (std::bad_cast&)
        {
          return false;
        }
      }
      lmp::cc::appl::IpccObserverProxyIF* IpccObserverProxy::do_clone() const
      {
        return new IpccObserverProxy(*this);
      }
      IpccObserverProxy::TransRecord::TransRecord(
          appl::State::Type         sourceState,
          appl::Event::EvType       event,
          appl::State::Type         targetState,
          appl::Action::ActionType  action)
      : theSourceState(sourceState),
        theEvent(event),
        theTargetState(targetState),
        theAction(action)
      {
      }
      bool IpccObserverProxy::TransRecord::operator==(
        const TransRecord&  other) const
      {
        return
          ( theSourceState == other.theSourceState &&
            theEvent == other.theEvent &&
            theTargetState == other.theTargetState &&
            theAction == other.theAction );
      }
      std::ostream& operator<<(
        std::ostream&                                 os,
        const IpccObserverProxy::TransistionSequence&  transitions)
      {
    	for (IpccObserverProxy::TransistionSequence::const_iterator iter = transitions.begin(),
    			                                                   end_iter = transitions.end();
    	    iter != end_iter;
    	    ++iter)
    	{
    	  if (iter != transitions.begin())
    	  {
    	    os << ", ";
    	  }
    	  os << *iter;
    	}
    	return os;
      }
      std::ostream& operator<<(
        std::ostream&                                 os,
        const IpccObserverProxy::TransRecord&          transition)
      {
    	os << transition.theEvent << "("
    	   << transition.theSourceState << "->"
    	   << transition.theTargetState << ")."
    	   << transition.theAction;
    	return os;
      }
    } // namespace appl
  } // namespace cc
} // namespace lmp
