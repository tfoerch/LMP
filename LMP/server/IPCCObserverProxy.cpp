
#include <IPCCObserverProxy.hpp>
#include <IPCCApplicationIF.hpp>
#include "lmp_mgtif_ipcc_observer.hpp"  // for IPCCObserver_var, etc
#include <iostream>                     // for operator<<, ostream, etc
#include <typeinfo>                     // for bad_cast


namespace lmp_ipcc
{
  IpccObserverProxy::IpccObserverProxy(
    const lmp::cc::IpccApplicationIF&      ipcc,
    const IPCCObserverContainer&  ipccObserverContainer)
  : m_ipcc(ipcc),
    m_ipccObserverContainer(ipccObserverContainer),
    m_transitions()
  {
  }
  const IpccObserverProxy::TransistionSequence& IpccObserverProxy::getTransistions() const
  {
    return m_transitions;
  }
  void IpccObserverProxy::reset()
  {
    m_transitions.clear();
  }
  void IpccObserverProxy::do_notifyTransition(
    const lmp::cc::IpccApplicationIF&  ipcc,
    const lmp::cc::appl::State&        sourceState,
    const lmp::cc::appl::Event&        event,
    const lmp::cc::appl::State&        targetState,
    const lmp::cc::appl::Action&       action)
  {
    std::cout << "IPCC[" << m_ipcc.getLocalCCId() << "]." << event << ": "
              << sourceState << " -> " << targetState
              << " executing " << action << std::endl;
    TransRecord  transRecord(sourceState.getType(),
                             event.getType(),
                             targetState.getType(),
                             action.getType());
    m_transitions.push_back(transRecord);
    if (sourceState != targetState)
    {
      ::lmp_ipcc_observer::IPCC_State newState = ::lmp_ipcc_observer::IPCC_Down;
      switch(targetState.getType())
      {
        case lmp::cc::appl::State::Down:
          newState = ::lmp_ipcc_observer::IPCC_Down;
          break;
        case lmp::cc::appl::State::ConfSnd:
          newState = ::lmp_ipcc_observer::IPCC_ConfSend;
          break;
        case lmp::cc::appl::State::ConfRcv:
          newState = ::lmp_ipcc_observer::IPCC_ConfRecv;
          break;
        case lmp::cc::appl::State::Active:
          newState = ::lmp_ipcc_observer::IPCC_Active;
          break;
        case lmp::cc::appl::State::Up:
          newState = ::lmp_ipcc_observer::IPCC_Up;
          break;
        case lmp::cc::appl::State::GoingDown:
          newState = ::lmp_ipcc_observer::IPCC_GoingDown;
          break;
      }
      for (IPCCObserverContainer::const_iterator iter = m_ipccObserverContainer.begin(),
                                                 end_iter = m_ipccObserverContainer.end();
           iter != end_iter;
           ++iter)
      {
        (*iter)->stateHasChanged(m_ipcc.getLocalCCId(), newState);
      }
    }
  }
  IpccObserverProxy::TransRecord::TransRecord(
    lmp::cc::appl::State::Type         sourceState,
    lmp::cc::appl::Event::EvType       event,
    lmp::cc::appl::State::Type         targetState,
    lmp::cc::appl::Action::ActionType  action)
  : m_sourceState(sourceState),
    m_event(event),
    m_targetState(targetState),
    m_action(action)
  {
  }
  bool IpccObserverProxy::TransRecord::operator==(
    const TransRecord&  other) const
  {
    return
      ( m_sourceState == other.m_sourceState &&
        m_event == other.m_event &&
        m_targetState == other.m_targetState &&
        m_action == other.m_action );
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
    const IpccObserverProxy::TransRecord&         transition)
  {
    os << transition.m_event << "("
       << transition.m_sourceState << "->"
       << transition.m_targetState << ")."
       << transition.m_action;
    return os;
  }
} // namespace lmp
