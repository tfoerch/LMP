#ifndef LMP_BASE_RETRANSMIT_TIMER_HPP_
#define LMP_BASE_RETRANSMIT_TIMER_HPP_
/*
 * RetransmitTimer.hpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include <boost/function.hpp>
#include <boost/asio/deadline_timer.hpp>

namespace lmp
{
  namespace base
  {
    class RetransmitTimer
    {
    public:
      RetransmitTimer(
    	boost::asio::io_service&                 io_service,
    	const boost::posix_time::time_duration&  expiry_time,
    	boost::function<void()>                  expiry_callback);
      void start();
      void reschedule();
      void stop();
    private:
      void handle_expired(
    	const boost::system::error_code&  error);
      boost::asio::deadline_timer       m_timer;
      boost::posix_time::time_duration  m_expiry_time;
      boost::function<void()>           m_expiry_callback;
    };
  } // namespace base
} // namespace lmp

#endif /* LMP_BASE_RETRANSMIT_TIMER_HPP_ */
