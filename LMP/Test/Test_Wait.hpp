#ifndef TEST_UTIL_WAIT_HPP_
#define TEST_UTIL_WAIT_HPP_
/*
 * Test_Wait.hpp
 *
 *  Created on: 19.02.2015
 *      Author: tom
 */

namespace boost
{
  namespace asio { class io_service; }
  namespace posix_time { class time_duration; }
}
namespace lmp
{
  namespace base { class CheckFtorIF; }
  namespace test
  {
    namespace util
    {
      bool wait(
    	const lmp::base::CheckFtorIF&            checkFtor,
    	boost::asio::io_service&                 io_service,
        const boost::posix_time::time_duration&  expiry_time);
    } // namespace util
  } // namespace test
} // namespace lmp

#endif /* TEST_UTIL_WAIT_HPP_ */
