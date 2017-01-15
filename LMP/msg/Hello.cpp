/*
 * Hello.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "Hello_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::hello_grammar<BufIterType>;

namespace lmp
{
  namespace msg
  {
    lmp::DWORD getLength(
      const HelloMsg&  hello)
    {
      lmp::DWORD length =
        ( lmp::msg::c_headerLength +
          lmp::obj::getLength(hello.m_hello) );
      return length;
    }
    bool operator==(
      const HelloMsg&  first,
      const HelloMsg&  second)
    {
      return
        ( first.m_flags == second.m_flags &&
          first. m_hello== second.m_hello  );
    }
    std::ostream& operator<<(
      std::ostream&    os,
      const HelloMsg&  hello)
    {
      std::cout << "HelloMsg(" << static_cast<lmp::WORD>(hello.m_flags)
	        << ", " << hello.m_hello
	        << ")";
      return os;
    }
  } // namespace msg
} // namespace lmp
