/*
 * UnknownHelloCType.cpp
 *
 *  Created on: 28.02.2015
 *      Author: tom
 */

#include "obj/UnknownHelloCType.hpp"
#include "obj/ObjectClass_def.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>

typedef boost::asio::buffers_iterator<boost::asio::const_buffers_1>  BufIterType;
template struct lmp::obj::parse::object_class_unknown_ctype_grammar<BufIterType, lmp::obj::ObjectClass::Hello>;
typedef boost::asio::buffers_iterator<boost::asio::mutable_buffers_1>  BufOutIterType;
template struct lmp::obj::generate::object_class_unknown_ctype_grammar<BufOutIterType, lmp::obj::ObjectClass::Hello>;
template std::ostream& lmp::obj::operator<< <lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::Hello>>(
  std::ostream&,
  const lmp::obj::ObjectClassUnknownCTypeData<lmp::obj::ObjectClassTraits<lmp::obj::ObjectClass::Hello>>&);


