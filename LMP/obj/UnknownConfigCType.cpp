/*
 * UnknownConfigCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownConfigCType_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::config::parse::unknown_config_grammar<BufIterType>;

std::ostream& lmp::obj::config::operator<<(
  std::ostream&                                os,
  const lmp::obj::config::UnknownConfigCTypeData&  unknownConfigCType)
{
  using lmp::obj::hex_stream::operator<<;

  os << unknownConfigCType.m_header << ", "
	 << unknownConfigCType.m_data;
  return os;
}
