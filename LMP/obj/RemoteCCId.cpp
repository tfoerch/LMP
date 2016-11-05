/*
 * RemoteCCId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/RemoteCCId_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::ccid::parse::remote_control_channel_id_grammar<BufIterType>;

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                          os,
  const lmp::obj::ccid::RemoteCCIdData&  remoteCCId)
{
  os << (remoteCCId.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << remoteCCId.m_CCId;
  return os;
}
