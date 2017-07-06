/*
 * RetransmitTimer.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "RetransmitTimer.hpp"
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include <iostream>

namespace lmp
{
  namespace base
  {
    //      Prior to initial transmission, initialize Rk = Ri and Rn = 0.
    //
    //      while (Rn++ < Rl) {
    //        transmit the message;
    //        wake up after Rk milliseconds;
    //        Rk = Rk * (1 + Delta);
    //      }
    //      /* acknowledged message or no reply from receiver and Rl
    //         reached */
    //      do any needed clean up;
    //      exit;
   RetransmitTimer::RetransmitTimer(
      boost::asio::io_service&          io_service,
      const std::chrono::milliseconds&  initialRetransmitIinterval,
      lmp::DWORD                        retryLimit,
      lmp::DWORD                        incrementValueDelta,
      boost::function<bool(bool)>           expiry_callback)
      : m_timer(io_service),
        m_initialRetransmitIinterval(initialRetransmitIinterval),
        m_retryLimit(retryLimit),
        m_incrementValueDelta(m_incrementValueDelta),
        m_expiry_callback(expiry_callback),
        m_currentRetransmitIinterval(m_initialRetransmitIinterval),
        m_retryCounter(0)
    {
    }
    void RetransmitTimer::start()
    {
      boost::system::error_code  error;
      m_timer.expires_from_now(m_initialRetransmitIinterval, error);
      m_timer.async_wait(boost::bind(&RetransmitTimer::handle_expired,
                                     this,
                                     boost::asio::placeholders::error));

    }
    void RetransmitTimer::reschedule()
    {

    }
    void RetransmitTimer::stop()
    {

    }
    void RetransmitTimer::handle_expired(
      const boost::system::error_code&  error)
    {
      std::cout << "RetransmitTimer::handle_expired called" << std::endl;
      if (!error)
      {
        //bool reschedule =
          m_expiry_callback(m_retryCounter >= m_retryLimit);
      }
    }
  } // namespace cc
} // namespace lmp
