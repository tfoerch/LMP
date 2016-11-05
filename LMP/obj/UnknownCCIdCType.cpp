/*
 * UnknownCCIdCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownCCIdCType_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::ccid::parse::unknown_control_channel_id_grammar<BufIterType>;

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                                os,
  const lmp::obj::ccid::UnknownCCIdCTypeData&  unknownCCIdCType)
{
  using lmp::obj::hex_stream::operator<<;

  os << unknownCCIdCType.m_header << ", "
	 << unknownCCIdCType.m_data;
  return os;
}
