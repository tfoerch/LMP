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
    std::ostream& operator<<(
      std::ostream&     os,
	  const HelloMsg&  hello)
    {
      std::cout << "HelloMsg(" << static_cast<lmp::WORD>(hello.m_flags)
			    << ", " << hello.m_hello
				<< ")";
      return os;
    }
  } // namespace msg
} // namespace lmp
