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
template struct lmp::obj::hello::parse::hello_body_grammar<BufIterType>;
template struct lmp::obj::parse::object_class_grammar<BufIterType, lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::hello::generate::hello_body_grammar<BufOutIterType>;
template struct lmp::obj::generate::object_class_grammar<BufOutIterType, lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>;
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTypeTraits<lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>>(
  std::ostream&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>>&);

std::ostream& lmp::obj::hello::operator<<(
  std::ostream&                         os,
  const lmp::obj::hello::HelloBody&     hello)
{
  os << hello.m_txSeqNum << ", "
	 << hello.m_rcvSeqNum;
  return os;
}
