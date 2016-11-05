/*
 * ControlChannelIdCTypes.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdCTypes_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::ccid::parse::control_channel_id_ctypes_grammar<BufIterType>;

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                                  os,
  const lmp::obj::ccid::ControlChannelIdCTypes&  controlChannelIdCTypes)
{
  return os;
}
