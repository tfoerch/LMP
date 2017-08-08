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
template bool lmp::obj::operator== <lmp::obj::ObjectClassTypeTraits<lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>>(
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>>&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::hello::ClassType, lmp::obj::hello::ClassType::Hello>>&);

bool lmp::obj::hello::IsEqualFtor::operator()(
  const  HelloBody& first,
  const  HelloBody& second) const
{
  return
    ( first.m_txSeqNum == second.m_txSeqNum &&
      first.m_rcvSeqNum == second.m_rcvSeqNum );
}

const lmp::WORD lmp::obj::hello::GetLengthFtor::c_length = 4 + 4;

lmp::WORD lmp::obj::hello::GetLengthFtor::operator()(
  const HelloBody& hello) const
{
  return c_length;
}

std::ostream& lmp::obj::hello::operator<<(
  std::ostream&                         os,
  const lmp::obj::hello::HelloBody&     hello)
{
  os << hello.m_txSeqNum << ", "
     << hello.m_rcvSeqNum;
  return os;
}