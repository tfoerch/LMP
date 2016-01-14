/*
 * CheckExpiryTimerFtor.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "CheckExpiryTimerFtor.hpp"
#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

namespace lmp
{
  namespace base
  {
    CheckExpiryTimerFtor::CheckExpiryTimerFtor(
      boost::asio::io_service&                 io_service,
	  const boost::posix_time::time_duration&  expiry_time)
      : CheckFtorIF(),
		m_timer(io_service, expiry_time),
		m_hasExpired(false)
    {
      m_timer.async_wait(boost::bind(&CheckExpiryTimerFtor::handle_expired,
		                             this,
			                         boost::asio::placeholders::error));
    }

    CheckExpiryTimerFtor::CheckExpiryTimerFtor(
      const CheckExpiryTimerFtor&      other)
    : CheckFtorIF(),
	  m_timer(const_cast<boost::asio::deadline_timer&>(other.m_timer).get_io_service(),
			  other.m_timer.expires_at()),
	  m_hasExpired(other.m_hasExpired)
    {
      if (!m_hasExpired)
      {
        m_timer.async_wait(boost::bind(&CheckExpiryTimerFtor::handle_expired,
    	                               this,
									   boost::asio::placeholders::error));

      }
    }

    bool CheckExpiryTimerFtor::do_check() const
    {
      return m_hasExpired;
    }

    CheckFtorIF* CheckExpiryTimerFtor::do_clone() const
    {
      return new CheckExpiryTimerFtor(*this);
    }

    void CheckExpiryTimerFtor::handle_expired(
  	  const boost::system::error_code& /*error*/)
    {
      m_hasExpired = true;
    }
  } // namespace cc
} // namespace lmp
