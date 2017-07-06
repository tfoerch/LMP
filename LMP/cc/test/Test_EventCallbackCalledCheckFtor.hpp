#ifndef EVENTCALLBACKCALLEDCheckFtor_HPP_
#define EVENTCALLBACKCALLEDCheckFtor_HPP_
/*
 * Test_EventCallbackCalledCheckFtor.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

#include "base/CheckFtorIF.hpp"

namespace lmp
{
  namespace cc
  {
    namespace test
    {
      class EventCallbackCalledCheckFtor : public lmp::base::CheckFtorIF
      {
      public:
        EventCallbackCalledCheckFtor();
        EventCallbackCalledCheckFtor(
          const EventCallbackCalledCheckFtor&  other);
        bool eventOccurred(
          bool retryLimitReached);
        inline bool isRetryLimitReached() const
        { return m_retryLimitReached; }
        void reset();
      private:
        virtual bool do_check() const;
        virtual CheckFtorIF* do_clone() const;
        bool m_callbackWasCalled;
        bool m_retryLimitReached;
      };
    };
  } // namespace cc
} // namespace lmp

#endif /* EVENTCALLBACKCALLEDCheckFtor_HPP_ */
