/*
 * MessageIdAck.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdAck_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::msgid::parse::message_id_ack_grammar<BufIterType>;

std::ostream& lmp::obj::msgid::operator<<(
  std::ostream&                         os,
  const lmp::obj::msgid::MessageIdAckData&  messageIdAck)
{
  os << (messageIdAck.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << messageIdAck.m_messageId;
  return os;
}
