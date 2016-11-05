/*
 * UnknownMessageIdCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownMessageIdCType_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::msgid::parse::unknown_message_id_grammar<BufIterType>;

std::ostream& lmp::obj::msgid::operator<<(
  std::ostream&                                os,
  const lmp::obj::msgid::UnknownMessageIdCTypeData&  unknownMessageIdCType)
{
  using lmp::obj::hex_stream::operator<<;

  os << unknownMessageIdCType.m_header << ", "
	 << unknownMessageIdCType.m_data;
  return os;
}
