/*
 * MessageId.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/MessageId.hpp"
#include "obj/ObjectClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::object_class_grammar<BufIterType, lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generate::object_class_grammar<BufOutIterType, lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>;
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>>(
  std::ostream&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>>&);
template bool lmp::obj::operator== <lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>>(
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>>&,
  const lmp::obj::ObjectClassTypeData<lmp::obj::ObjectClassTypeTraits<lmp::obj::msgid::ClassType, lmp::obj::msgid::ClassType::MessageId>>&);