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
    RetransmitTimer::RetransmitTimer(
      boost::asio::io_service&                 io_service,
      const boost::posix_time::time_duration&  expiry_time,
      boost::function<void()>                  expiry_callback)
      : m_timer(io_service),
        m_expiry_time(expiry_time),
        m_expiry_callback(expiry_callback)
    {
    }
    void RetransmitTimer::start()
    {
      boost::system::error_code  error;
      m_timer.expires_from_now(m_expiry_time, error);
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
        m_expiry_callback();
      }
    }
  } // namespace cc
} // namespace lmp
