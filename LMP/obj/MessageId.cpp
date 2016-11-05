/*
 * MessageId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageId_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::msgid::parse::message_id_grammar<BufIterType>;

std::ostream& lmp::obj::msgid::operator<<(
  std::ostream&                          os,
  const lmp::obj::msgid::MessageIdData&  messageId)
{
  os << (messageId.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << messageId.m_messageId;
  return os;
}
