/*
 * UnknownNodeIdCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownNodeIdCType_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::nodeid::parse::unknown_node_id_grammar<BufIterType>;

std::ostream& lmp::obj::nodeid::operator<<(
  std::ostream&                                os,
  const lmp::obj::nodeid::UnknownNodeIdCTypeData&  unknownNodeIdCType)
{
  using lmp::obj::hex_stream::operator<<;

  os << unknownNodeIdCType.m_header << ", "
	 << unknownNodeIdCType.m_data;
  return os;
}
