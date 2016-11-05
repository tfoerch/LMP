/*
 * UnknownHelloCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownHelloCType_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::hello::parse::unknown_hello_grammar<BufIterType>;

std::ostream& lmp::obj::hello::operator<<(
  std::ostream&                                os,
  const lmp::obj::hello::UnknownHelloCTypeData&  unknownHelloCType)
{
  using lmp::obj::hex_stream::operator<<;

  os << unknownHelloCType.m_header << ", "
	 << unknownHelloCType.m_data;
  return os;
}
