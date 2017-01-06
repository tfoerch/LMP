/*
 * MessageIdClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageIdClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::msgid::parse::message_id_body_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::msgid::generate::message_id_body_grammar<BufOutIterType>;

std::ostream& lmp::obj::msgid::operator<<(
  std::ostream&     os,
  const ClassType&  cType)
{
  switch(cType)
  {
    case ClassType::MessageId:
      os << "MessageId";
      break;
    case ClassType::MessageIdAck:
      os << "MessageIdAck";
      break;
  }
  return os;
}

bool lmp::obj::msgid::IsEqualFtor::operator()(
  const  MessageIdBody& first,
  const  MessageIdBody& second) const
{
  return ( first.m_messageId == second.m_messageId );
}

const lmp::WORD lmp::obj::msgid::GetLengthFtor::c_length = 4;

lmp::WORD lmp::obj::msgid::GetLengthFtor::operator()(
  const MessageIdBody& messageIdBody) const
{
  return c_length;
}

std::ostream& lmp::obj::msgid::operator<<(
  std::ostream&                          os,
  const lmp::obj::msgid::MessageIdBody&  messageIdBody)
{
  os << messageIdBody.m_messageId;
  return os;
}

