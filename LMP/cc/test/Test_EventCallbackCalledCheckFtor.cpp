/*
 * Test_EventCallbackCalledCheckFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_EventCallbackCalledCheckFtor.hpp"
#include "neighbor/NeighborAdjacencyObserverIF.hpp"

#include <boost/chrono.hpp>
#include <iostream>

namespace lmp
{
  namespace cc
  {
    namespace test
    {
      EventCallbackCalledCheckFtor::EventCallbackCalledCheckFtor(
        lmp::DWORD                        numberOfCalls)
      : m_numberOfCalls(numberOfCalls),
        m_timeouts()
      {}
      EventCallbackCalledCheckFtor::EventCallbackCalledCheckFtor(
        const EventCallbackCalledCheckFtor&  other)
      : m_numberOfCalls(other.m_numberOfCalls),
        m_timeouts(other.m_timeouts)
      {}
      bool EventCallbackCalledCheckFtor::eventOccurred(
        bool retryLimitReached)
      {
        TimeoutEvent  timeoutEvent =
          { std::chrono::system_clock::now(), retryLimitReached };
        boost::unique_lock<boost::shared_mutex> guard(m_flags_mutex);
        std::cout << "EventCallbackCalledCheckFtor::eventOccurred(retryLimitReached = "
                  << retryLimitReached << ")" << std::endl;
        m_timeouts.push_back(timeoutEvent);
        return !retryLimitReached;
      }
      const EventCallbackCalledCheckFtor::TimeoutEventSequence&
      EventCallbackCalledCheckFtor::getTimeouts() const
      {
        return m_timeouts;
      }
      void EventCallbackCalledCheckFtor::reset()
      {
        boost::unique_lock<boost::shared_mutex> guard(m_flags_mutex);
        m_timeouts.clear();
      }
      bool EventCallbackCalledCheckFtor::do_check() const
      {
        boost::shared_lock<boost::shared_mutex> guard(m_flags_mutex);
        std::cout << "EventCallbackCalledCheckFtor::do_check() called at " << boost::chrono::steady_clock::now() << std::endl;
        return (m_timeouts.size() == m_numberOfCalls);
      }
      base::CheckFtorIF* EventCallbackCalledCheckFtor::do_clone() const
      {
        return new EventCallbackCalledCheckFtor(*this);
      }
    }
  } // namespace cc
} // namespace lmp
