/*
 * ControlChannelIdClass.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/ControlChannelIdClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::ccid::parse::control_channel_id_body_grammar<BufIterType>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::ccid::generate::control_channel_id_body_grammar<BufOutIterType>;

std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                     os,
  const lmp::obj::ccid::ClassType&  cType)
{
  switch(cType)
  {
    case lmp::obj::ccid::ClassType::LocalCCId:
	  os << "LocalCCId";
	  break;
    case lmp::obj::ccid::ClassType::RemoteCCId:
  	  os << "RemoteCCId";
  	  break;
  }
  return os;
}
std::ostream& lmp::obj::ccid::operator<<(
  std::ostream&                                  os,
  const lmp::obj::ccid::ControlChannelIdBody&  controlChannelIdBody)
{
  os << controlChannelIdBody.m_CCId;
  return os;
}

