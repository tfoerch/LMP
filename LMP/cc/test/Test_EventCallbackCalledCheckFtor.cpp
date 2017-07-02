/*
 * Test_EventCallbackCalledCheckFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Test_EventCallbackCalledCheckFtor.hpp"
#include "neighbor/NeighborAdjacencyObserverIF.hpp"

#include <iostream>

namespace lmp
{
  namespace cc
  {
    namespace test
    {
      EventCallbackCalledCheckFtor::EventCallbackCalledCheckFtor()
      : m_callbackWasCalled(false)
      {}
      EventCallbackCalledCheckFtor::EventCallbackCalledCheckFtor(
        const EventCallbackCalledCheckFtor&  other)
      : m_callbackWasCalled(other.m_callbackWasCalled)
      {}
      void EventCallbackCalledCheckFtor::eventOccurred()
      {
        m_callbackWasCalled = true;
      }
      bool EventCallbackCalledCheckFtor::do_check() const
      {
        return m_callbackWasCalled;
      }
      base::CheckFtorIF* EventCallbackCalledCheckFtor::do_clone() const
      {
        return new EventCallbackCalledCheckFtor(*this);
      }
    }
  } // namespace cc
} // namespace lmp
