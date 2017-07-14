#ifndef LMP_BASE_RETRANSMIT_TIMER_HPP_
#define LMP_BASE_RETRANSMIT_TIMER_HPP_
/*
 * RetransmitTimer.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "base/ProtocolTypes.hpp"                  // for DWORD
#include <boost/function.hpp>
#include <boost/asio/high_resolution_timer.hpp>

#include <chrono>

namespace lmp
{
  namespace base
  {
    class RetransmitTimer
    {
    public:
      RetransmitTimer(
    	boost::asio::io_service&          io_service,
    	const std::chrono::milliseconds&  initialRetransmitIinterval,
    	lmp::DWORD                        retryLimit,
    	lmp::DWORD                        incrementValueDelta,
    	boost::function<bool (bool)>      expiry_callback);
      void start();
      void stop();
      bool isReltryLimitReached() const
      { return ( m_retryCounter >= m_retryLimit ); }
    private:
      void handle_expired(
    	const boost::system::error_code&  error);
      boost::asio::high_resolution_timer      m_timer;
      std::chrono::milliseconds               m_initialRetransmitIinterval;
      lmp::DWORD                              m_retryLimit;
      lmp::DWORD                              m_incrementValueDelta;
      boost::function<bool (bool)>            m_expiry_callback;
      std::chrono::milliseconds               m_currentRetransmitIinterval;
      lmp::DWORD                              m_retryCounter;
    };
  } // namespace base
} // namespace lmp

#endif /* LMP_BASE_RETRANSMIT_TIMER_HPP_ */
