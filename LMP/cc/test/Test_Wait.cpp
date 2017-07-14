/*
 * Test_Wait.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include <Test_Wait.hpp>
#include <CheckExpiryTimerFtor.hpp>

namespace lmp
{
  namespace test
  {
    namespace util
    {
      bool wait(
    	const lmp::base::CheckFtorIF&            checkFtor,
    	boost::asio::io_service&                 io_service,
        const boost::posix_time::time_duration&  expiry_time)
      {
        lmp::base::CheckExpiryTimerFtor  expiryTimer(io_service, expiry_time);
        while (!checkFtor() && !expiryTimer())
        {
          io_service.run_one();
        }
        return checkFtor();
      }
    } // namespace util
  } // namespace test
} // namespace lmp
