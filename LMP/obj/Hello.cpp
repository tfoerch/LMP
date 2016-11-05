/*
 * Hello.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/Hello_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::hello::parse::hello_grammar<BufIterType>;

std::ostream& lmp::obj::hello::operator<<(
  std::ostream&                         os,
  const lmp::obj::hello::HelloData&     hello)
{
  os << (hello.m_negotiable ? "negotiable" : "not negotiable") << ", "
	 << hello.m_txSeqNum << ", "
	 << hello.m_rcvSeqNum;
  return os;
}
