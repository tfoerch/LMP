/*
 * UnknownNodeIdCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownNodeIdCType.hpp"
#include "obj/ObjectClassUnknownCType_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::object_class_unknown_ctype_grammar<BufIterType, lmp::obj::ObjectClass::NodeID>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generate::object_class_unknown_ctype_grammar<BufOutIterType, lmp::obj::ObjectClass::NodeID>;
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::NodeID>>(
  std::ostream&,
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::NodeID>>&);
template bool lmp::obj::operator== <lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::NodeID>>(
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::NodeID>>&,
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::NodeID>>&);
