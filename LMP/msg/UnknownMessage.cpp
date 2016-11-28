/*
 * UnknownMessage.cpp
 *
 *  Created on: 20.02.2015
 *      Author: tom
 */

#include "UnknownMessage_def.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <iostream>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::msg::parse::unknown_message_grammar<BufIterType>;

namespace lmp
{
  namespace msg
  {
    namespace parse
    {
	  std::ostream& operator<<(
	    std::ostream&          os,
		const UnknownMessage&  unknownMessage)
	  {
	    std::cout << "UnknownMessage(" << unknownMessage.m_header
				  << ", " << unknownMessage.m_objects
				  << ")";
	    return os;
	  }
    }
  } // namespace msg
} // namespace lmp
